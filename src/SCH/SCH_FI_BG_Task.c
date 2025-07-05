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

/*-------------- Required interfaces --------------*/
#include "SCH_FE_Delay_Us.h"
#include "SCH_VI.h"
#include "COM_TE_Types.h"
#include "GPIO.h"

/* -------------- Provided interfaces  --------------*/

#include "SCH_FI_BG_Task.h"

/* -------------- Provided operations --------------*/

void SCH_FI_BG_Task(void)
{

    int dummy = 0;
    int i;
    while (1)
    {
        pin_set(SCH_PROF_PB0);
        
        for(i = 0; i < 10; i++) 
        {
                dummy++;
        }

        V_SCH.tasks[BG_TASK].execution_nb++;
        pin_reset(SCH_PROF_PB0);
    }
}
