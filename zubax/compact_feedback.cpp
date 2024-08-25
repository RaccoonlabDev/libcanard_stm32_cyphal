/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2024 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "compact_feedback.hpp"
#include "main.h"
#include "params.hpp"

namespace zubax::telega {

void CompactFeedbackPublisher::publish(const CompactFeedback& msg) {
    push(zubax_telega_CompactFeedback_0_1_SERIALIZATION_BUFFER_SIZE_BYTES, (const uint8_t*)&msg);
}

}  // namespace zubax::telega
