/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef UDRAL_MAGNETOMETER_HPP_
#define UDRAL_MAGNETOMETER_HPP_

#include "cyphal.hpp"
#include "uavcan/si/sample/magnetic_field_strength/Vector3_1_1.h"

namespace cyphal::udral {

struct MagneticFieldPublisher: public CyphalPublisher {
    MagneticFieldPublisher() : CyphalPublisher(Cyphal::get_instance(), 65535) {}
    void publish(const uavcan_si_sample_magnetic_field_strength_Vector3_1_1& msg);
};

}  // namespace cyphal::udral

#endif  // UDRAL_MAGNETOMETER_HPP_
