/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

/**
 * @file cyphal.h
 * @author d.ponomarev
 * @date Dec 28, 2021
 */

#ifndef LIBCYPHAL_CYPHAL_REGISTERS_HPP_
#define LIBCYPHAL_CYPHAL_REGISTERS_HPP_

#include "cyphal_subscribers.hpp"
#include "uavcan/_register/Access_1_0.h"
#include "uavcan/_register/List_1_0.h"

enum class RegistersIndexes {
    ID = 0,
    SETPOINT_ID,
    READINESS_ID,
    PWM_1_CHANNEL,
    PWM_2_CHANNEL,
    INTEGER_AMOUNT,
};

struct RegisterListRequest: public CyphalSubscriber {
    RegisterListRequest(Cyphal* driver_, CanardPortID port_id_) : CyphalSubscriber(driver_, port_id_) {};
    void callback(const CanardRxTransfer& transfer) override;
private:
    uint16_t parseRequest(const CanardRxTransfer& transfer);
    void makeResponse(const CanardRxTransfer& transfer, uint16_t index);
};

struct RegisterAccessRequest: public CyphalSubscriber {
    RegisterAccessRequest(Cyphal* driver_, CanardPortID port_id_) : CyphalSubscriber(driver_, port_id_) {};
    void callback(const CanardRxTransfer& transfer) override;
private:
    uint16_t parseRequest(const CanardRxTransfer& transfer);
    void makeResponse(const CanardRxTransfer& transfer, int8_t reg_index);
    uavcan_register_Access_Request_1_0 _request_msg;
};


#endif  // LIBCYPHAL_CYPHAL_REGISTERS_HPP_
