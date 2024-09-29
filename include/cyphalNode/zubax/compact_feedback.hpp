/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef ZUBAX_COMPACT_FEEDBACK_HPP_
#define ZUBAX_COMPACT_FEEDBACK_HPP_

#include "cyphalNode/cyphal.hpp"
#include "cyphalNode/cyphal_publishers.hpp"

namespace zubax::telega {

struct CompactFeedback {
    float dc_voltage;
    float dc_current;
    float phase_current_amplitude;
    int32_t velocity;
    int8_t demand_factor_pct;
};

// https://telega.zubax.com/interfaces/cyphal.html#compact
#pragma pack(push, 1)
struct RawCompactFeedback {
    uint32_t dc_voltage             : 11;
    int32_t dc_current              : 12;
    int32_t phase_current_amplitude : 12;
    int32_t velocity                : 13;
    int8_t demand_factor_pct        : 8;
};
#pragma pack(pop)

struct CompactFeedbackPublisher: public cyphal::CyphalPublisher {
    CompactFeedbackPublisher() = default;

    inline void publish() {
        constexpr size_t zubax_telega_CompactFeedback_0_1_SERIALIZATION_BUFFER_SIZE_BYTES = 7;
        constexpr float RPM_TO_RAD_PER_SEC = 0.1047198;
        constexpr float VOLTAGE_SERIALIZE = 5.0f;
        constexpr float CURRENT_SERIALIZE = 5.0f;

        RawCompactFeedback buffer = {
            .dc_voltage = static_cast<uint32_t>(msg.dc_voltage * VOLTAGE_SERIALIZE),
            .dc_current = static_cast<int32_t>(msg.dc_current * CURRENT_SERIALIZE),
            .phase_current_amplitude = (int32_t)(msg.phase_current_amplitude * CURRENT_SERIALIZE),
            .velocity = static_cast<int32_t>(msg.velocity * RPM_TO_RAD_PER_SEC),
            .demand_factor_pct = msg.demand_factor_pct,
        };

        push(zubax_telega_CompactFeedback_0_1_SERIALIZATION_BUFFER_SIZE_BYTES, (const uint8_t*)&buffer);
    }

    CompactFeedback msg;
};

}  // namespace zubax::telega

#endif  // ZUBAX_COMPACT_FEEDBACK_HPP_
