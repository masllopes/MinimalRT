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
 * @file    SCH_FI_Sync_Task.c
 * @author  Marco Lopes
 * @brief   Provides a place holder for the synchronization event task.
 *
 * @param   None
 * @return  void
 */

/*-------------- Required interfaces --------------*/
#include "SCH_TI_Device.h"
#include "SCH_CI_User_Config.h"
#include "SCH_TI.h"


/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_Sync_Task.h"

/* ---------- Local operations prototypes ----------*/
static inline void SCH_FL_Sync_Task_Prologue(void);

/* -------------- Provided operations --------------*/
void SCH_FI_Sync_Task(void)
{

    /* Perform the sync prologue, handling systick and jumping to the first cyclic task*/
    SCH_FL_Sync_Task_Prologue();
}

void SCH_FL_Sync_Task_Prologue(void)
{
    /* Reset the Systick counter to zero, setting the new zero time reference and
    update the reload value for the quanta ticks without offset, which will kick-in
    after from the second Systick interrupt onwards */
    SysTick->VAL = 0;
    SysTick->CTRL |= STRCTRL_INT_EN;
    SysTick->LOAD = SCH_QUANTA_TICKS;
}
