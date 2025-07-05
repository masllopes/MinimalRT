/*************************************************************************************
* @file    SCH_FI_T1_Task.h
*
* @brief   T1 Task.
*
* @param   None
* @return  void
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

#ifndef SCH_FI_T1_TASK_H
#define SCH_FI_T1_TASK_H

/** @file  SCH_FI_T1_Task.h
 *
 * @brief T1 task.
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces --------------*/

/* -------------- Provided operations prototypes --------------*/

__attribute__((naked)) void SCH_FI_T1_Task(void); /* This function is naked in order to allow a correct manual context switching into it */

#endif /* SCH_FI_T1_TASK_H */
