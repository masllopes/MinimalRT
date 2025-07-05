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
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

/*-------------- Required interfaces --------------*/
#include "COM_TE_Types.h"
#include "SCH_FI_Task_Yield.h"
#include "SCH_FE_Delay_Us.h"
#include "GPIO.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_T1_Task.h"

/* -------------- Provided operations --------------*/

void SCH_FI_T1_Task(void)
{
  pin_set(SCH_PROF_PA6);

  SCH_FE_Delay_Us(300U);

  pin_reset(SCH_PROF_PA6);

  /* Terminate this instance of the task */
  SCH_FI_Task_Yield();

  return;
}
