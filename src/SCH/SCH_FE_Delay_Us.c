/*****************************************************************************************
 * @file    SCH_FE_Delay_Us.c
 *
 * @brief   Provides the capability of performing a delay/busy wait, specified in microseconds.
 *
 *
 * @param   IN_delay_us: The delay duration in microseconds.
 * @return  void
 ******************************************************************************************
 *  Version  | Date       | Author     | Description
 ******************************************************************************************
 *  1.0      | 24/06/2025 | M. Lopes   | Initial revision.
 ******************************************************************************************
 */

/*-------------------------------- Required interfaces ---------------------------------*/
#include "SCH_VI.h"
#include "SCH_TI.h"
#include "COM_TE_Types.h"
#include "SCH_CI_User_Config.h"
#include "SCH_TI_Device.h"

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "SCH_FE_Delay_Us.h"

/*-------------------------------- Provided operations ---------------------------------*/

void SCH_FE_Delay_Us(t_uint32 IN_delay_us)
{
	t_uint32 v_init_ticks;
	t_uint32 v_current_ticks;
	t_uint32 v_delay_ticks;
	t_uint32 v_tick_diff;

	if (IN_delay_us > (t_uint32)0U)
	{
		/*Read tick at beginning of delay*/
		v_init_ticks = SCH_AUX_CLK_TICKS_COUNTER;
		v_current_ticks = v_init_ticks;
		v_tick_diff = 0U;

		/* Calculate number of ticks corresponding to the desired delay */
		v_delay_ticks = IN_delay_us / SCH_AUX_CLK_TICK_US;
		// v_delay_ticks = IN_delay_us;

		/* Loop until the number of ticks corresponding to the delay have elapsed */
		while (v_tick_diff < v_delay_ticks)
		{

			v_current_ticks = SCH_AUX_CLK_TICKS_COUNTER;
			if (v_current_ticks >= v_init_ticks)
			{
				v_tick_diff = v_current_ticks - v_init_ticks;
			}
			else
			{
				v_tick_diff = (0xFFFFFFFF - v_init_ticks) + v_current_ticks + 1U;
			}
		}
	}
	return;
}
