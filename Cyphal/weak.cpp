/// This software is distributed under the terms of the MIT License.
/// Copyright (c) 2022 Dmitry Ponomarev.
/// Author: Dmitry Ponomarev <ponomarevda96@gmail.com>

#include "platform_specific.h"
#include <string.h>

__attribute__((weak)) bool platformSpecificRequestRestart() {
    return false;  // because not implemented
}

__attribute__((weak)) void platformSpecificReadUniqueID(uint8_t out_uid[16]) {
    memset(out_uid, 0x00, 16);
}
