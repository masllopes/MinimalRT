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

#ifndef SCH_CI_CONFIGURE_H
#define SCH_CI_CONFIGURE_H

/*--------------- Required interfaces -------------*/
#include "COM_TE_Types.h"
#include "SCH_TI_Configure.h"

/*-------------- Provided interfaces --------------*/
#include "SCH_CI_User_Config.h"

/*---------------- Provided data -----------------*/
extern const t_sch_task_configure C_SCH_TASK_CONFIGS[]; // Array of task configurations.
extern const t_uint32 C_SCH_CYCLIC_TASK_BASEPRI;        // Base priority for cyclic tasks, used to set the base priority of interrupts that can interrupt cyclic tasks.

/*--------------- User configurations -------------------*/

/********************************************************/
/*                  Device parameters                   */
/********************************************************/

/* These parameters shall be aligned with the clock
and timer configurations of the device */
#define SCH_SYS_CLK_HZ 84000000.0f                                 // System clock frequency in Hz. Used for systick configuration.
#define SCH_SYSTICK_TICK_NS (float)((1.0f / SCH_SYS_CLK_HZ) * 1E9) // Systick tick duration in ns. Used for systick configuration.
#define SCH_AUX_CLK_TICK_NS 1000.0f                                // Auxiliary clock (used for delays) tick duration in ns.
#define SCH_AUX_CLK_MAX_TICK 4294967295U                           // Max ticks for auxiliary clocks. Used for delays compensation of wrap-around.
#define SCH_AUX_CLK_ONE_MS_TICKS 3750U                             // 1ms in auxiliary clock ticks (1/aux_clocks_tick_ns)*10E6. Used for ms delays.
#define SCH_AUX_CLK_TICKS_COUNTER ((volatile)(TIM5->CNT))                      // Specify a read access to the auxiliary clock ticks counter. Used for delays and timestamps.

/********************************************************/
/*                  Scheduler parameters                */
/********************************************************/

#define SCH_QUANTA_US 250U          // Scheduler quanta period in microseconds. Determines the fastest task execution rate.
#define SCH_TASK_NUMBER 3U          // Number of scheduled tasks. Used for structures and arrays sizes.
#define SCH_TASK_STACK_SIZE 100U    // Stack size per task in words. Adjust depending on nesting and data needs.
#define SCH_CYCLIC_TASK_BASE_PRI 8U // Any interrupt with a numerical priority value equal to or higher (lower prio)
                                    // can be served during the background task execution. None can be served during cyclic tasks.

#endif /* SCH_CI_USER_CONFIG_H */
