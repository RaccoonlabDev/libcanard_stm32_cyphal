/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2023 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#ifndef ZUBAX_COMPACT_FEEDBACK_HPP_
#define ZUBAX_COMPACT_FEEDBACK_HPP_

#include "cyphalNode/cyphal.hpp"
#include "cyphalNode/cyphal_publishers.hpp"

namespace zubax::telega {

// https://telega.zubax.com/interfaces/cyphal.html#compact
#pragma pack(push, 1)
struct CompactFeedback {
    uint32_t dc_voltage             : 11;
    int32_t dc_current              : 12;
    int32_t phase_current_amplitude : 12;
    int32_t velocity                : 13;
    int8_t demand_factor_pct        : 8;
};
#pragma pack(pop)

struct CompactFeedbackPublisher: public cyphal::CyphalPublisher {
    CompactFeedbackPublisher() : cyphal::CyphalPublisher(cyphal::Cyphal::get_instance(), 65535) { }
    void publish(const CompactFeedback& msg);
    static constexpr float RPM_TO_RAD_PER_SEC = 0.1047198;
private:
    static constexpr size_t zubax_telega_CompactFeedback_0_1_SERIALIZATION_BUFFER_SIZE_BYTES = 7;
};

}  // namespace zubax::telega

#endif  // ZUBAX_COMPACT_FEEDBACK_HPP_
