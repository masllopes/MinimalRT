
#ifndef SCH_TI_H
#define SCH_TI_H

/** @file  SCH_TI.h
 *
 * @brief Scheduler data types and definitions used during scheduler operation.
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces --------------*/
#include "SCH_CI_User_Config.h"
#include "COM_TE_Types.h"

/*-------------- Provided interfaces --------------*/
#include "SCH_TI.h"

/*-------------------- Provided define constants----------------------*/
/* Number of base stack of a
task with caller and callee saved registers, including FPU */
#define SCH_TASK_BASE_STACK_WORDS 51U

/* Index of the PC register on the stack of a task */
#define SCH_BASE_STACK_PC_INDEX (SCH_TASK_STACK_SIZE - 20U)

/* Index of background task is 0 and used for scheduling logic */
#define BG_TASK 0U

/* Systick control register configuration values (adjusted according to clock config)*/
#define STRCTRL_CLK_SYSCLK      0x04u     /* Select System clock as source for systick*/
#define STCTRL_EN               0x01u     /* Enable systick timer*/
#define STRCTRL_INT_EN          0x02u     /* Interrupt enable for systick wraparound */

/*-------------------- Provided data types ----------------------------*/

typedef enum
{
	TASK_STATE_INIT = 0,
	TASK_STATE_WAIT = 1,
	TASK_STATE_RUNNING = 2,
	TASK_STATE_FINISHED = 3,
} t_sch_task_state;

/* Thread / task control block */
typedef struct
{
	volatile t_uint32 *volatile sp; /* Thread stack pointer */
	t_sch_task_state state;			/* Task state */
	t_uint32 period_quanta;			/* Task period in number of scheduler quanta*/
	void (*pt_function)(void);		/* Pointer to the task function*/
	t_uint32 execution_nb;			/* Number of completed executions of the task*/
	t_uint32 last_execution_time;	/* TODO:*/
	t_uint32 overruns;				/* Number of missed schedulings */
	t_uint32 id;			     	/* Task ID */
} t_sch_task;

typedef enum
{
	OP_MODE_INIT = 0,
	OP_MODE_CYCLIC = 1
} t_sch_op_mode;

/* Scheduler data */
typedef struct
{
	volatile t_uint32 *volatile *volatile *task_sp_queue_pt;		  /* Pointer to the task stack pointers queue managed by SCH_FI_Task_Manager */
	volatile t_uint32 current_task_id;							  /* Identifier of the currently scheduled task */
	t_uint64 quanta_ctr;											  /* Scheduler quanta counter */
	volatile t_uint32 *volatile *task_sp_queue[SCH_TASK_NUMBER + 1U]; /* Task queue managed by SCH_FI_Task_Manager. Index 0 holds SP of the task being interrupted. */
	t_sch_task tasks[SCH_TASK_NUMBER];								  /* Array containing the structs for each task handled by the scheduler */
	t_sch_op_mode operation_mode;									  /* Operation mode of the scheduler */
} t_sch_data;

/* Task stack frame, constituted by the ARM CM4F exception stack frame with FPU
 * plus the CPU and FPU caller saved registers and a copy of the EXEC_RETURN
 * at the entry of the context switcher function */
typedef struct
{
	// Floating-point caller saved registers
	t_uint32 S16;
	t_uint32 S17;
	t_uint32 S18;
	t_uint32 S19;
	t_uint32 S20;
	t_uint32 S21;
	t_uint32 S22;
	t_uint32 S23;
	t_uint32 S24;
	t_uint32 S25;
	t_uint32 S26;
	t_uint32 S27;
	t_uint32 S28;
	t_uint32 S29;
	t_uint32 S30;
	t_uint32 S31;

	// Copy of LR at context switcher entry, used to restore LR with the
	// appropriate EXC_RETURN and inform the CPU how to handle the return
	// from the context switcher
	t_uint32 EXC_RETURN;

	// General purpose caller saved registers
	t_uint32 R4;
	t_uint32 R5;
	t_uint32 R6;
	t_uint32 R7;
	t_uint32 R8;
	t_uint32 R9;
	t_uint32 R10;
	t_uint32 R11;

	// General purpose callee saved registers
	t_uint32 R0;
	t_uint32 R1;
	t_uint32 R2;
	t_uint32 R3;
	t_uint32 R12;
	t_uint32 LR;
	t_uint32 PC;
	t_uint32 xPSR;

	// Floating-point callee saved registers
	t_uint32 S0;
	t_uint32 S1;
	t_uint32 S2;
	t_uint32 S3;
	t_uint32 S4;
	t_uint32 S5;
	t_uint32 S6;
	t_uint32 S7;
	t_uint32 S8;
	t_uint32 S9;
	t_uint32 S10;
	t_uint32 S11;
	t_uint32 S12;
	t_uint32 S13;
	t_uint32 S14;
	t_uint32 S15;
	t_uint32 FPSCR;
	t_uint32 NO_NAME;

} t_sch_stack_frame;

#endif /* SCH_TI_H */
