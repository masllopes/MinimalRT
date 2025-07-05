/*************************************************************************************
* @file    SCH_FE_Init.c
*
* @brief   Initializes the scheduler.
*
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
#include "COM_TE_Types.h"
#include "SCH_TI_Device.h"
#include "SCH_TI.h"
#include "SCH_VI.h"
#include "SCH_TI.h"
#include "SCH_CI_User_Config.h"
#include "COM_FE_Enable_Interrupts.h"
#include "COM_FE_Disable_Interrupts.h"
#include "SCH_FI_Start_Scheduling.h"
#include "SCH_FI_BG_Task.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FE_Init.h"

/* -------------- Provided operations --------------*/

void SCH_FE_Init(void)
{
	/* Task iteration index */
	t_uint32 v_task_id = 0U;

	/* Stack iteration index */
	t_uint32 v_stack_word = 0U;


	/*****************************************************************************/
	/*                           Systick Configuration                           */
	/*****************************************************************************/

	/* Disable interrupts before starting the schedule configuration */
	COM_FE_Disable_Interrupts();

	/*Program the value in the STRELOAD register to generate an interrupt every scheduler quanta*/
	SysTick->LOAD = SCH_QUANTA_US * 1000U / SCH_SYSTICK_TICK_NS - 1U;

	/*Clear the STCURRENT register by writing to it with any value*/
	SysTick->VAL = 0x1234;

	/*Configure the STCTRL register, clock source is system clock enable systick */
	SysTick->CTRL = STCTRL_EN | STRCTRL_CLK_SYSCLK;

	/* Set Priority for Systick and PendSV Interrupts */
    SCB->SHP[(((uint32_t)SysTick_IRQn) & 0xFUL)-4UL] = (uint8_t)(2UL << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL;
    SCB->SHP[(((uint32_t)PendSV_IRQn) & 0xFUL)-4UL] = (uint8_t) (3UL << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL;
	__DMB();
	__ISB();

	/* Allow returning from interrupt handlers while other interrupts are active
	 *  in order to allow manual context switching, by setting NONBASETHRDENA */
	SCB->CCR |= 0x1;

	/* Disable lazy floating point context saving, to make everything more consistent,
	 *  at the cost of higher interrupt latency */
	FPU->FPCCR |= FPU_FPCCR_ASPEN_Msk;
	FPU->FPCCR &= !FPU_FPCCR_LSPEN_Msk;

	/*****************************************************************************/
	/*                           Stack initialization                            */
	/*****************************************************************************/

	/* For each task to be scheduled*/
	for (v_task_id = 0U; v_task_id < (t_uint32)SCH_TASK_NUMBER; v_task_id++)
	{
		/* Initialize stack with pattern for debugging / analysis */
		for (v_stack_word = 0U; v_stack_word < SCH_TASK_STACK_SIZE; v_stack_word++)
		{
			V_SCH_STACKS[v_task_id][v_stack_word] = 0xDEADBEEF;
		}

		/* Initialize Stack pointers */
		V_SCH.tasks[v_task_id].sp = &(V_SCH_STACKS[v_task_id][SCH_TASK_STACK_SIZE]);

		/* Initialize the configurable parameters of the thread control block with the values from the configuration table */
		V_SCH.tasks[v_task_id].id = C_SCH_TASK_CONFIGS[v_task_id].id;
		V_SCH.tasks[v_task_id].period_quanta = C_SCH_TASK_CONFIGS[v_task_id].period_quanta;
		V_SCH.tasks[v_task_id].pt_function = C_SCH_TASK_CONFIGS[v_task_id].pt_function;

		/* Initialize the number of finished executions */
		V_SCH.tasks[v_task_id].execution_nb = 0U;

		/* Initialize the task state to be ready to be scheduled.
		 Since BG task is an infinite loop and not cyclical, it is always running. */
		if (v_task_id == BG_TASK)
		{
			V_SCH.tasks[v_task_id].state = TASK_STATE_RUNNING;
		}
		else
		{
			V_SCH.tasks[v_task_id].state = TASK_STATE_FINISHED;
		}

		/* Initialize stack xPSR and PC, and the remainder with pattern for debugging
	 leaving .sp pointing to the end of the first stack frame memory */
		V_SCH.tasks[v_task_id].sp = &(V_SCH_STACKS[v_task_id][SCH_TASK_STACK_SIZE]);
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEA95C;																					  /* FPSCR */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB95C;																					  /* FPSCR */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB115;																					  /* S15 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB114;																					  /* S14 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB113;																					  /* S13 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB112;																					  /* S12 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB111;																					  /* S11 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB110;																					  /* S10 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB159;																					  /* S9 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB158;																					  /* S8 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB157;																					  /* S7 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB156;																					  /* S6 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB155;																					  /* S5 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB154;																					  /* S4 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB153;																					  /* S3 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB152;																					  /* S2 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB151;																					  /* S1 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB150;																					  /* S0 */
		*(--V_SCH.tasks[v_task_id].sp) = (1u << 24);																					  /* Set xPSR bit 24: Operate in thumb mode*/
		*(--V_SCH.tasks[v_task_id].sp) = (uint32_t)V_SCH.tasks[v_task_id].pt_function;													  /* Set PC to the address of the thread function, will be used to load LR */
		*(--V_SCH.tasks[v_task_id].sp) = (uint32_t)V_SCH.tasks[v_task_id].pt_function; /* Set LR to the address of the thread function */ /* LR (R14) */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB112;																					  /* R12 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F3;																					  /* R3  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F2;																					  /* R2  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F1;																					  /* R1  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F0;																					  /* R0  */

		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB111; /* R11 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB110; /* R10 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F9; /* R9  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F8; /* R8  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F7; /* R7  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F6; /* R6  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F5; /* R5  */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB1F4; /* R4  */

		*(--V_SCH.tasks[v_task_id].sp) = 0xFFFFFFED; /* EXC_RETURN code for the task. FPU used, thread mode. Used to load LR during context switching. */

		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB531; /* S31 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB530; /* S30 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB529; /* S29 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB528; /* S28 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB527; /* S27 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB526; /* S26 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB525; /* S25 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB524; /* S24 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB523; /* S23 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB522; /* S22 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB521; /* S21 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB520; /* S20 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB519; /* S19 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB518; /* S18 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB517; /* S17 */
		*(--V_SCH.tasks[v_task_id].sp) = 0xCAFEB516; /* S16 */
	}


	/*****************************************************************************/
	/*                           Start of scheduling                             */
	/*****************************************************************************/

	/* Initialize the task queue pointer to the beginning of the queue */
	V_SCH.task_sp_queue_pt = &V_SCH.task_sp_queue[0U];

	/* Initialize the scheduler task queue with the background task since
		it will be the first one to be executed before the first Systick interrupt */
	V_SCH.task_sp_queue[0U] = &V_SCH.tasks[BG_TASK].sp;

	/*Initialize scheduler status data structure*/
	V_SCH.quanta_ctr = 0U;

	/*Clear the STCURRENT register by writing to it with any value*/
	SysTick->VAL = 0x1234;

	/* Enable the systick interrupts */
	SysTick->CTRL |= STRCTRL_INT_EN;

	/* Enter cyclic scheduling */
	V_SCH.operation_mode = OP_MODE_CYCLIC;
	SCH_FI_Start_Scheduling();
}
