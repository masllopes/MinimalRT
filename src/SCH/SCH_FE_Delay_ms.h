/* SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2025-2026 Marco Lopes
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file    SCH_FE_Delay_ms.h
 * @author  Marco Lopes
 * @brief   Provides the capability of performing a delay/busy wait, specified in
 *          milliseconds.
 *
 * @param   IN_delay_ms: The delay duration in milliseconds.
 * @return  void
 */

#ifndef SCH_FE_DELAY_MS_H
#define SCH_FE_DELAY_MS_H

/*-------------------------------- Required interfaces ---------------------------------*/
#include "COM_TE_Types.h"

/*--------------------------- Provided operations prototypes ---------------------------*/

void SCH_FE_Delay_ms(t_uint64 delay_ms);

/*----------------------------- Provided define constants ------------------------------*/

#endif /* SCH_FE_DELAY_MS_H */
