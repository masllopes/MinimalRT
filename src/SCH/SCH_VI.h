/*************************************************************************************
* @file    SCH_VI.h
*
* @brief   Scheduler global variables.
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

#ifndef SCH_VI_H
#define SCH_VI_H

/** @file  SCH_VI.h
 *
 * @brief Declaration of the internal variables of the scheduler component.
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces ------------------*/
#include "SCH_FE_Init.h"
#include "SCH_TI.h"

/*-------------- Provided interfaces -------------------*/
#include "SCH_VI.h"

/* -------------- Provided Global Data --------------*/

/*Stack of each thread*/
extern volatile t_uint32 V_SCH_STACKS[SCH_TASK_NUMBER][SCH_TASK_STACK_SIZE];

/*Scheduler status data*/
extern t_sch_data V_SCH;

/* TODO: Debug variables to be removed */
extern t_sch_stack_frame *V_DEBUG_CURRENT_STACK_STRUCT;

#endif /* SCH_VI_H */
