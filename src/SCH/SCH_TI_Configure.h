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
 * @file    SCH_TI_Configure.h
 * @author  Marco Lopes
 * @brief   Scheduler user configurations.
 *
 *          Scheduler configuration data types.
 */

#ifndef SCH_TI_CONFIGURE_H
#define SCH_TI_CONFIGURE_H

/*-------------- Required interfaces --------------*/
#include "COM_TE_Types.h"

/*-------------- Provided interfaces --------------*/
#include "SCH_TI_Configure.h"

/*-------------------- Provided data types ----------------------------*/
/* Task configuration */
typedef struct
{
    t_uint32 id;
    t_uint32 period_quanta;
    void (*pt_function)(void);
} t_sch_task_configure;


#endif /* SCH_TI_CONFIGURE_H */
