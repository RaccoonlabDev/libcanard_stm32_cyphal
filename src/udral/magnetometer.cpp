/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "cyphalNode/udral/magnetometer.hpp"

namespace cyphal::udral {

void MagneticFieldPublisher::publish(const uavcan_si_sample_magnetic_field_strength_Vector3_1_1& msg) {
    static uint8_t buffer[uavcan_si_sample_magnetic_field_strength_Vector3_1_1_EXTENT_BYTES_];
    size_t buffer_size = uavcan_si_sample_magnetic_field_strength_Vector3_1_1_EXTENT_BYTES_;
    int32_t result = uavcan_si_sample_magnetic_field_strength_Vector3_1_1_serialize_(&msg, buffer, &buffer_size);
    if (NUNAVUT_SUCCESS == result) {
        push(buffer_size, buffer);
    }
}

}  // namespace cyphal::udral
