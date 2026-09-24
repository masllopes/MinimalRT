#ifndef SCH_FE_DELAY_MS_H
#define SCH_FE_DELAY_MS_H

/******************************************************************************************
* @file    SCH_FE_Delay_ms.h
*
* @brief   Provides the capability of performing a delay/busy wait, specified in milliseconds.
*
*
* @param   IN_delay_ms: The delay duration in milliseconds.
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

void SCH_FE_Delay_ms(t_uint64 delay_ms);

/*----------------------------- Provided define constants ------------------------------*/

#endif /* SCH_FE_DELAY_MS_H */
