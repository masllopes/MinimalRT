/*************************************************************************************
* @file    SCH_FI_BG_Task.c
*
* @brief   Background task, executed while none of the cyclic tasks has to be attended to.
*
* @param   None
* @return  void 
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/
#ifndef SCH_FI_BG_TASK_H
#define SCH_FI_BG_TASK_H

/** @file  SCH_F03_BG_Task.h
 *
 * @brief Prototype of the scheduler BG thread
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces --------------*/

/* -------------- Provided operations prototypes --------------*/

__attribute__((naked)) void SCH_FI_BG_Task(void); /* This function is naked in order to allow a correct manual context switching into it */

#endif /* SCH_FI_BG_TASK_H */
