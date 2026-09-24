#ifndef SCH_FE_DELAY_US_H
#define SCH_FE_DELAY_US_H

/******************************************************************************************
* @file    SCH_FE_Delay_Us.h
*
* @brief   Provides the capability of performing a delay/busy wait, specified in microseconds.
*
*
* @param   IN_delay_us: The delay duration in microseconds.
* @return  void
******************************************************************************************
*  Version  | Date       | Author     | Description       
******************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
******************************************************************************************
*/

/*-------------------------------- Required interfaces ---------------------------------*/
#include "COM_TE_Types.h"

/*--------------------------- Provided operations prototypes ---------------------------*/

void SCH_FE_Delay_Us(t_uint32 delay_us);

/*----------------------------- Provided define constants ------------------------------*/

#endif /* SCH_FE_DELAY_US_H */
