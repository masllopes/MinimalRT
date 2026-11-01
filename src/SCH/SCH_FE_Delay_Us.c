/* SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2025-2026 Marco Lopes
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file    SCH_FE_Delay_Us.c
 * @author  Marco Lopes
 * @brief   Provides the capability of performing a delay/busy wait, specified in
 *          microseconds.
 *
 * @param   IN_delay_us: The delay duration in microseconds.
 * @return  void
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
