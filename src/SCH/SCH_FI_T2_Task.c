/*************************************************************************************
* @file    SCH_FI_T2_Task.c
*
* @brief   T2 Task.
*
* @param   None
* @return  void
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

/*-------------- Required interfaces --------------*/
#include "SCH_FI_Task_Yield.h"
#include "COM_TE_Types.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_T2_Task.h"

/* -------------- Provided operations --------------*/

void SCH_FI_T2_Task(void)
{


   /* Terminate this instance of the task */
   SCH_FI_Task_Yield();
}
