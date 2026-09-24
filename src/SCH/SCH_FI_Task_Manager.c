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
#include "SCH_TI_Configure.h"

/* -------------- Provided interfaces  --------------*/

#include "SCH_FI_Task_Manager.h"

/* -------------- Provided operations --------------*/
void SCH_FI_Task_Manager(void)
{
    /* Disable interrupts to prevent any preemption of the task manager
       by a higher priority interrupt, which could lead to an inconsistent state
       of the scheduler data */
    __disable_irq();

#if SCH_PH_SHIFT_ENABLE
    /* If a phase shift is ongoing, reset the reload value to the original one */
    switch (V_SCH.phase_shift_state)
    {
    case PH_SHIFT_ADJ_CYCLE:

        /* Reset the Systick reload value to the original one, which will kick-in in the next cycle */
        SysTick->LOAD = SCH_QUANTA_TICKS;

        /* The request was made before this Systick interrupt, so the adjustment cycle will follow */
        V_SCH.phase_shift_state = PH_SHIFT_RESET;
        break;

    case PH_SHIFT_RESET:

        /* Now that the Systick reload value returned to SCH_QUANTA_TICKS,
        reset the phase shift state to allow processing further requests */
        V_SCH.phase_shift_state = PH_SHIFT_REQ_AVAILABLE;
        break;
    default:
        break;
    }
#endif /* SCH_PH_SHIFT_ENABLE */

    t_uint32 v_task_id; /* Task ID variable used to iterate through the tasks */

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
        /* If it is time for the task to be scheduled */
        if (V_SCH.quanta_ctr % V_SCH.tasks[v_task_id].period_quanta == 0U)
        {
            /* If the previous execution has finished */
            if (V_SCH.tasks[v_task_id].state == TASK_STATE_FINISHED)
            {
                /* Set its state to wait so that it can be scheduled when the higher priority ones finish */
                V_SCH.tasks[v_task_id].state = TASK_STATE_WAIT;

                /* Reset the stack pointer */
                V_SCH.tasks[v_task_id].sp = V_SCH.tasks[v_task_id].stack_top_ptr;

                /* Reset the program counter to the beginning of the task function */
                *(V_SCH.tasks[v_task_id].stack_pc_ptr) = (t_uint32)V_SCH.tasks[v_task_id].pt_function;

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
    __enable_irq();
    // pin_reset(SCH_PROF_PA7);
    /* Exit to allow execution of PendSV */
    return;
}
