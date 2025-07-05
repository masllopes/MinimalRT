/*************************************************************************************
* @file    SCH_FI_Task_Yield.h
*
* @brief   Yields the task execution, by updating the task state and statistics 
*          and triggering a context switch to the next task.
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

#ifndef SCH_FI_TASK_YIELD_H
#define SCH_FI_TASK_YIELD_H

/** @file  SCH_FI_Task_Yield.h
*
* @brief Updates the scheduler data concerning a task at the end of its
*        execution and triggers a manual context switch via PendSV.
*
* @param   None
* @return  void
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces --------------*/
#include "COM_TE_TYPES.h"
#include "SCH_TI_Device.h"
#include "SCH_TI.h"
#include "SCH_VI.h"

/* -------------- Provided operations prototypes --------------*/

extern void SCH_FI_Task_Yield(void);

#endif /* SCH_FI_TASK_YIELD_H */
