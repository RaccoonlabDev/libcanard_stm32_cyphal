/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "cyphalNode/cyphal_subscribers.hpp"
#include "cyphalNode/cyphal.hpp"
#include "cyphalNode/algorithms.hpp"
#include "cyphalNode/platform_specific.h"
#include "params.hpp"

#ifndef GIT_HASH
    #define GIT_HASH 0xBADC0FFEE000
#endif
#if GIT_HASH == 0xBADC0FFEE000
    #warning "GIT_HASH has not been provided!"
#endif

#ifndef APP_VERSION_MAJOR
    #warning "APP_VERSION_MAJOR has been assigned to 0 by default."
    #define APP_VERSION_MAJOR   0
#endif

#ifndef APP_VERSION_MINOR
    #warning "APP_VERSION_MINOR has been assigned to 0 by default."
    #define APP_VERSION_MINOR   0
#endif

namespace cyphal {

static const auto DEFAULT_NODE_NAME = (const uint8_t*)"co.raccoonlab.unknown_node";

uavcan_node_Version_1_0 NodeGetInfoSubscriber::hw_version;

bool CyphalSubscriber::isEnabled() const {
    constexpr uint16_t MAX_PORT_ID = 8191;
    return (port_id == 0 || port_id > MAX_PORT_ID) ? false : true;
}

bool CyphalSubscriber::isService() const {
    return false;
}


NodeGetInfoSubscriber::NodeGetInfoSubscriber(Cyphal* driver_) :
        CyphalSubscriber(driver_, uavcan_node_GetInfo_1_0_FIXED_PORT_ID_) {
    get_info_response.protocol_version.major = CANARD_CYPHAL_SPECIFICATION_VERSION_MAJOR;
    get_info_response.protocol_version.minor = CANARD_CYPHAL_SPECIFICATION_VERSION_MINOR;
    get_info_response.software_version.major = APP_VERSION_MAJOR;
    get_info_response.software_version.minor = APP_VERSION_MINOR;
    get_info_response.software_vcs_revision_id = GIT_HASH;
}

void NodeGetInfoSubscriber::init() {
    get_info_response.hardware_version.major = hw_version.major;
    get_info_response.hardware_version.minor = hw_version.minor;
    get_info_response.certificate_of_authenticity.count = 0;

    platformSpecificReadUniqueID(get_info_response.unique_id);
    updateNodeName();
}

void NodeGetInfoSubscriber::updateNodeName() {
    auto param_idx = static_cast<ParamIndex_t>(IntParamsIndexes::INTEGER_PARAMS_AMOUNT);
    auto custom_name = (const uint8_t*)paramsGetStringValue(param_idx);
    auto& name = get_info_response.name;

    if (custom_name != nullptr) {
        name.count = strcpySafely(name.elements, custom_name, MAX_STRING_LENGTH);
        if (name.count != 0) {
            return;
        }
    }

    name.count = strcpySafely(name.elements, DEFAULT_NODE_NAME, MAX_STRING_LENGTH);
}

void NodeGetInfoSubscriber::callback(const CanardRxTransfer& transfer) {
    CanardTransferMetadata transfer_metadata = {
        CanardPriorityNominal,
        CanardTransferKindResponse,
        uavcan_node_GetInfo_1_0_FIXED_PORT_ID_,
        transfer.metadata.remote_node_id,
        transfer.metadata.transfer_id,
    };

    static uint8_t buffer[uavcan_node_GetInfo_Response_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_] = {};
    size_t buffer_size = uavcan_node_GetInfo_Response_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_;
    int32_t result;
    result = uavcan_node_GetInfo_Response_1_0_serialize_(&get_info_response, buffer, &buffer_size);
    if (NUNAVUT_SUCCESS == result) {
        driver->push(&transfer_metadata, buffer_size, buffer);
    }
}

void NodeGetInfoSubscriber::setHardwareVersion(uint8_t major, uint8_t minor) {
    hw_version.major = major;
    hw_version.minor = minor;
}

void NodeGetInfoSubscriber::setHardwareVersion(uavcan_node_Version_1_0 version) {
    hw_version = version;
}

bool NodeGetInfoSubscriber::isService() const {
    return true;
}

void ExecuteCommandSubscriber::callback(const CanardRxTransfer& transfer) {
    auto payload = static_cast<const uint8_t*>(transfer.payload);
    size_t payload_len = transfer.payload_size;
    uavcan_node_ExecuteCommand_Request_1_0 msg;
    if (uavcan_node_ExecuteCommand_Request_1_0_deserialize_(&msg, payload, &payload_len) < 0) {
        return;
    }

    uavcan_node_ExecuteCommand_Response_1_0 cmd_response = {};

    switch (msg.command) {
        case uavcan_node_ExecuteCommand_Request_1_0_COMMAND_RESTART:
            cmd_response.status = platformSpecificRequestRestart() ? 0 : 1;
            break;

        case uavcan_node_ExecuteCommand_Request_1_0_COMMAND_STORE_PERSISTENT_STATES:
            if (LIBPARAMS_OK == paramsSave()) {
                cmd_response.status = uavcan_node_ExecuteCommand_Response_1_0_STATUS_SUCCESS;
            } else {
                cmd_response.status = uavcan_node_ExecuteCommand_Response_1_0_STATUS_FAILURE;
            }
            break;

        case uavcan_node_ExecuteCommand_Request_1_0_COMMAND_FACTORY_RESET:
            paramsResetToDefault();
            if (LIBPARAMS_OK == paramsSave()) {
                cmd_response.status = uavcan_node_ExecuteCommand_Response_1_0_STATUS_SUCCESS;
            } else {
                cmd_response.status = uavcan_node_ExecuteCommand_Response_1_0_STATUS_FAILURE;
            }
            break;

        default:
            cmd_response.status = uavcan_node_ExecuteCommand_Response_1_0_STATUS_BAD_COMMAND;
            break;
    }

    CanardTransferMetadata transfer_metadata = {
        CanardPriorityNominal,
        CanardTransferKindResponse,
        uavcan_node_ExecuteCommand_1_0_FIXED_PORT_ID_,
        transfer.metadata.remote_node_id,
        transfer.metadata.transfer_id,
    };

    uint8_t buffer[uavcan_node_ExecuteCommand_Response_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_] = {};
    size_t buffer_size = uavcan_node_ExecuteCommand_Response_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_;
    int32_t result;
    result = uavcan_node_ExecuteCommand_Response_1_0_serialize_(&cmd_response, buffer, &buffer_size);
    if (NUNAVUT_SUCCESS == result) {
        driver->push(&transfer_metadata, buffer_size, buffer);
    }
}

bool ExecuteCommandSubscriber::isService() const {
    return true;
}

}  // namespace cyphal
