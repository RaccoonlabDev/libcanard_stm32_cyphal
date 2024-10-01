/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2024 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef UDRAL_FEEDBACK_HPP_
#define UDRAL_FEEDBACK_HPP_

#include "cyphalNode/cyphal.hpp"
#include "reg/udral/service/actuator/common/Feedback_0_1.h"

namespace udral {

struct FeedbackPublisher: public cyphal::CyphalPublisher {
    FeedbackPublisher() = default;

    inline void publish() {
        uint8_t buffer[reg_udral_service_actuator_common_Feedback_0_1_EXTENT_BYTES_];
        size_t size = reg_udral_service_actuator_common_Feedback_0_1_EXTENT_BYTES_;
        int32_t res = reg_udral_service_actuator_common_Feedback_0_1_serialize_(&msg, buffer, &size);
        if (NUNAVUT_SUCCESS == res) {
            push(size, buffer);
        }
    }

    reg_udral_service_actuator_common_Feedback_0_1 msg;
};


}  // namespace udral

#endif  // UDRAL_FEEDBACK_HPP_
