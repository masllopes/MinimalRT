#ifndef SCH_FE_PHASE_SHIFT_H
#define SCH_FE_PHASE_SHIFT_H

/************************************************************************************************ 
* @file  SCH_FE_Phase_Shift.h
*
* @brief Updates the Systick reload value in order to offset the
* Systick timer by a given amount of time, in microseconds. SCH_FI_Task_Manager
* will then reset the reload value to the original one, so that the period is kept.
* @param   None
* @return  void
******************************************************************************************
*  Version  |       Date        |     Author      |   Description
******************************************************************************************
*     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
******************************************************************************************
*/

/*-------------------------------- Required interfaces ---------------------------------*/
#include "SCH_CI_User_Config.h"
/*-------------------------------- Provided interfaces ---------------------------------*/
#include "SCH_FE_Phase_Shift.h"

/*--------------------------- Provided operations prototypes ---------------------------*/
#if SCH_PH_SHIFT_ENABLE
    t_bool SCH_FE_Phase_Shift(t_float32 in_offset_us);
#endif /* SCH_PH_SHIFT_ENABLE */

#endif /* SCH_FE_PHASE_SHIFT_H */
