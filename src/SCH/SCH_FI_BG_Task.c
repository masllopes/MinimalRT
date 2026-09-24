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

    while (1)
    {
        
        

    }
}
