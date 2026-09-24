
/*****************************************************************************************
 * @file    SCH_CI_User_Config.h
 *
 * @brief   Scheduler configurations.
 ******************************************************************************************
 *  Version  | Date       | Author     | Description
 ******************************************************************************************
 *  1.0      | 24/06/2025 | M. Lopes   | Initial revision.
 ******************************************************************************************
 */

/*-------------------------------- Required interfaces ---------------------------------*/
#include "SCH_FI_BG_Task.h"
#include "SCH_FI_T1_Task.h"
#include "SCH_FI_T2_Task.h"

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "SCH_CI_User_Config.h"

/*-------------------------------- User configurations ---------------------------------*/

/****************************************************************************************/
/*                                  Task configuration                                  */
/****************************************************************************************/

/* Task period constants */
/* The periods should be equal or larger than the scheduler quanta SCH_QUANTA_US
and for an accurate timing it shall be equal to an integer multiple of the quanta (x*SCH_QUANTA_US) */
#define T1_TASK_PERIOD_US SCH_QUANTA_US // Equal to the scheduler quanta period
#define T2_TASK_PERIOD_US 1000U         // (2KHz)

/* For each task, defined in order of increasing period, the following fields have to be defined:
 - id: unique identifier for the task in growing order of task period, with 0 corresponding to the background task
 - period_us: cyclic task execution period in microseconds
 - pt_function: pointer to the task function to be executed                                                        */


const t_sch_task_configure C_SCH_TASK_CONFIGS[] =
    {
        {.id = 0, .period_us = 0U, .pt_function = &SCH_FI_BG_Task},
        {.id = 1, .period_us = T1_TASK_PERIOD_US, .pt_function = &SCH_FI_T1_Task},
        {.id = 2, .period_us = T2_TASK_PERIOD_US, .pt_function = &SCH_FI_T2_Task}};

/*----------------------------------- Provided data ------------------------------------*/

#define NVIC_PRIO_BITS 4U // Number of priority bits of the processor

/* Global constant holding the priority of interrupts allowed to interrupt
 * foreground tasks, initialized with CYCLIC_TASK_PRIMASK macro to be used
 by assembly code. Do not modify this. */

const t_uint32 C_SCH_CYCLIC_TASK_BASEPRI = (SCH_CYCLIC_TASK_BASE_PRI) << (8U - NVIC_PRIO_BITS);