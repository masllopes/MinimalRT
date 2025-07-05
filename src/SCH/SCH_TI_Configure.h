/*************************************************************************************
* @file    SCH_TI_Configure.h
*
* @brief   Scheduler user configurations.
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

#ifndef SCH_TI_CONFIGURE_H
#define SCH_TI_CONFIGURE_H

/** @file  SCH_TI_Configure.h
 *
 * @brief Scheduler configuration data types.
 *****************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 *****************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 *****************************************************************************************
 */

/*-------------- Required interfaces --------------*/
#include "COM_TE_Types.h"

/*-------------- Provided interfaces --------------*/
#include "SCH_TI_Configure.h"

/*-------------------- Provided data types ----------------------------*/
/* Task configuration */
typedef struct
{
    t_uint32 id;
    t_uint32 period_quanta;
    void (*pt_function)(void);
} t_sch_task_configure;


#endif /* SCH_TI_CONFIGURE_H */
