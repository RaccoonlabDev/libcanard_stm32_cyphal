/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "cyphalNode/udral/actuator.hpp"
#include "params.hpp"

namespace cyphal {

SetpointSubscriber::SetpointSubscriber(Cyphal* driver_) :
    CyphalSubscriber(driver_, 0) {
}

int8_t SetpointSubscriber::init() {
    port_id = paramsGetIntegerValue(IntParamsIndexes::SETPOINT_ID);
    if (driver->subscribe(this,
                reg_udral_service_actuator_common_sp_Vector31_0_1_EXTENT_BYTES_,
                CanardTransferKindMessage) < 0) {
        return -1;
    }

    return 0;
}

void SetpointSubscriber::callback(const CanardRxTransfer& transfer) {
    auto payload = static_cast<const uint8_t*>(transfer.payload);
    size_t payload_len = transfer.payload_size;
    reg_udral_service_actuator_common_sp_Vector31_0_1_deserialize_(&msg, payload, &payload_len);
    _setpoint_size = payload_len / 2;
    _recv_counter++;
}

const reg_udral_service_actuator_common_sp_Vector31_0_1& SetpointSubscriber::get_setpoint() const {
    return msg;
}

uint32_t SetpointSubscriber::get_recv_counter() const {
    return _recv_counter;
}

void SetpointSubscriber::clear_recv_counter() {
    _recv_counter = 0;
}


ReadinessSubscriber::ReadinessSubscriber(Cyphal* driver_) :
    CyphalSubscriber(driver_, 0) {
}

int8_t ReadinessSubscriber::init() {
    port_id = paramsGetIntegerValue(IntParamsIndexes::READINESS_ID);
    msg.value = reg_udral_service_common_Readiness_0_1_STANDBY;
    if (driver->subscribe(this,
                reg_udral_service_common_Readiness_0_1_EXTENT_BYTES_,
                CanardTransferKindMessage) < 0) {
        return -1;
    }

    return 0;
}

uint8_t ReadinessSubscriber::get_readiness() {
    if (_last_recv_time_ms == 0 || platformSpecificGetTimeMs() > _last_recv_time_ms + 500) {
        return reg_udral_service_common_Readiness_0_1_SLEEP;
    }

    return msg.value;
}

void ReadinessSubscriber::callback(const CanardRxTransfer& transfer) {
    auto payload = static_cast<const uint8_t*>(transfer.payload);
    size_t payload_len = transfer.payload_size;
    reg_udral_service_common_Readiness_0_1_deserialize_(&msg, payload, &payload_len);
    _last_recv_time_ms = platformSpecificGetTimeMs();
}

}  // namespace cyphal
