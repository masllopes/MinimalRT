/*************************************************************************************
* @file    SCH_FI_T1_Task.c
*
* @brief   T1 Task.
*
* @param   None
* @return  void
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/09/2026 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

/*-------------- Required interfaces --------------*/
#include "COM_TE_Types.h"
#include "SCH_FI_Task_Yield.h"


/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_T1_Task.h"

/* -------------- Provided operations --------------*/

void SCH_FI_T1_Task(void)
{



  /* Terminate this instance of the task */
  SCH_FI_Task_Yield();

  return;
}
