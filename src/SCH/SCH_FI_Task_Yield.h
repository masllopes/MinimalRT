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
 * @file    SCH_FI_Task_Yield.h
 * @author  Marco Lopes
 * @brief   Yields the task execution, by updating the task state and statistics and
 *          triggering a context switch to the next task.
 *
 *          Updates the scheduler data concerning a task at the end of its execution and
 *          triggers a manual context switch via PendSV.
 *
 * @param   None
 * @return  void
 */

#ifndef SCH_FI_TASK_YIELD_H
#define SCH_FI_TASK_YIELD_H

/*-------------- Required interfaces --------------*/
#include "COM_TE_TYPES.h"
#include "SCH_TI_Device.h"
#include "SCH_TI.h"
#include "SCH_VI.h"

/* -------------- Provided operations prototypes --------------*/

extern void SCH_FI_Task_Yield(void);

#endif /* SCH_FI_TASK_YIELD_H */
