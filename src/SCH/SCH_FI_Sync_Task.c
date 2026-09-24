/****************************************************************************************
 * @file  SCH_FI_Sync_Task.c
 *
 * @brief SCH_FI_Sync_Task is
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

// #include "SCH_FE_Delay_Us.h"
#include "COM_FE_Enable_IRQ.h"
#include "COM_FE_Disable_IRQ.h"

/* -------------- Provided interfaces  --------------*/
#include "SCH_FI_Sync_Task.h"

/* ---------- Local operations prototypes ----------*/
static inline void SCH_FL_Sync_Task_Prologue(void);

/* -------------- Provided operations --------------*/
void SCH_FI_Sync_Task(void)
{

    // Wait for the sync event to be detected */
    //  SCH_FE_Delay_Us(50U); // Simulate some sync process time

    // COM_FE_Enable_IRQ(EXTI15_10_IRQn);

    COM_FE_Disable_IRQ(EXTI15_10_IRQn);

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
