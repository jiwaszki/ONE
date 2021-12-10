/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "Builders.h"

#include "kernels/AveragePool2D.h"
#include <luci/Plan/CircleNodeExecutionPlan.h>

namespace luci_interpreter
{

std::unique_ptr<Kernel> build_kernel_CircleAveragePool2D(const luci::CircleNode *circle_node,
                                                         KernelBuilderHelper &helper)
{
  const auto *node = dynamic_cast<const luci::CircleAveragePool2D *>(circle_node);
  if (node == nullptr)
    throw std::runtime_error("wrong builder for operation");
  assert(node->arity() == 1);

  const Tensor *input = helper.getInputTensor(node->value());
  Tensor *output = helper.getOutputTensor(node);

  Pool2DParams params{};
  params.padding = node->padding();
  params.filter_height = node->filter()->h();
  params.filter_width = node->filter()->w();
  params.stride_height = node->stride()->h();
  params.stride_width = node->stride()->w();
  params.activation = node->fusedActivationFunction();

  // It is unknown what data will be stored in scratchpad tensor,
  // using UINT8 as a most general option
  auto scratchpad = std::make_unique<Tensor>(DataType::U8, Shape({}), AffineQuantization{}, "");
  scratchpad->set_observable(false);
  scratchpad->set_data_buffer(nullptr);
  // If node has execution plan then read memory offsets for scratchpad temporary tensor
  // from the beginning of shared memory buffer.
  // Used in Static Memory Manager.
  // TODO move tensors offset initialization to one place
  if (luci::has_execution_plan(node))
  {
    const auto execution_plan = luci::get_execution_plan(node);
    // Check whether the offset for the current CircleConv2D temporary was found.
    if (execution_plan.offsets().size() > 1)
      // If this is true, then we keep this offset in scratchpad.
      scratchpad->set_offset(execution_plan.offsets().at(1));
  }
  Tensor *tmp = helper.getRuntimeGraph(node->graph())->addTensor(std::move(scratchpad));

  return std::make_unique<kernels::AveragePool2D>(input, output, tmp, params);
}

} // namespace luci_interpreter
