/* SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2026 Marco Lopes
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
 * @file    SCH_FE_Phase_Shift.h
 * @author  Marco Lopes
 * @brief   Updates the Systick reload value in order to offset the Systick timer by a
 *          given amount of time, in microseconds. SCH_FI_Task_Manager will then reset
 *          the reload value to the original one, so that the period is kept.
 *
 * @param   in_offset_us: Offset in microseconds to be applied to the Systick timer for
 *          the next cycle.
 * @return  Returns TRUE if the offset was successfully applied, FALSE otherwise.
 */

#ifndef SCH_FE_PHASE_SHIFT_H
#define SCH_FE_PHASE_SHIFT_H

/*-------------------------------- Required interfaces ---------------------------------*/
#include "SCH_CI_User_Config.h"
/*-------------------------------- Provided interfaces ---------------------------------*/
#include "SCH_FE_Phase_Shift.h"

/*--------------------------- Provided operations prototypes ---------------------------*/
#if SCH_PH_SHIFT_ENABLE
    t_bool SCH_FE_Phase_Shift(t_float32 in_offset_us);
#endif /* SCH_PH_SHIFT_ENABLE */

#endif /* SCH_FE_PHASE_SHIFT_H */
