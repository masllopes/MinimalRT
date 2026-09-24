/** @file  SCH_FI_Context_Switch.s
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
*****************************************************************************************
*  Version  |       Date        |     Author      |   Description
*****************************************************************************************
*     1.0   |    20/07/2025     |  M. Lopes       |    Initial revision.
*****************************************************************************************
*/

 .syntax unified
 .cpu cortex-m4
 .thumb
 .global SCH_FI_Context_Switch

.thumb_func
SCH_FI_Context_Switch:

    /* ************ SUSPEND THE CURRENT TASK ************* */

    /* Disable global interrupts */
    CPSID   I;

    /* Profile  */
    //LDR     R0, =0x40020418     ; 
    //MOV     R1, #(1 << 0)       ; 
    //STR     R1, [R0]            ; 

    /* Recover PSP into r12. r12 is used as a temporary SP, since in handler
     mode the CPU uses the MSP by default. Alternatively could use MSR
     instruction to write to SPSEL and use push and pop. */
    MRS r12, PSP;
    ISB
    
    /* Save the floating point s16-s31 callee saved registers, to be retrieved when the halted task continues */
    VSTMDB r12!, {s16-s31};

    /* Save the CPU r4-r11 callee saved registers in the running task stack, to be retrieved when the halted task continues */
    STMDB r12!, {r4-r11};

    /* Because EXC_RETURN can be different dependent on whether the context switcher is entering from a task or from
     another interrupt, it is required to save and restore it, as such a copy is kept on the stack amongst the
     caller saved registers, and referred to as r14 in order to differentiate it from the CPU LR loaded for the return */
    /*STMDB r12!, {r14};*/


   /* Point debugging variable to the top of the current stack with the stored context */
    LDR     r2, =V_SCH_CURRENT_STACK_STRUCT;
    STR     r12,[r2];

    /* Load the address of V_SCH.task_sp_queue[0] (offset of 16 from V_SCH),
     which points to V_SCH.task[x].sp of the current task, into r0 */
    LDR     r0, =V_SCH;
    ADD     r0,	#16;

    /* Load the address of the stack pointer of the task V_SCH.task[x].sp , into r1 */
    LDR	    r1, [r0];

    /* Update the stack pointer V_SCH.tasks[x].sp with the current stack pointer (r12) so that it can
       be retrieved if the task did not finish yet or is BG, and has to be resumed later */
    STR     r12,[r1];


    /* ************** SELECT THE NEXT TASK ************** */
    /* Load the address of V_SCH.task_sp_queue_pt (equal to V_SCH),
     which points to V_SCH.task_queue[x], into r3 */
    LDR     r3, =V_SCH;

    /* Load the address of V_SCH.task_sp_queue[x], into r1 */
    LDR     r1,	[r3];

    /* Select the next task by changing the stack pointer of the task that
     V_SCH.task_sp_queue_pt points to that of the next higher prio task
     in wait state, i.e. the next element of V_SCH.task_sp_queue (offset of 4) */
    ADD	    r1, r1, #4;

    /* Update V_SCH.task_sp_queue_pt with the address of the next V_SCH.task_queue[x] */
    STR     r1, [r3];

    /* Load the address of the stack pointer of the next task (V_SCH.tasks[x].sp) */
    LDR	    r1, [r1];

    /* Update V_SCH.task_sp_queue[0] (address in r0) with
     the address of the sp of the next task */
    STR    r1, [r0];

    /* Load the stack pointer value of the next task (V_SCH.tasks[x].sp) into r12*/
    LDR	    r12, [r1];

    /* Load the address of the next task stack state (V_SCH.tasks[x].state,
     which is at an offset of 4 from V_SCH.tasks[x].sp) into r1 */
    ADD     r1, r1, #4;

    /* Indicate that the task will be running, by updating V_SCH.tasks[x].state
     to TASK_STATE_RUNNING (2) */
    LDR	    r2, =#2;
    STR     r2, [r1];

   /* Load the address of the next task stack's id (V_SCH.tasks[x].id,
    which is at an offset of 24 from V_SCH.tasks[x].state) into r1 */
    ADD     r1, r1, #24;

    /* Load the address of the current task id indicator (V_SCH.current_task_id)
     , which is at an offset of 4 from V_SCH.task_sp_queue_pt */
    ADD	   r3,r3,#4;

    /* Load the id of the next task into r2 */
    LDR	   r2,[r1];

    /* Update V_SCH.current_task_id with the id of the next task */
    STR	   r2,[r3];

    /* If the next task is the background (task_id == 0), allow all interrupts,
	otherwise allow only interrupts with a priority lower than
	SCH_CYCLIC_TASK_BASE_PRI, by setting BASEPRI accordingly */

    CMP     r2, #0;
    BEQ     SetBasePri0;
    LDR     r0, =C_SCH_CYCLIC_TASK_BASEPRI;
    LDR	    r1, [r0];
    MSR     BASEPRI, r1;
    ISB;
    B       BranchNextTask;

SetBasePri0:
    /* Allow all interrupts */
    MOV     r0, #0;
    MSR     BASEPRI, r0;
    ISB;

BranchNextTask:

    /* ************* BRANCH TO THE NEXT TASK ************* */

    /* Point debugging variable to the current stack */
    LDR     r2, =V_SCH_CURRENT_STACK_STRUCT;
    STR     r12,[r2];

    /* Restore r4,r5,r6,r7,r8,r9,r10,11 from the next task stack
       SP now points to r0 of the task stack */
    LDMIA r12!, {R4-r11};

    /* Restore the floating point s16-s30 callee saved registers,
     from the next task stack */
    VLDMIA r12!, {s16-s31};

    /* Update PSP to the current position of r12 */
    MSR PSP, r12;
    ISB

    /* Enable global interrupts */
    CPSIE   I;

    /* Toggle PB00 for profiling*/
    //LDR     R0, =0x40020418     
    //MOV     R1, #(1 << 16)    ;  
    //STR     R1, [R0]           ; 
 

    /* Branch to the next task */
contextSwitchBranch:
    BX      LR;
