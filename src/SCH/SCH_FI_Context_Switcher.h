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
 * @file    SCH_FI_Context_Switcher.h
 * @author  Marco Lopes
 * @brief   Performs a manual context switch by manipulating the stack to store the
 *          current context and restore the one pointed to by V_SCH. For sake of
 *          simplicity it always stores the FPU context, even if the FPU is not used.
 *
 * @param   None
 * @return  void
 */

#ifndef SCH_FI_CONTEXT_SWITCHER_H
#define SCH_FI_CONTEXT_SWITCHER_H

/*-------------- Required interfaces --------------*/

/* -------------- Provided operations prototypes --------------*/

__attribute__((naked)) void SCH_FI_Context_Switcher(void);

#endif /* SCH_FI_CONTEXT_SWITCHER_H */
