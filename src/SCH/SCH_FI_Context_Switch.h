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
 * @file    SCH_FI_Context_Switch.h
 * @author  Marco Lopes
 * @brief   When a new SCH_FI_Context_Switch (systick) interrupt service routine is
 *          entered, the callee saved registers are automatically pushed by HW, the
 *          context switch code then pushes the caller saved registers, in order to save
 *          the context of whatever task is being excuted at the time of the interrupt.
 *
 *          Then using the data in V_SCH it gets the SP to the next task to be executed
 *          and it pops the caller saved registers in order to start restoring the
 *          context of the next task. It also sets the PRIMASK in order to allow other
 *          interrupts to interrupt the cyclic tasks based on the priority configurable
 *          via the SCH_CYCLIC_TASK_BASE_PRI constant parameter.
 *
 *          When the interrupt service routine is left the HW automatically pops the
 *          callee saved registers, completing the restoring of the context of the next
 *          task and branching to where the PC of the new context points to.
 *
 *          When popping to the CPU register the SP increments, when push to the stack
 *          SP decrements.
 *
 *          For sake of simplicity, the lazy context save of FP state feauture of the
 *          cortex cores is used, and the code always stores the FPU context, even if
 *          the FPU is not used.
 *
 * @param   None
 * @return  void
 */

#ifndef SCH_FI_Context_Switch_H
#define SCH_FI_Context_Switch_H

/*-------------------------------- Required interfaces ---------------------------------*/

/*--------------------------- Provided operations prototypes ---------------------------*/

__attribute__((naked)) void SCH_FI_Context_Switch(void);

#endif /* SCH_FI_Context_Switch_H */
