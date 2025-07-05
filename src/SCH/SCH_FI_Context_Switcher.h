
#ifndef SCH_FI_CONTEXT_SWITCHER_H
#define SCH_FI_CONTEXT_SWITCHER_H

/*************************************************************************************
* @file    SCH_FI_Context_Switcher.h
*
* @brief   Performs a manual context switch by manipulating the stack to store the 
* current context and restore the one pointed to by V_SCH. 
* For sake of simplicity it always stores the FPU context, even if the FPU is not used.
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

/* -------------- Provided operations prototypes --------------*/

__attribute__((naked)) void SCH_FI_Context_Switcher(void);

#endif /* SCH_FI_CONTEXT_SWITCHER_H */
