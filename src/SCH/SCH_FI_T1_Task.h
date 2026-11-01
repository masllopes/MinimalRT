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
 * @file    SCH_FI_T1_Task.h
 * @author  Marco Lopes
 * @brief   T1 Task.
 *
 * @param   None
 * @return  void
 */

#ifndef SCH_FI_T1_TASK_H
#define SCH_FI_T1_TASK_H

/*-------------- Required interfaces --------------*/

/* -------------- Provided operations prototypes --------------*/

__attribute__((naked)) void SCH_FI_T1_Task(void); /* This function is naked in order to allow a correct manual context switching into it */

#endif /* SCH_FI_T1_TASK_H */
