/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __ONERT_BACKEND_TRAIN_CONFIG_H__
#define __ONERT_BACKEND_TRAIN_CONFIG_H__

#include <backend/IConfig.h>
#include <util/ITimer.h>

namespace onert
{
namespace backend
{
namespace train
{

class Config : public IConfig
{
public:
  std::string id() override { return "train"; }
  bool initialize() override;
  bool supportPermutation() override { return true; }
  bool supportDynamicTensor() override { return false; }
  bool supportFP16() override { return false; }

  std::unique_ptr<util::ITimer> timer() override { return std::make_unique<util::CPUTimer>(); }
};

} // namespace train
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_TRAIN_CONFIG_H__
