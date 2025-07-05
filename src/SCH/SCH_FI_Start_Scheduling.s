/** @file  SCH_FI_Start_Scheduling.s
* 
* @brief Sets the CPU to use the PSP stack pointer instead of MSP, initializes the CPU 
*        registers and branches to the background task and enables interrupts, to start
*        the cyclic scheduling of tasks.
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
.global SCH_FI_Start_Scheduling
.global C_SCH_CYCLIC_TASK_BASEPRI

.thumb_func
SCH_FI_Start_Scheduling:

    /* Disable global interrupts */
    CPSID I;

    /* Initially do not allow any interrupts to be attended, other than the scheduler interrupts */
    LDR     R0, =C_SCH_CYCLIC_TASK_BASEPRI;
    MSR     BASEPRI, R0;

    /* Load the address of V_SCH.task_queue_pt, which is pointing to V_SCH.task_queue[0], into R0 */
    LDR R0, =V_SCH;

    /* Load the address of V_SCH.task_queue[0], which is pointing to V_SCH.task[BG_Task].sp, into R1 */
    LDR R1, [R0];
    
    /* Load the address V_SCH.task[BG_Task].sp, which is pointing to the stack the BG task, into R1 */
    LDR R1,[R1];
    
    /* Load the address of the BG task stack into R1 */
    LDR R1,[R1];

    /* Change the CPU PSP to the address of the stack of the BG task */
    MSR PSP, R1;
    
    /* Switch to using the PSP instead of the MSP, by setting bit 1 of CONTROL */
    MOV R0, #6
    MSR CONTROL, R0;

    /* Point debugging variable to the top of the current stack */
    LDR     R2, =V_DEBUG_CURRENT_STACK_STRUCT;
    STR     R1,[R2]; 
    
    /* Initialize the floating point s16-s31 callee saved registers to the init values in the BG task stack */
    VPOP {S16-S31};
    
    /* Initialize the link register with EXC_RETURN of the BG task */
    POP {LR};
    
    /* Initialize the CPU r4,r5,r6,r7,r8,r9,r10,r11 registers to the init values in the BG task stack */
    POP {R4-R11};

    /* Initialize r0,r1,r2,r3 registers to the init values in the BG task stack */
    POP {R0-R3};

    /* Initialize r12 register to the init value in the BG task stack */
    POP {R12};

    /* Set LR to the PC of the BG task stack, i.e. to the address of the BG task entry point function, in order to branch to it */
    POP {LR};

    /* Point SP back to R0 which is what is expected when the BG task context is to be recovered  */
    SUB SP, SP, #32;
    
    /* Enable global interrupts */
    CPSIE I;

    /* Branch to the BG task */
    BX LR;
