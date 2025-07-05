#ifndef SCH_FI_START_SCHEDULING_H
#define SCH_FI_START_SCHEDULING_H


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


/*-------------- Required interfaces --------------*/

/* -------------- Provided operations prototypes --------------*/

__attribute__((naked)) void SCH_FI_Start_Scheduling(void);

#endif /* SCH_FI_START_SCHEDULING_H */
