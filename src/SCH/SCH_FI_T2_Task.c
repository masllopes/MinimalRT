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
 * @file    SCH_FI_T2_Task.c
 * @author  Marco Lopes
 * @brief   T2 Task.
 *
 * @param   None
 * @return  void
 */

/*-------------- Required interfaces --------------*/
#include "SCH_FI_Task_Yield.h"
#include "COM_TE_Types.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_T2_Task.h"

/* -------------- Provided operations --------------*/

void SCH_FI_T2_Task(void)
{


   /* Terminate this instance of the task */
   SCH_FI_Task_Yield();
}
