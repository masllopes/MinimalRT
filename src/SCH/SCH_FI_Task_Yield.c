/*************************************************************************************
* @file    SCH_FI_Task_Yield.h
*
* @brief   Yields the task execution, by updating the task state and statistics 
*          and triggering a context switch to the next task.
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

/*-------------- Required interfaces --------------*/
#include "SCH_TI_Device.h"
#include "SCH_TI.h"
#include "SCH_VI.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_Task_Yield.h"

/* -------------- Provided operations --------------*/

inline void SCH_FI_Task_Yield(void)
{
    /* Indicate the end of execution of the task */
    V_SCH.tasks[V_SCH.current_task_id].state = TASK_STATE_FINISHED;
    V_SCH.tasks[V_SCH.current_task_id].execution_nb++;

    /* Set the execution of PendSV to pending */
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    __ISB(); /* Instruction Synchronization Barrier */
    __DSB(); /* Data Synchronization Barrier */

    return;
}
