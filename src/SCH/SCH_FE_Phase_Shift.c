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
 * @file    SCH_FE_Phase_Shift.c
 * @author  Marco Lopes
 * @brief   Updates the Systick reload value in order to offset the Systick timer by a
 *          given amount of time, in microseconds. SCH_FI_Task_Manager will then reset
 *          the reload value to the original one, so that the period is kept.
 *
 * @param   in_offset_us: Offset in microseconds to be applied to the Systick timer for
 *          the next cycle.
 * @return  Returns TRUE if the offset was successfully applied, FALSE otherwise.
 */

/*-------------- Required interfaces --------------*/
#include "SCH_VI.h"
#include "SCH_TI_Device.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FE_Phase_Shift.h"

/* -------------- Provided operations --------------*/
t_bool SCH_FE_Phase_Shift(t_float32 in_offset_us)
{
    t_int32 v_offset_ticks;
    t_bool v_success = FALSE;

    /* If there is no phase shift request ongoing */
    if (V_SCH.phase_shift_state == PH_SHIFT_REQ_AVAILABLE)
    {
        __asm volatile(
            "    cpsid   i\n");

        /* Convert the offset in microseconds to systick ticks */
        v_offset_ticks = in_offset_us * 1000.0f / SCH_SYSTICK_TICK_NS;

        /* Update Systick with the respective reload value */
        SysTick->LOAD += v_offset_ticks;

        V_SCH.phase_shift_state = PH_SHIFT_ADJ_CYCLE;

        __asm volatile(
            "    cpsie   i\n");

        v_success = TRUE;
    }

    return v_success;
}
