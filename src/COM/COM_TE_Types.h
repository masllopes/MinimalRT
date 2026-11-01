/* SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2025 Marco Lopes
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
 * @file    COM_TE_Types.h
 * @author  Marco Lopes
 * @brief   Common data types.
 */

#ifndef COM_TE_TYPES_H
#define COM_TE_TYPES_H

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
