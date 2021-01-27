/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __LUCI_QUANTIZATION_UTILS_H__
#define __LUCI_QUANTIZATION_UTILS_H__

#include <luci/IR/CircleNodes.h>
#include <loco/IR/TensorShape.h>

namespace luci
{

void compute_sym_scale_zp(float min, float max, float &scaling_factor, int64_t &zp,
                          float &nudged_min, float &nudged_max);

void compute_asym_scale_zp(float min, float max, float &scaling_factor, int64_t &zp,
                           float &nudged_min, float &nudged_max);

void asymmetric_wquant_with_minmax_per_layer(CircleConst *node, float min, float max,
                                             float &scaling_factor, int64_t &zp, float &nudged_min,
                                             float &nudged_max);

void symmetric_wquant_with_minmax_per_layer(CircleConst *node, float min, float max,
                                            float &scaling_factor, int64_t &zp, float &nudged_min,
                                            float &nudged_max);

bool get_channel_dim_index(CircleConst *node, loco::TensorShape &dimension, int &channel_dim_index);

uint32_t cal_offset(loco::TensorShape &dimension, uint32_t *indices);

void propagate_concat_quantparam(luci::CircleConcatenation *concat, loco::DataType quant_type);

bool is_weights(CircleNode *node);

bool is_quantized(const CircleNode *node);

// Clone a new const node from an existing node.
// The new node has the same shape, type, contents, and qparam with 'node'
template <loco::DataType T> luci::CircleConst *clone_const_from(luci::CircleConst *node)
{
  assert(T == node->dtype());

  auto new_node = node->graph()->nodes()->create<CircleConst>();
  // TODO: We don't have any naming policy for newly created nodes yet.
  //       Fix this when we have one.
  new_node->name(node->name());
  new_node->dtype(node->dtype());
  new_node->rank(node->rank());
  for (uint32_t i = 0; i < node->rank(); i++)
    new_node->dim(i).set(node->dim(i).value());

  const auto size = node->size<T>();
  new_node->size<T>(size);
  for (uint32_t i = 0; i < size; i++)
    new_node->at<T>(i) = node->at<T>(i);

  new_node->shape_status(luci::ShapeStatus::VALID);

  if (node->quantparam() != nullptr)
  {
    auto qparam = std::make_unique<CircleQuantParam>();
    qparam->scale = node->quantparam()->scale;
    qparam->zerop = node->quantparam()->zerop;
    qparam->min = node->quantparam()->min;
    qparam->max = node->quantparam()->max;
    qparam->quantized_dimension = node->quantparam()->quantized_dimension;

    new_node->quantparam(std::move(qparam));
  }

  return new_node;
}

} // namespace luci

#endif // __LUCI_QUANTIZATION_UTILS_H__
