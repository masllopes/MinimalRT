#ifndef SCH_FI_Context_Switch_H
#define SCH_FI_Context_Switch_H

/******************************************************************************************
* @file    SCH_FI_Context_Switch.h
*
* @brief  When a new SCH_FI_Context_Switch (systick) interrupt service routine is entered,
* the callee saved registers are automatically pushed by HW, the context switch code then
* pushes the caller saved registers, in order to save the context of whatever task is being 
* excuted at the time of the interrupt. 
*
* Then using the data in V_SCH it gets the SP to the next task to be executed and it pops the 
* caller saved registers in order to start restoring the context of the next task. 
* It also sets the PRIMASK in order to allow other interrupts to interrupt the cyclic tasks
* based on the priority configurable via the SCH_CYCLIC_TASK_BASE_PRI constant parameter.
*
* When the interrupt service routine is left the HW automatically pops the callee saved 
* registers, completing the restoring of the context of the next task and branching to where 
* the PC of the new context points to.
* 
* When popping to the CPU register the SP increments, when push to the stack SP decrements. 
* 		
* For sake of simplicity, the lazy context save of FP state feauture of the cortex cores is used,
* and the code always stores the FPU context, even if the FPU is not used.
*
* @param   None
* @return  void 
******************************************************************************************
*  Version  | Date       | Author     | Description       
******************************************************************************************
*  1.0      | 20/07/2025 | M. Lopes   | Initial revision. 
/*****************************************************************************************
*/

/*-------------------------------- Required interfaces ---------------------------------*/

/*--------------------------- Provided operations prototypes ---------------------------*/

__attribute__((naked)) void SCH_FI_Context_Switch(void);

#endif /* SCH_FI_Context_Switch_H */
