/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "cyphalNode/udral/barometer.hpp"
#include "cyphalNode/cyphal.hpp"
#include "params.hpp"

namespace cyphal {

BaroPressurePublisher::BaroPressurePublisher() :
    CyphalPublisher(Cyphal::get_instance(), 65535) { }

void BaroPressurePublisher::publish(const uavcan_si_sample_pressure_Scalar_1_0& msg) {
    static uint8_t buffer[uavcan_si_sample_pressure_Scalar_1_0_EXTENT_BYTES_];
    size_t buffer_size = uavcan_si_sample_pressure_Scalar_1_0_EXTENT_BYTES_;
    int32_t result = uavcan_si_sample_pressure_Scalar_1_0_serialize_(&msg, buffer, &buffer_size);
    if (NUNAVUT_SUCCESS == result) {
        push(buffer_size, buffer);
    }
}

BaroTemperaturePublisher::BaroTemperaturePublisher() :
    CyphalPublisher(Cyphal::get_instance(), 65535) { }

void BaroTemperaturePublisher::publish(const uavcan_si_sample_temperature_Scalar_1_0& msg) {
    static uint8_t buffer[uavcan_si_sample_temperature_Scalar_1_0_EXTENT_BYTES_];
    size_t buffer_size = uavcan_si_sample_temperature_Scalar_1_0_EXTENT_BYTES_;
    int32_t result = uavcan_si_sample_temperature_Scalar_1_0_serialize_(&msg, buffer, &buffer_size);
    if (NUNAVUT_SUCCESS == result) {
        push(buffer_size, buffer);
    }
}

}  // namespace cyphal
