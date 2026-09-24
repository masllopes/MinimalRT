
    /*------------------------------------------------------------------------------
    * @file  SCH_FI_Start_Scheduling.s
    *
    * @brief Sets the CPU to use the PSP stack pointer instead of MSP, initializes the CPU
    *        registers and branches to the background task and enables interrupts, to start
    *        the cyclic scheduling of tasks.
    *
    * @param   None
    * @return  void
    *------------------------------------------------------------------------------
    *  Version  |       Date        |     Author      |   Description
    *------------------------------------------------------------------------------
    *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
    *------------------------------------------------------------------------------
    */

/* Directives */
	
.syntax unified
.cpu cortex-m4
.thumb
			 
.global SCH_FI_Start_Scheduling

/* External symbols */
.extern V_SCH
.extern V_SCH_CURRENT_STACK_STRUCT
.extern SCH_FI_Sync_Task
.extern C_SCH_CYCLIC_TASK_BASEPRI

.thumb_func
SCH_FI_Start_Scheduling:								  
    /* Disable global interrupts */                
    CPSID I                                       
    ISB                                           
    DSB                                           

    /* After branching to the first task allow only interrupts with a priority lower than SCH_CYCLIC_TASK_BASE_PRI, by setting BASEPRI accordingly */ 
    MOV     r0, #15       
    MSR     BASEPRI, r0   
    ISB                   
    /* Load the address of V_SCH.task_queue_pt, which is pointing to V_SCH.task_queue[0], into R0 */ 
    LDR R0, =V_SCH                                

    /* Load the address of V_SCH.task_queue[0], which is pointing to V_SCH.task[x].sp, into R1 */ 
    LDR R1, [R0]                                  
    /* Load the address V_SCH.task[x].sp, which is pointing to the stack the first task, into R1 */ 
    LDR R1, [R1]                                  
    /* Load the address of the first task stack into R1 */ 
    LDR R1, [R1]                                  

    /* Change the CPU PSP to the address of the stack of the first task */ 
    MSR PSP, R1                                   
    ISB                                           
    DSB                                          

    /* Switch to using the PSP instead of the MSP, by setting bit 1 of CONTROL */ 
    MOV R0, #6                                    
    MSR CONTROL, R0                               
    ISB                                           
    DSB                                           
	
													   
				

    /* Point debugging variable to the top of the current stack */ 
    LDR     R2, =V_SCH_CURRENT_STACK_STRUCT        
    STR     R1,[R2]                                
																				 
			  
					

																  
											
					 
	
    /* Initialize the CPU r4,r5,r6,r7,r8,r9,r10,r11 registers to the init values in the first task stack */ 
    POP {R4-R11}                                  
                
																	 
			 
	
    /* Initialize the floating point s16-s31 caller saved registers to the init values in the first task stack */ 
    VPOP {S16-S31}                                

    /* Initialize r0,r1,r2,r3 registers to the init values in the first task stack */ 
    POP {R0-R3}                                   

    /* Initialize r12 register to the init value in the first task stack */ 
    POP {R12}                                     

    /* Initialize the link register with EXC_RETURN of the first task */ 
    POP {LR}                                      

    /* Skip to S0 */
    ADD SP, SP, #8                                

    /* Initialize the floating point s0-s15 callee saved registers to the init values in the first task stack */ 
    VPOP {S0-S15}                                 

    /* SP now points to FPSCR. Since lazy stack is used 8-byte alignment, 
    meaning FPSCR must be an 8-byte boundary and the SP must point to the next 8-byte 
    boundary beyond the stack frame for the next context switch to be performed correctly */ 
    ADD SP, SP, #8                                

#if SCH_START_SYNC_ENABLE
    /* Allow only interrupts with a priority lower than
        SCH_CYCLIC_TASK_BASE_PRI, by setting BASEPRI accordingly */
    LDR     r0, =C_SCH_CYCLIC_TASK_BASEPRI                    
    LDR	    r1, [r0]                                  
    MSR     BASEPRI, r1                                 
    ISB                                               

    /* Preserve the current LR which points to the first cyclic task entry point */
    PUSH {LR}                                     
    
    /* Call SCH_FI_Sync_Task */
    BL SCH_FI_Sync_Task                           

    /* Restore the cyclic task LR */
    POP {LR}                                      
#endif // SCH_START_SYNC_ENABLE

startBranch:                                      
    /* Enable global interrupts */
    CPSIE I                                       

    /* Branch to the first task */
    BX LR                                         