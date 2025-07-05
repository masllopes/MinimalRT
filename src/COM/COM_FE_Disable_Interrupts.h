#ifndef COM_FE_DISABLE_INTERRUPTS_H
#define COM_FE_DISABLE_INTERRUPTS_H

/***************************************************************************************** 
* @file  COM_FE_Disable_Interrupts.h
*
* @brief This function disables interrupts by writting to PRIMASK.
*
* @param   None
* @return  void
******************************************************************************************
*  Version  |       Date        |     Author      |   Description
******************************************************************************************
*     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
******************************************************************************************
*/

/*-------------------------------- Required interfaces ---------------------------------*/

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "COM_FE_Disable_Interrupts.h"

/*--------------------------- Provided operations prototypes ---------------------------*/
void COM_FE_Disable_Interrupts(void);

#endif /* COM_FE_DISABLE_INTERRUPTS_H */
