 /** @file  SCH_FI_Context_Switch.s
 *
* @brief   Performs a manual context switch by manipulating the stack to store the 
* current context and restore the one pointed to by V_SCH. 
* For sake of simplicity it always stores the FPU context, even if the FPU is not used.
*
* @param   None
* @return  void 
*****************************************************************************************
*  Version  |       Date        |     Author      |   Description
*****************************************************************************************
*     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
*****************************************************************************************
*/

 .syntax unified
 .cpu cortex-m4
 .thumb
 .global V_SCH
 .global C_SCH_CYCLIC_TASK_BASEPRI
 .global SCH_FI_Context_Switch


.thumb_func
SCH_FI_Context_Switch:

    /* ************ SUSPEND THE CURRENT TASK ************* */

    /* Disable global interrupts */
    CPSID   I;

    /* Toggle PB00 for profiling
    LDR r0, =0x4100809C;
    LDR r1, =1;
    STR r1, [r0]; */

    /* Recover PSP into R12. R12 is used as a temporary PSP, since in handler
     mode the CPU uses the MSP by default. Alternatively could use MSR
     instruction to write to SPSEL and use push and pop. */
    MRS R12, PSP;
    ISB

    /* Save the CPU r4-r11 callee saved registers in the running task stack, to be retrieved when the halted task continues */
    STMDB R12!, {r4-r11};

    /* Because EXC_RETURN can be different dependent on whether the context switcher is entering from a task or from
     another interrupt, it is required to save and restore it, as such a copy is kept on the stack amongst the
     caller saved registers, and referred to as R14 in order to differentiate it from the CPU LR loaded for the return */
    STMDB R12!, {r14};

    /* Save the floating point s16-s31 callee saved registers, to be retrieved when the halted task continues */
    VSTMDB R12!, {S16-S31};

   /* Point debugging variable to the top of the current stack with the stored context */
    LDR     R2, =V_DEBUG_CURRENT_STACK_STRUCT;
    STR     R12,[R2];

    /* Load the address of V_SCH.task_sp_queue[0] (offset of 16 from V_SCH),
     which points to V_SCH.task[x].sp of the current task, into R0 */
    LDR     R0, =V_SCH;
    ADD     R0,	#16;

    /* Load the address of the stack pointer of the task V_SCH.task[x].sp , into R1 */
    LDR	    R1, [R0];

    /* Update the stack pointer V_SCH.tasks[x].sp with the current stack pointer (R12) so that it can
       be retrieved if the task did not finish yet or is BG, and has to be resumed later */
    STR     R12,[R1];


    /* ************** SELECT THE NEXT TASK ************** */
    /* Load the address of V_SCH.task_sp_queue_pt (equal to V_SCH),
     which points to V_SCH.task_queue[x], into R3 */
    LDR     R3, =V_SCH;

    /* Load the address of V_SCH.task_sp_queue[x], into R1 */
    LDR     R1,	[R3];

    /* Select the next task by changing the stack pointer of the task that
     V_SCH.task_sp_queue_pt points to that of the next higher prio task
     in wait state, i.e. the next element of V_SCH.task_sp_queue (offset of 4) */
    ADD	    R1, R1, #4;

    /* Update V_SCH.task_sp_queue_pt with the address of the next V_SCH.task_queue[x] */
    STR     R1, [R3];

    /* Load the address of the stack pointer of the next task (V_SCH.tasks[x].sp) */
    LDR	    R1, [R1];

    /* Update V_SCH.task_sp_queue[0] (address in R0) with
     the address of the sp of the next task */
    STR    R1, [R0];

    /* Load the stack pointer value of the next task (V_SCH.tasks[x].sp) into R12*/
    LDR	    R12, [R1];

    /* Load the address of the next task stack*s state (V_SCH.tasks[x].state,
     which is at an offset of 4 from V_SCH.tasks[x].sp) into R1 */
    ADD     R1, R1, #4;

    /* Indicate that the task will be running, by updating V_SCH.tasks[x].state
     to TASK_STATE_RUNNING (2) */
    LDR	    R2, =#2;
    STR     R2, [R1];

   /* Load the address of the next task stack's id (V_SCH.tasks[x].id,
    which is at an offset of 24 from V_SCH.tasks[x].state) into R1 */
    ADD     R1, R1, #24;

    /* Load the address of the current task id indicator (V_SCH.current_task_id)
     , which is at an offset of 4 from V_SCH.task_sp_queue_pt */
    ADD	   R3,R3,#4;

    /* Load the id of the next task into R2 */
    LDR	   R2,[R1];

    /* Update V_SCH.current_task_id with the id of the next task */
    STR	   R2,[R3];

    /* If the next task is the background (task_id == 0), allow all interrupts,
	otherwise allow only interrupts with a priority lower than
	C_SCH_CYCLIC_TASK_BASEPRI, by setting BASEPRI accordingly */

    CMP     R2, #0;
    BEQ     SetPrimask0;
    LDR     R0, =C_SCH_CYCLIC_TASK_BASEPRI;
    MSR     BASEPRI, R0;
    B       Continue;

SetPrimask0:
    MOV     R0, #0;
    MSR     BASEPRI, R0;

Continue:

    /* ************* BRANCH TO THE NEXT TASK ************* */

    /* Point debugging variable to the current stack */
    LDR     R2, =V_DEBUG_CURRENT_STACK_STRUCT;
    STR     R12,[R2];

    /* Restore the floating point s16-s30 callee saved registers,
     from the next task stack */
    VLDMIA R12!, {S16-S31};

    /* Because EXC_RETURN can be different dependent on whether the context switcher is entering from a task or from
     another interrupt, it is required to save and restore it, as such a copy is kept on the stack amongst the
     caller saved registers, and referred to as R14 in order to differentiate it from the CPU LR loaded for the return */
    LDMIA R12!, {r14};

    /* Restore r4,r5,r6,r7,r8,r9,r10,11 from the next task stack
       SP now points to R0 of the task stack */
    LDMIA R12!, {r4-r11};

    /* Update PSP to the current position of R12 */
    MSR PSP, R12;
    ISB

    /* Enable global interrupts */
    CPSIE   I;

    /* Toggle PB00 for profiling
    LDR r0, =0x4100809C;
    LDR r1, =1;
    STR r1, [r0]; */

    /* Branch to the next task */
    BX      LR;
