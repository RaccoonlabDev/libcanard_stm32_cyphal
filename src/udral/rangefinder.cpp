/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "cyphalNode/udral/rangefinder.hpp"

namespace cyphal {

void RangefinderRangePublisher::publish(float range) {
    if (!isEnabled()) {
        return;
    }

    uavcan_si_sample_length_Scalar_1_0 msg;
    msg.timestamp.microsecond = 0;
    msg.meter = range;

    static uint8_t buffer[uavcan_si_sample_length_Scalar_1_0_EXTENT_BYTES_];
    size_t buffer_size = uavcan_si_sample_length_Scalar_1_0_EXTENT_BYTES_;
    int32_t result = uavcan_si_sample_length_Scalar_1_0_serialize_(&msg, buffer, &buffer_size);
    if (NUNAVUT_SUCCESS == result) {
        push(buffer_size, buffer);
    }
}

}  // namespace cyphal
