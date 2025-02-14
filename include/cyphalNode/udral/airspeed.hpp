/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef UDRAL_AIRSPEED_HPP_
#define UDRAL_AIRSPEED_HPP_

#include "cyphalNode/cyphal.hpp"
#include "uavcan/si/sample/pressure/Scalar_1_0.h"

namespace cyphal {

struct DiffPressurePublisher: public CyphalPublisher {
    DiffPressurePublisher(Cyphal* driver_, CanardPortID port_id) : CyphalPublisher(driver_, port_id) {};
    void publish(float pressure);
};

}  // namespace cyphal

#endif  // UDRAL_AIRSPEED_HPP_
