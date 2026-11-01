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
 * @file    SCH_VI.c
 * @author  Marco Lopes
 * @brief   Scheduler global variables.
 */

/*-------------- Required interfaces ------------------*/
#include "SCH_TI.h"
#include "SCH_CI_User_Config.h"

/*-------------- Provided interfaces -------------------*/
#include "SCH_VI.h"

/* -------------- Provided Global Data --------------*/

/*Stack of each thread*/
volatile t_uint32 V_SCH_STACKS[SCH_TASK_NUMBER][SCH_TASK_STACK_SIZE];

/*Scheduler status data*/
t_sch_data V_SCH;

/* TODO: Debug variables to be removed */
t_sch_stack_frame *V_DEBUG_CURRENT_STACK_STRUCT;
