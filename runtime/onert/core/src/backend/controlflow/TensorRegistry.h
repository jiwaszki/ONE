/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// This file will be removed or unified with backend/cpu/TensorRegistry.h

#ifndef __ONERT_BACKEND_CPU_TENSOR_REGISTRY__
#define __ONERT_BACKEND_CPU_TENSOR_REGISTRY__

#include "ir/OperandIndexMap.h"
#include "backend/ITensorRegistry.h"
#include "operand/Tensor.h"

#include <memory>

namespace onert
{
namespace backend
{
namespace controlflow
{

class TensorRegistry : public ITensorRegistry,
                       public ir::OperandIndexMap<std::shared_ptr<operand::Tensor>>
{
public:
  /**
   * @brief Returns pointer of ITensor
   * @note  Returned tensor cannot be used longer than dynamic tensor manager
   */
  std::shared_ptr<ITensor> getITensor(const ir::OperandIndex &ind) override { return at(ind); }
};

} // namespace controlflow
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_CPU_TENSOR_REGISTRY__
