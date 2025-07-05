/**************************************************************************************** 
* @file  SCH_FI_Task_Manager.h
*
* @brief SCH_FI_Task_Manager is executed on the systick timer.
* It updates the state of each task, setting them to WAIT when the tasks have
* to be executed.
*
* Additionally, it resets the stack pointer of each task
* pointing it to the right place in the stack for the context switch into them,
* since they don't return and therefore the SP will be pointing to the end
* of the task by the end of its execution.
*
* To allow the detection of overruns, the branching to the tasks is handled by
* PendSV (SCH_FI_Context_Switcher).
*
* This is done because otherwise, due to the lack of reentrant interrupts on
* ARM Cortex-M, a new instance of the Systick timer interrupt cannot preempt a
* previous ongoing call of the handler.
*
* Therefore, if a task was to get blocked, it would not be possible to detect
* that with code on the systick handler. Also, if a task lasts longer than the
* period of systick it would lead to that same kind of blocking behavior, event
* if it's duration was within that task's period, and would prevent faster tasks
* to preempt as intended.
*
* @param   None
* @return  void
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces --------------*/
#include "stdint.h"

#include "SCH_VI.h"
#include "SCH_TI.h"
#include "COM_FE_Disable_Interrupts.h"
#include "COM_FE_Enable_Interrupts.h"
#include "SCH_TI_Device.h"

/* -------------- Provided interfaces  --------------*/

#include "SCH_FI_Task_Manager.h"

/* -------------- Provided operations --------------*/

void SCH_FI_Task_Manager(void)
{
    /* Initialize task index */
    t_uint32 v_task_id = 0U;

    /* Disable interrupts to ensure data integrity */
    COM_FE_Disable_Interrupts();

    /* Increment scheduler quanta counter */
    V_SCH.quanta_ctr++;

    /* Save the currently used SP on index 0 of the queue so that it can be
     used by the context switcher in order to store the context
     of the currently running task */
    V_SCH.task_sp_queue[0] = *V_SCH.task_sp_queue_pt;

    /* Reset the task pointer to one word before the beginning of the queue
     * since it will be pre-incremented before being written */
    V_SCH.task_sp_queue_pt = &V_SCH.task_sp_queue[0];

    /* For every task except BG, starting from the fastest, i.e. highest prio one */
    for (v_task_id = 1U; v_task_id < SCH_TASK_NUMBER; v_task_id++)
    {
        /*`* If it is time for the task to be scheduled */
        if (V_SCH.quanta_ctr % V_SCH.tasks[v_task_id].period_quanta == 0U)
        {
            /* If the previous execution has finished */
            if (V_SCH.tasks[v_task_id].state == TASK_STATE_FINISHED)
            {
                /* Set its state to wait so that it can be scheduled when the higher priority ones finish */
                V_SCH.tasks[v_task_id].state = TASK_STATE_WAIT;

                /* Reset the stack pointer */
                V_SCH.tasks[v_task_id].sp = &V_SCH_STACKS[v_task_id][SCH_TASK_STACK_SIZE - SCH_TASK_BASE_STACK_WORDS];

                /* Reset the program counter to the beginning of the task function */
                V_SCH_STACKS[v_task_id][SCH_BASE_STACK_PC_INDEX] = (t_uint32)V_SCH.tasks[v_task_id].pt_function;

                /* Add the task stack pointer address to the next position in the task queue */
                V_SCH.task_sp_queue_pt++;
                *V_SCH.task_sp_queue_pt = &V_SCH.tasks[v_task_id].sp;
            }
            else if (V_SCH.tasks[v_task_id].state == TASK_STATE_RUNNING || V_SCH.tasks[v_task_id].state == TASK_STATE_WAIT)
            {
                /* If a new instance of the task is meant to start, but the
                 * previous one has not yet started or is still running,
                 * indicate that an overrun has occurred. */
                V_SCH.tasks[v_task_id].overruns++;

                /* Add the task stack pointer address to the next position in the task queue */
                V_SCH.task_sp_queue_pt++;
                *V_SCH.task_sp_queue_pt = &V_SCH.tasks[v_task_id].sp;
            }
        }
        else
        {
            /* If the task has been interrupted and still has to finish */
            if (V_SCH.tasks[v_task_id].state == TASK_STATE_RUNNING)
            {
                /* Add the task stack pointer address to the next position in the task queue */
                V_SCH.task_sp_queue_pt++;
                *V_SCH.task_sp_queue_pt = &V_SCH.tasks[v_task_id].sp;
            }
        }
    }

    /* Add the background task as the last task in the queue */
    V_SCH.task_sp_queue_pt++;
    *V_SCH.task_sp_queue_pt = &V_SCH.tasks[BG_TASK].sp;

    /* Reset the task pointer to one word before the beginning of the queue
     * since it will be pre-incremented by the context switcher before
     * being used to branch to the tasks */
    V_SCH.task_sp_queue_pt = &V_SCH.task_sp_queue[0];

    /* Trigger the execution of the context switcher after return */
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

    /* Reenable interrupts to resume scheduling */
    COM_FE_Enable_Interrupts();

    /* Exit to allow execution of PendSV */
    return;
}
