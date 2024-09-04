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
#include "core/OMKernelData.h"
#include "core/OMDataType.h"

#include "execute/OMKernelExecutionBuilder.h"
#include "execute/OMUtils.h"
#include "execute/OMRuntimeKernel.h"

#include "PALCast.h"

using namespace onert_micro;
using namespace onert_micro::execute;

namespace
{

constexpr uint32_t inputTensorIdx = 0;
constexpr uint32_t outputTensorIdx = 0;

} // namespace

// NOTE: doesnt currently support dynamic shapes
OMStatus onert_micro::execute::execute_kernel_CircleCast(const OMExecuteArgs &execute_args)
{
  const circle::Tensor *input = nullptr;
  const circle::Tensor *output = nullptr;

  uint8_t *input_data = nullptr;
  uint8_t *output_data = nullptr;

  SISOHeader(execute_args, &input, &output, &input_data, &output_data);

  OMStatus status;

  switch (input->type())
  {
#ifndef DIS_FLOAT
    case circle::TensorType_FLOAT32:
    {
      switch (output->type())
      {
        case circle::TensorType_INT32:
        {
          status = pal::Cast(
            core::OMRuntimeShape(input), core::utils::castInputData<float>(input_data),
            core::OMRuntimeShape(output), core::utils::castOutputData<int32_t>(output_data));
          break;
        }
        case circle::TensorType_INT8:
        {
          status = pal::Cast(
            core::OMRuntimeShape(input), core::utils::castInputData<float>(input_data),
            core::OMRuntimeShape(output), core::utils::castOutputData<int8_t>(output_data));
          break;
        }
        case circle::TensorType_INT16:
        {
          status = pal::Cast(
            core::OMRuntimeShape(input), core::utils::castInputData<float>(input_data),
            core::OMRuntimeShape(output), core::utils::castOutputData<int16_t>(output_data));
          break;
        }
        default:
        {
          status = UnsupportedType;
          assert(false && "Unsupported type.");
          break;
        }
      }
    }
    break;
#endif // DIS_FLOAT
    default:
    {
      status = UnsupportedType;
      assert(false && "Unsupported type.");
      break;
    }
  }

  return status;
}
