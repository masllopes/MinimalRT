/*****************************************************************************************
* @file  COM_FE_Disable_Interrupts.c
*
* @brief  This function disables interrupts by writting to PRIMASK.
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
#include "COM_TE_Types.h"

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "COM_FE_Disable_Interrupts.h"

/*-------------------------------- Provided operations ---------------------------------*/

void COM_FE_Disable_Interrupts(void)
{

  t_uint32 v_primask;

  /*Read PRIMASK and disable interrupts*/
  __asm__ volatile(
      "    mrs     %[v_primask], PRIMASK\n"
      "    cpsid   i\n"
      : [v_primask] "=r"(v_primask));
}
