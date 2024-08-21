/*
 * Copyright (c) 2024 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "OMStatus.h"

#include "core/OMUtils.h"
#include "core/OMRuntimeShape.h"

#include "execute/OMUtils.h"
#include "execute/OMKernelExecutionBuilder.h"
#include "execute/OMRuntimeKernel.h"

#include "PALSub.h"

using namespace onert_micro;
using namespace onert_micro::execute;

namespace
{

constexpr uint32_t numInput = 2;
constexpr uint32_t numOutput = 1;

constexpr uint32_t input1TensorIdx = 0;
constexpr uint32_t input2TensorIdx = 1;
constexpr uint32_t outputTensorIdx = 0;

void calculateQuantParams(core::ArithmeticQuantParams &params, const circle::Tensor *input1,
                          const circle::Tensor *input2, const circle::Tensor *output,
                          circle::ActivationFunctionType act)
{
  long input1_zp;
  long input2_zp;
  long output_zp;

  float input1_scale;
  float input2_scale;
  float output_scale;

  // Read input1 quant params
  readQuantParams(input1, input1_zp, input1_scale);
  // Read input2 quant params
  readQuantParams(input2, input2_zp, input2_scale);
  // Read output quant params
  readQuantParams(output, output_zp, output_scale);

  params.input1_offset = -static_cast<int32_t>(input1_zp);
  params.input2_offset = -static_cast<int32_t>(input2_zp);
  params.output_offset = static_cast<int32_t>(output_zp);
  params.left_shift = (output->type() == circle::TensorType_INT16) ? 15 : 20;
  const double twice_max_input_scale =
    2 * static_cast<double>(std::max(input1_scale, input2_scale));
  const double real_input1_multiplier = static_cast<double>(input1_scale) / twice_max_input_scale;
  const double real_input2_multiplier = static_cast<double>(input2_scale) / twice_max_input_scale;
  const double real_output_multiplier =
    twice_max_input_scale / ((1 << params.left_shift) * static_cast<double>(output_scale));

  quantizeMultiplierSmallerThanOneExp(real_input1_multiplier, &params.input1_multiplier,
                                      &params.input1_shift);

  quantizeMultiplierSmallerThanOneExp(real_input2_multiplier, &params.input2_multiplier,
                                      &params.input2_shift);

  quantizeMultiplierSmallerThanOneExp(real_output_multiplier, &params.output_multiplier,
                                      &params.output_shift);

  calculateActivationRangeQuantized(act, output_zp, output_scale, output->type(),
                                    &params.quantized_activation_min,
                                    &params.quantized_activation_max);
}

} // namespace

// NOTE: doesnt currently support dynamic shapes
// TODO: reduce code duplication with Add, Mul
OMStatus onert_micro::execute::execute_kernel_CircleSub(const OMExecuteArgs &execute_args)
{
  core::OMRuntimeContext &runtime_context = execute_args.runtime_context;
  core::OMRuntimeStorage &runtime_storage = execute_args.runtime_storage;
  uint16_t op_index = execute_args.kernel_index;

  const circle::Tensor *input1;
  const circle::Tensor *input2;
  const circle::Tensor *output;

  uint8_t *input1_data;
  uint8_t *input2_data;
  uint8_t *output_data;

  const circle::SubOptions *options;
  // Read kernel
  {
    execute::OMRuntimeKernel runtime_kernel;
    runtime_kernel.readKernel(op_index, runtime_context);

    input1 = runtime_kernel.inputs[input1TensorIdx];
    input2 = runtime_kernel.inputs[input2TensorIdx];
    output = runtime_kernel.outputs[outputTensorIdx];
    assert(input1 != nullptr);
    assert(input2 != nullptr);
    assert(output != nullptr);

    runtime_kernel.getDataFromStorage(op_index, runtime_storage, runtime_context);

    input1_data = runtime_kernel.inputs_data[input1TensorIdx];
    input2_data = runtime_kernel.inputs_data[input2TensorIdx];
    output_data = runtime_kernel.outputs_data[outputTensorIdx];
    assert(input1_data != nullptr);
    assert(input2_data != nullptr);
    assert(output_data != nullptr);

    options = runtime_kernel.first_operator->builtin_options_as_SubOptions();
  }

  OMStatus status;

  core::OMRuntimeShape input1_shape(input1);
  core::OMRuntimeShape input2_shape(input2);
  core::OMRuntimeShape output_shape(output);

  core::BinaryArithmeticBroadcastParams params{};
  const bool need_broadcast = pal::processBroadcastShapes(input1_shape, input2_shape, &params);

  switch (input1->type())
  {
#ifndef DIS_FLOAT
    case circle::TensorType_FLOAT32:
    {
      status = execute::calculateActivationRange(options->fused_activation_function(),
                                                 &params.float_activation_min,
                                                 &params.float_activation_max);

      if (need_broadcast)
      {
        status = pal::BroadcastSub4DSlow(
          params, input1_shape, core::utils::castInputData<float>(input1_data), input2_shape,
          core::utils::castInputData<float>(input2_data), output_shape,
          core::utils::castOutputData<float>(output_data));
      }
      else
      {
        status =
          pal::Sub(params, input1_shape.flatSize(), core::utils::castInputData<float>(input1_data),
                   core::utils::castInputData<float>(input2_data),
                   core::utils::castOutputData<float>(output_data));
      }
    }
    break;
    case circle::TensorType_INT64:
    {
      status = execute::calculateActivationRange(options->fused_activation_function(),
                                                 &params.int64_activation_min,
                                                 &params.int64_activation_max);

      if (need_broadcast)
      {
        status = pal::BroadcastSub4DSlow(
          params, input1_shape, core::utils::castInputData<int64_t>(input1_data), input2_shape,
          core::utils::castInputData<int64_t>(input2_data), output_shape,
          core::utils::castOutputData<int64_t>(output_data));
      }
      else
      {
        status = pal::Sub(params, input1_shape.flatSize(),
                          core::utils::castInputData<int64_t>(input1_data),
                          core::utils::castInputData<int64_t>(input2_data),
                          core::utils::castOutputData<int64_t>(output_data));
      }
    }
    break;
    case circle::TensorType_INT32:
    {
      status = execute::calculateActivationRange(options->fused_activation_function(),
                                                 &params.int32_activation_min,
                                                 &params.int32_activation_max);

      if (need_broadcast)
      {
        status = pal::BroadcastSub4DSlow(
          params, input1_shape, core::utils::castInputData<int32_t>(input1_data), input2_shape,
          core::utils::castInputData<int32_t>(input2_data), output_shape,
          core::utils::castOutputData<int32_t>(output_data));
      }
      else
      {
        status = pal::Sub(params, input1_shape.flatSize(),
                          core::utils::castInputData<int32_t>(input1_data),
                          core::utils::castInputData<int32_t>(input2_data),
                          core::utils::castOutputData<int32_t>(output_data));
      }
    }
    break;
#endif // DIS_FLOAT
#ifndef DIS_QUANT
    case circle::TensorType_INT8:
    {
      core::ArithmeticQuantParams sub_params{};

      calculateQuantParams(sub_params, input1, input2, output,
                           options->fused_activation_function());

      if (need_broadcast)
      {
        status = pal::BroadcastSub4DSlow(
          sub_params, input1_shape, core::utils::castInputData<int8_t>(input1_data), input2_shape,
          core::utils::castInputData<int8_t>(input2_data), output_shape,
          core::utils::castOutputData<int8_t>(output_data));
      }
      else
      {
        status = pal::Sub(sub_params, input1_shape.flatSize(),
                          core::utils::castInputData<int8_t>(input1_data),
                          core::utils::castInputData<int8_t>(input2_data),
                          core::utils::castOutputData<int8_t>(output_data));
      }
    }
    break;
#endif // DIF_QUANT
    default:
    {
      status = UnsupportedType;
      assert(false && "Unsupported type.");
    }
  }

  return status;
}
