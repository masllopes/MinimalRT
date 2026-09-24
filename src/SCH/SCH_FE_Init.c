/*****************************************************************************************
* @file    SCH_FE_Init.c
*
* @brief   Initializes the scheduler.
*
*
* @param   None
* @return  void
******************************************************************************************
*  Version  | Date       | Author     | Description       
******************************************************************************************
*  1.0      | 20/07/2025 | M. Lopes   | Initial revision. 
******************************************************************************************
*/

/*-------------------------------- Required interfaces ---------------------------------*/
#include "COM_TE_Types.h"
#include "SCH_TI_Device.h"
#include "SCH_TI_Configure.h"
#include "SCH_TI.h"
#include "SCH_VI.h"
#include "SCH_TI.h"
#include "SCH_CI_User_Config.h"
#include "COM_FE_Enable_Interrupts.h"
#include "COM_FE_Disable_Interrupts.h"
#include "SCH_FI_Start_Scheduling.h"
#include "SCH_FI_BG_Task.h"

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "SCH_FE_Init.h"

/*-------------------------------- Provided operations ---------------------------------*/

void SCH_FE_Init(void)
{
	
	t_sch_stack_frame *v_stack_frame_ptr; /* Stack frame pointer */
	t_uint32 v_task_id = 0U;              /* Task iteration index */
	t_uint32 v_stack_word = 0U;           /* Stack iteration index */
	t_uint32 v_align_idx_off = 0U;        /* Index offset for 8-byte alignment of the stack */


	/*****************************************************************************/
	/*                           Systick Configuration                           */
	/*****************************************************************************/

	/* Disable interrupts before starting the schedule configuration */
	__disable_irq();

	/*Program the value in the STRELOAD register to generate an interrupt every scheduler quanta*/
	#if SCH_START_SYNC_ENABLE
		SysTick->LOAD = SCH_QUANTA_TICKS_SYNC;
	#else
		SysTick->LOAD = SCH_QUANTA_TICKS;
	#endif

	/*Configure the STCTRL register, clock source is system clock enable systick */
	SysTick->CTRL = STCTRL_EN | STRCTRL_CLK_SYSCLK;

	/* Set Priority for Systick and PendSV Interrupts */
    SCB->SHP[(((uint32_t)SysTick_IRQn) & 0xFUL)-4UL] = (uint8_t)(0UL << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL;
    SCB->SHP[(((uint32_t)PendSV_IRQn) & 0xFUL)-4UL] = (uint8_t) (0UL << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL;
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

		/* Initialize the configurable parameters of the thread control block with the values from the configuration table */
		V_SCH.tasks[v_task_id].id = C_SCH_TASK_CONFIGS[v_task_id].id;
		V_SCH.tasks[v_task_id].period_quanta = C_SCH_TASK_CONFIGS[v_task_id].period_us / SCH_QUANTA_US;
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

		/* The stack bottom and top have to be 8-byte aligned since lazy stacking is used,
		save the top and PC addresses with the alignment, in order to reset the tasks later  */
		v_align_idx_off  = ((t_uint32)&V_SCH_STACKS[v_task_id][SCH_TASK_STACK_SIZE] & 0x7U) != 0U;
		V_SCH.tasks[v_task_id].stack_top_ptr = &V_SCH_STACKS[v_task_id][SCH_BASE_STACK_TOP_IDX_OFFSET-v_align_idx_off];
		V_SCH.tasks[v_task_id].stack_pc_ptr = &V_SCH_STACKS[v_task_id][SCH_BASE_STACK_PC_IDX_OFFSET-v_align_idx_off];

		/* 	Point to the top of the stack of the task with 8-byte alignment.
			From lowest to highest address it should contain the following:
	      	- Caller (SW) saved registers: R4-R11, S16-S31
		  	- Callee (HW) saved registers: R0-R13, R12, LR, PC, xPSR, S0-S15 FPSCR, one or two 8-byte alignment words

		  */

		  V_SCH.tasks[v_task_id].sp = V_SCH.tasks[v_task_id].stack_top_ptr;        

        /* Fill the task stack frame fields with a pattern for analysis and debugging */
		v_stack_frame_ptr = (t_sch_stack_frame *)V_SCH.tasks[v_task_id].stack_top_ptr;

        v_stack_frame_ptr->R4  = 0xCAFEB1F4;
        v_stack_frame_ptr->R5  = 0xCAFEB1F5;
        v_stack_frame_ptr->R6  = 0xCAFEB1F6;
        v_stack_frame_ptr->R7  = 0xCAFEB1F7;
        v_stack_frame_ptr->R8  = 0xCAFEB1F8;
        v_stack_frame_ptr->R9  = 0xCAFEB1F9;
        v_stack_frame_ptr->R10 = 0xCAFEB110;
        v_stack_frame_ptr->R11 = 0xCAFEB111;

        v_stack_frame_ptr->S16 = 0xCAFEB516;
        v_stack_frame_ptr->S17 = 0xCAFEB517;
        v_stack_frame_ptr->S18 = 0xCAFEB518;
        v_stack_frame_ptr->S19 = 0xCAFEB519;
        v_stack_frame_ptr->S20 = 0xCAFEB520;
        v_stack_frame_ptr->S21 = 0xCAFEB521;
        v_stack_frame_ptr->S22 = 0xCAFEB522;
        v_stack_frame_ptr->S23 = 0xCAFEB523;
        v_stack_frame_ptr->S24 = 0xCAFEB524;
        v_stack_frame_ptr->S25 = 0xCAFEB525;
        v_stack_frame_ptr->S26 = 0xCAFEB526;
        v_stack_frame_ptr->S27 = 0xCAFEB527;
        v_stack_frame_ptr->S28 = 0xCAFEB528;
        v_stack_frame_ptr->S29 = 0xCAFEB529;
        v_stack_frame_ptr->S30 = 0xCAFEB530;
        v_stack_frame_ptr->S31 = 0xCAFEB531;

        v_stack_frame_ptr->R0  = 0xCAFEB1F0;
        v_stack_frame_ptr->R1  = 0xCAFEB1F1;
        v_stack_frame_ptr->R2  = 0xCAFEB1F2;
        v_stack_frame_ptr->R3  = 0xCAFEB1F3;
        v_stack_frame_ptr->R12 = 0xCAFEB112;
        v_stack_frame_ptr->LR  = (uint32_t)V_SCH.tasks[v_task_id].pt_function;
        v_stack_frame_ptr->PC  = (uint32_t)V_SCH.tasks[v_task_id].pt_function;
        v_stack_frame_ptr->xPSR = (1u << 24);

        v_stack_frame_ptr->S0  = 0xCAFEB150;
        v_stack_frame_ptr->S1  = 0xCAFEB151;
        v_stack_frame_ptr->S2  = 0xCAFEB152;
        v_stack_frame_ptr->S3  = 0xCAFEB153;
        v_stack_frame_ptr->S4  = 0xCAFEB154;
        v_stack_frame_ptr->S5  = 0xCAFEB155;
        v_stack_frame_ptr->S6  = 0xCAFEB156;
        v_stack_frame_ptr->S7  = 0xCAFEB157;
        v_stack_frame_ptr->S8  = 0xCAFEB158;
        v_stack_frame_ptr->S9  = 0xCAFEB159;
        v_stack_frame_ptr->S10 = 0xCAFEB110;
        v_stack_frame_ptr->S11 = 0xCAFEB111;
        v_stack_frame_ptr->S12 = 0xCAFEB112;
        v_stack_frame_ptr->S13 = 0xCAFEB113;
        v_stack_frame_ptr->S14 = 0xCAFEB114;
        v_stack_frame_ptr->S15 = 0xCAFEB115;
        v_stack_frame_ptr->FPSCR = 0x0;
		
	}

	/*****************************************************************************/
	/*                           Start of scheduling                             */
	/*****************************************************************************/

	/* Initialize the task queue pointer to the beginning of the queue */
	V_SCH.task_sp_queue_pt = &V_SCH.task_sp_queue[0];

	/* Initialize the scheduler task queue with the background task since
	it will be the first one to be executed before the first Systick interrupt */
	
	/* If sync start is enabled */
	#if SCH_START_SYNC_ENABLE
		/* Set the queue so that the sync task is executed, waiting for the sync event detection,
		setting time zero and then jumping to the first cyclic task */
		V_SCH.task_sp_queue[0U] = &V_SCH.tasks[1].sp;
		V_SCH.task_sp_queue[1U] = &V_SCH.tasks[0].sp;

	#else
		/* Otherwise, set the queue so that the background task is the first one being executed
		until one quanta has elapsed and the task manager starts managing the queue */
		V_SCH.task_sp_queue[0U] = &V_SCH.tasks[BG_TASK].sp;
	#endif
	
	/*Initialize scheduler status data structure*/
	V_SCH.quanta_ctr = 0U;

	/* If sync start is not enable, reset the systick counter and enable the interrupts */
	#if !SCH_START_SYNC_ENABLE
		/*Clear the STCURRENT register by writing to it with any value*/
		SysTick->VAL = 0x1234;

		/* Enable the systick interrupts */
		SysTick->CTRL |= STRCTRL_INT_EN;
	#endif

	/* Enter cyclic scheduling, by manually setting up the registers to the 
	context of the first task to be executed */
	V_SCH.operation_mode = OP_MODE_CYCLIC;
	SCH_FI_Start_Scheduling();

	/* This point should never be reached */
	while(1);
}
