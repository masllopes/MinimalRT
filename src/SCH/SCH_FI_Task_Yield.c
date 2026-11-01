/* SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2025 Marco Lopes
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
 * @file    SCH_FI_Task_Yield.c
 * @author  Marco Lopes
 * @brief   Yields the task execution, by updating the task state and statistics and
 *          triggering a context switch to the next task.
 *
 * @param   None
 * @return  void
 */

/*-------------- Required interfaces --------------*/
#include "SCH_TI_Device.h"
#include "SCH_TI.h"
#include "SCH_VI.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_Task_Yield.h"

/* -------------- Provided operations --------------*/

inline void SCH_FI_Task_Yield(void)
{
    /* Indicate the end of execution of the task */
    V_SCH.tasks[V_SCH.current_task_id].state = TASK_STATE_FINISHED;
    V_SCH.tasks[V_SCH.current_task_id].execution_nb++;

    /* Set the execution of PendSV to pending */
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    __ISB(); /* Instruction Synchronization Barrier */
    __DSB(); /* Data Synchronization Barrier */

    return;
}
