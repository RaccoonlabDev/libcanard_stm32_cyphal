/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef UDRAL_ACTUATOR_HPP_
#define UDRAL_ACTUATOR_HPP_

#include "cyphalNode/cyphal.hpp"
#include "reg/udral/service/actuator/common/sp/Scalar_0_1.h"
#include "reg/udral/service/actuator/common/sp/Vector31_0_1.h"
#include "reg/udral/service/common/Readiness_0_1.h"

namespace cyphal {

struct SetpointSubscriber: public CyphalSubscriber {
    SetpointSubscriber(Cyphal* driver);
    int8_t init();
    void callback(const CanardRxTransfer& transfer) override;
    const reg_udral_service_actuator_common_sp_Vector31_0_1& get_setpoint() const;
    uint8_t get_setpoint_size() const {return _setpoint_size;};
    uint32_t get_recv_counter() const;
    void clear_recv_counter();
private:
    reg_udral_service_actuator_common_sp_Vector31_0_1 msg = {};
    uint32_t _recv_counter{0};
    uint8_t _setpoint_size{0};
};


struct ReadinessSubscriber: public CyphalSubscriber {
    ReadinessSubscriber(Cyphal* driver_);
    int8_t init();
    uint8_t get_readiness();
private:
    void callback(const CanardRxTransfer& transfer) override;
    reg_udral_service_common_Readiness_0_1 msg = {};
    uint32_t _last_recv_time_ms{0};
};

}  // namespace cyphal

#endif  // UDRAL_ACTUATOR_HPP_
