#ifndef SCH_CI_USER_CONFIG_H
#define SCH_CI_USER_CONFIG_H

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
#include "COM_TE_Types.h"

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "SCH_CI_User_Config.h"

/*-------------------------------- User configurations ---------------------------------*/

/****************************************************************************************/
/*                              Device clock parameters:                                */
/* These parameters shall be aligned with the configuration of device in order to       */
/* inform the scheduler about the clock properties on which its timing is based upon    */
/****************************************************************************************/

#define SCH_SYS_CLK_HZ 168000000.0f // System clock frequency in Hz. Used for systick configuration.

#define SCH_SYSTICK_TICK_NS (float)((1.0f / SCH_SYS_CLK_HZ) * 1E9) // Systick tick duration in ns. Used for systick configuration.

#define SCH_AUX_CLK_TICK_US 1.0f // Auxiliary clock (used for delays) tick duration in ns.

#define SCH_AUX_CLK_MAX_TICK 0xFFFFFFFF // Max ticks for auxiliary clocks. Used for delays compensation of wrap-around.

#define SCH_AUX_CLK_ONE_MS_TICKS 1000U // 1ms in auxiliary clock ticks (1/aux_clocks_tick_ns)*10E6. Used for ms delays.

#define SCH_AUX_CLK_TICKS_COUNTER ((volatile t_uint32)(TIM5->CNT)) // Specify a read access to the auxiliary clock ticks counter. Used for delays and timestamps.

/****************************************************************************************/
/*                               Scheduler parameters:                                  */
/* These parameters define the fundamental behavior and base timing of the scheduler    */
/****************************************************************************************/

#define SCH_QUANTA_US 500U // Scheduler quanta period in microseconds. Determines the fastest task execution rate.

#define SCH_TASK_NUMBER 3U // Number of scheduled tasks. Used for structures and arrays sizes.

#define SCH_TASK_STACK_SIZE 101 // Stack size per task in words. Adjust depending on nesting and data needs.

#define SCH_CYCLIC_TASK_BASE_PRI 0U // Any interrupt with a numerical priority value equal to or higher (lower prio)
                                    // can interrupt the cyclic tasks. Lower priority interrupts can only interrupt the background task.

#define SCH_START_SYNC_ENABLE 0U // If set to 1, enables the execution of the synchronization task (SCH_FI_Sync_Task) at the start of the scheduler.
                                 // This task can be used to synchronize the scheduler quanta with any kind of event, jumping to the first cyclic task
                                 // when the synchronization condition is fulfilled.
                                 //
                                 // If set to 0, the scheduler starts with the background task (SCH_FI_BG_Task) being executed and after the quanta
                                 // time has elapsed, the task manager starts managing the queue of tasks and jumps to the first cyclic task.

#define SCH_PH_SHIFT_ENABLE 0U // If set to 1, enables the phase shift management feature, which allows the scheduler to adjust the timing of tasks
                               // based on external synchronization events. This is useful for applications that require precise timing adjustments.
                               //
                               // If set to 0, the scheduler does not handle phase shifts and runs tasks based on their defined periods without adjustments.

/*-------------------------------- Provided data types ---------------------------------*/
/* Task configuration data type */
typedef struct
{
    t_uint32 id;
    t_uint32 period_us;
    void (*pt_function)(void);
} t_sch_task_configure;

/*----------------------------------- Provided data ------------------------------------*/
extern const t_sch_task_configure C_SCH_TASK_CONFIGS[]; // Array of task configurations.
extern const t_uint32 C_SCH_CYCLIC_TASK_BASEPRI;        // Base priority for cyclic tasks, used to set the base priority of interrupts that can interrupt cyclic tasks.

#endif /* SCH_CI_USER_CONFIG_H */
