
/*************************************************************************************
 * @file    SCH_CI_User_Config.h
 *
 * @brief   Scheduler configurations.
 **************************************************************************************
 *  Version  | Date       | Author     | Description
 **************************************************************************************
 *  1.0      | 24/06/2025 | M. Lopes   | Initial revision.
 **************************************************************************************
 */

/*--------------- Required interfaces ------------------*/
#include "SCH_FI_BG_Task.h"
#include "SCH_FI_T1_Task.h"
#include "SCH_FI_T2_Task.h"
#include "SCH_TI_Configure.h"

/*--------------- Provided interfaces ------------------*/
#include "SCH_CI_User_Config.h"

/*---------------- Provided data -----------------------*/

/* Global constant holding the priority of interrupts allowed to interrupt
 * foreground tasks, initialized with CYCLIC_TASK_PRIMASK macro to be used
 by assembly code. Do not modify this. */
const t_uint32 C_SCH_CYCLIC_TASK_BASEPRI = (SCH_CYCLIC_TASK_BASE_PRI) << (8U - 3U);

/*--------------- User configurations -------------------*/

/********************************************************/
/*                 Task configuration                   */
/********************************************************/

/* Task period constants */
#define T1_TASK_PERIOD_US SCH_QUANTA_US // Equal to the scheduler quanta
#define T2_TASK_PERIOD_US 1000U         // Equal to 1ms

/* For each task, the following fields have to be defined:
 - id: unique identifier for the task in growing order of task period, with 0 corresponding to the background task
 - period_quanta: number of scheduler quanta between task executions
 - pt_function: pointer to the task function to be executed  */

const t_sch_task_configure C_SCH_TASK_CONFIGS[] =
    {
        {.id = 0, .period_quanta = 0U, .pt_function = &SCH_FI_BG_Task},
        {.id = 1, .period_quanta = T1_TASK_PERIOD_US / SCH_QUANTA_US, .pt_function = &SCH_FI_T1_Task},
        {.id = 2, .period_quanta = T2_TASK_PERIOD_US / SCH_QUANTA_US, .pt_function = &SCH_FI_T2_Task}
    };
