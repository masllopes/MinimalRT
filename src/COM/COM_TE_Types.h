#ifndef COM_TE_TYPES_H
#define COM_TE_TYPES_H

/****************************************************************************************** 
 * @file  COM_TE_TYPES.h
 *
 * @brief Common data types.
 ******************************************************************************************
 *  Version  |       Date        |     Author      |   Description
 ******************************************************************************************
 *     1.0   |    24/06/2025     |  M. Lopes       |    Initial revision.
 ******************************************************************************************
 */

/*-------------------------------- Provided interfaces ---------------------------------*/
#include "COM_TE_Types.h"

/*-------------------------------- Provided data types ---------------------------------*/
/* Boolean data type */
typedef enum
{
  FALSE = 0,
  TRUE = !FALSE
} t_bool;

/* Unsigned integer types */
typedef unsigned char t_uint8;
typedef unsigned short t_uint16;
typedef unsigned int t_uint32;
typedef unsigned long long t_uint64;

/* Signed integer types */
typedef signed char t_int8;
typedef signed short t_int16;
typedef signed int t_int32;
typedef signed long long t_int64;

/* Floating-point types */
typedef float t_float32;
typedef double t_float64;

#endif /* COM_TE_TYPES_H */
