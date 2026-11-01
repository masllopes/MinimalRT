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
 * @file    SCH_FI_Task_Manager.h
 * @author  Marco Lopes
 * @brief   SCH_FI_Task_Manager is executed on the systick timer. It updates the state
 *          of each task, setting them to WAIT when the tasks have to be executed.
 *
 *          Additionally, it resets the stack pointer of each task pointing it to the
 *          right place in the stack for the context switch into them, since they don't
 *          return and therefore the SP will be pointing to the end of the task by the
 *          end of its execution.
 *
 *          To allow the detection of overruns, the branching to the tasks is handled by
 *          PendSV (SCH_FI_Context_Switch).
 *
 *          This is done because otherwise, due to the lack of reentrant interrupts on
 *          ARM Cortex-M, a new instance of the Systick timer interrupt cannot preempt a
 *          previous ongoing call of the handler.
 *
 *          Therefore, if a task was to get blocked, it would not be possible to detect
 *          that with code on the systick handler. Also, if a task lasts longer than the
 *          period of systick it would lead to that same kind of blocking behavior,
 *          event if it's duration was within that task's period, and would prevent
 *          faster tasks to preempt as intended.
 *
 * @param   None
 * @return  void
 */

#ifndef SCH_FI_TASK_MANAGER_H
#define SCH_FI_TASK_MANAGER_H

/*-------------------------------- Required interfaces ---------------------------------*/

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "SCH_FI_Task_Manager.h"

/*--------------------------- Provided operations prototypes ---------------------------*/

void SCH_FI_Task_Manager(void);

#endif /* SCH_FI_TASK_MANAGER_H */
