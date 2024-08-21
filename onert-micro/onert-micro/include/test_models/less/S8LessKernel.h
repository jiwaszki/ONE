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

#ifndef ONERT_MICRO_TEST_MODELS_LESS_KERNEL_S8_H
#define ONERT_MICRO_TEST_MODELS_LESS_KERNEL_S8_H

#include "TestDataLessBase.h"

namespace onert_micro
{
namespace test_model
{
namespace less_s8_with_no_broadcasting
{

/*
 * Less Kernel:
 *
 * Input_1(1, 1, 4, 3)   Input_2(1, 1, 4, 3)
 * scale: 0.0078431373   scale: 0.008431373
 *       \             /
 *     Less(no broadcast)
 *              |
 *          Output(1, 1, 4, 3)
 */

const unsigned char test_kernel_model_circle[] = {

  0x1c, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
  0x00, 0x14, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x2c,
  0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x88, 0xff, 0xff, 0xff, 0x8c, 0xff, 0xff,
  0xff, 0x90, 0xff, 0xff, 0xff, 0x94, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08,
  0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x07,
  0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x10, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0xcc, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14,
  0x00, 0x10, 0x00, 0x0f, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00,
  0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x6f, 0x66, 0x6d, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x8a, 0xff, 0xff,
  0xff, 0x14, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x09, 0x4c, 0x00, 0x00, 0x00, 0x7c, 0xff, 0xff, 0xff, 0x30, 0x00, 0x00, 0x00, 0x24,
  0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0xbe, 0x23, 0x0a, 0x3c, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x42, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x04, 0x00, 0x00, 0x00, 0x69, 0x66, 0x6d, 0x32, 0x00,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14,
  0x00, 0x13, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x54,
  0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00,
  0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x81, 0x80, 0x00, 0x3c, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xfe, 0x42, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x04, 0x00, 0x00, 0x00,
  0x69, 0x66, 0x6d, 0x31, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a,
  0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e, 0x45, 0x2d, 0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32,
  0x63, 0x69, 0x72, 0x63, 0x6c, 0x65, 0x00, 0x00, 0x00

};
const std::vector<int8_t> input1_data = {36, 4, 49, 84, 22, 40, 74, 97, 25, 26, 69, 37};

const std::vector<int8_t> input2_data = {66, 62, 58, 89, 2, 29, 37, 88, 64, 83, 73, 33};

const std::vector<bool> reference_output_data = {true,  true,  true, true, false, false,
                                                 false, false, true, true, true,  false};

} // namespace less_s8_with_no_broadcasting

namespace neg_less_s8_with_no_broadcasting
{

/*
 * Less Kernel with input type mismatch:
 *
 * Input_1(1, 2, 2, 3) INT8   Input_2(1, 2, 2, 3) UINT8
 *       \             /
 *     Less(no broadcast)
 *              |
 *          Output(1, 2, 2, 3)
 */

const unsigned char test_kernel_model_circle[] = {
  0x1c, 0x00, 0x00, 0x00, 0x43, 0x49, 0x52, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x10, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x2c, 0x02, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x88, 0xff, 0xff, 0xff, 0x8c, 0xff, 0xff, 0xff, 0x90, 0xff, 0xff, 0xff,
  0x94, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
  0x6c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29,
  0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0xcc, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00,
  0x10, 0x00, 0x0f, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x6f, 0x66, 0x6d, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x8a, 0xff, 0xff, 0xff, 0x14, 0x00, 0x00, 0x00,
  0x4c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x4c, 0x00, 0x00, 0x00,
  0x7c, 0xff, 0xff, 0xff, 0x30, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xbe, 0x23, 0x0a, 0x3c, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x69, 0x66, 0x6d, 0x32, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
  0x18, 0x00, 0x14, 0x00, 0x13, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09,
  0x54, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x81, 0x80, 0x00, 0x3c, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x42,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x04, 0x00, 0x00, 0x00, 0x69, 0x66, 0x6d, 0x31,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x11, 0x00, 0x00, 0x00, 0x4f, 0x4e, 0x45, 0x2d,
  0x74, 0x66, 0x6c, 0x69, 0x74, 0x65, 0x32, 0x63, 0x69, 0x72, 0x63, 0x6c, 0x65, 0x00, 0x00, 0x00};
const std::vector<int8_t> input1_data = {36, 4, 49, 84, 22, 40, 74, 97, 25, 26, 69, 37};

const std::vector<int8_t> input2_data = {66, 62, 58, 89, 2, 29, 37, 88, 64, 83, 73, 33};

const std::vector<bool> reference_output_data = {true,  true,  true, true, false, false,
                                                 false, false, true, true, true,  false};

} // namespace neg_less_s8_with_no_broadcasting

class TestDataS8Less : public TestDataLessBase<int8_t, bool>
{
public:
  explicit TestDataS8Less(bool is_with_broadcast, bool is_neg)
    : TestDataLessBase<int8_t, bool>(is_with_broadcast)
  {
    if (is_with_broadcast)
    {
      assert(false && "Not impl yet");
    }
    else
    {
      if (is_neg)
      {
        _input1_data = neg_less_s8_with_no_broadcasting::input1_data;
        _input2_data = neg_less_s8_with_no_broadcasting::input2_data;
        _reference_output_data = neg_less_s8_with_no_broadcasting::reference_output_data;
        _test_kernel_model_circle = neg_less_s8_with_no_broadcasting::test_kernel_model_circle;
      }
      else
      {
        _input1_data = less_s8_with_no_broadcasting::input1_data;
        _input2_data = less_s8_with_no_broadcasting::input2_data;
        _reference_output_data = less_s8_with_no_broadcasting::reference_output_data;
        _test_kernel_model_circle = less_s8_with_no_broadcasting::test_kernel_model_circle;
      }
    }
  }

  ~TestDataS8Less() override = default;
};

} // namespace test_model
} // namespace onert_micro

#endif // ONERT_MICRO_TEST_MODELS_LESS_KERNEL_QUANT_H
