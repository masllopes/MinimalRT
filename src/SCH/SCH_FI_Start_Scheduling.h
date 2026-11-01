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
 * @file    SCH_FI_Start_Scheduling.h
 * @author  Marco Lopes
 * @brief   Sets the CPU to use the PSP stack pointer instead of MSP, initializes the
 *          CPU registers and branches to the background task and enables interrupts, to
 *          start the cyclic scheduling of tasks.
 *
 * @param   None
 * @return  void
 */

#ifndef SCH_FI_START_SCHEDULING_H
#define SCH_FI_START_SCHEDULING_H

/*-------------------------------- Required interfaces ---------------------------------*/

/*--------------------------- Provided operations prototypes ---------------------------*/

void SCH_FI_Start_Scheduling(void);

#endif /* SCH_FI_START_SCHEDULING_H */
