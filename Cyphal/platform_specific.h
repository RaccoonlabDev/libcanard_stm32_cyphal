/*
 * Copyright (C) 2024 Dmitry Ponomarev <ponomarevda96@gmail.com>
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CYPHAL_PLATFORM_SPECIFIC_H_
#define CYPHAL_PLATFORM_SPECIFIC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @return the time in milliseconds since the application started.
  * @note This function must be provided by a user!
  */
uint32_t platformSpecificGetTimeMs();

/**
  * @return whether the request will be processed
  * True  - the application will be restarted soon.
  * False - the restarted is not supported or can't be handled at the moment.
  * @note Implementation is recommended, but optional.
  */
bool platformSpecificRequestRestart();

/**
  * @param[out] out_id - hardware Unique ID
  * @note Implementation is recommended, but optional.
  */
void platformSpecificReadUniqueID(uint8_t out_uid[16]);

#ifdef __cplusplus
}
#endif

#endif  // CYPHAL_PLATFORM_SPECIFIC_H_
