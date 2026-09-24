/****************************************************************************************
 * @file  SCH_FI_Sync_Task.c
 *
 * @brief Provides a place holder for the synchronization event task.
 * @param   None
 * @return  void
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    21/07/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces --------------*/
#include "SCH_TI_Device.h"
#include "SCH_CI_User_Config.h"
#include "SCH_TI.h"


/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_Sync_Task.h"

/* ---------- Local operations prototypes ----------*/
static inline void SCH_FL_Sync_Task_Prologue(void);

/* -------------- Provided operations --------------*/
void SCH_FI_Sync_Task(void)
{

    /* Perform the sync prologue, handling systick and jumping to the first cyclic task*/
    SCH_FL_Sync_Task_Prologue();
}

void SCH_FL_Sync_Task_Prologue(void)
{
    /* Reset the Systick counter to zero, setting the new zero time reference and
    update the reload value for the quanta ticks without offset, which will kick-in
    after from the second Systick interrupt onwards */
    SysTick->VAL = 0;
    SysTick->CTRL |= STRCTRL_INT_EN;
    SysTick->LOAD = SCH_QUANTA_TICKS;
}
