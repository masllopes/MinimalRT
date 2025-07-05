/*************************************************************************************
* @file    SCH_VI.c
*
* @brief   Scheduler global variables.
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
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
