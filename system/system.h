//-----------------------------------------------------------------------
// UpperCase a toy language made up of nothing but uppercase letters
// Copyright (C) 2016  Anshul Kharbanda
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------

/**
 * Handles system states
 */
#ifndef _UC_MODULE_SYSTEM_H_
#define _UC_MODULE_SYSTEM_H_

/**
 * state system
 *
 * Handles system commands like print.
 */
void *uc_system_state(void);

/**
 * state stack
 *
 * Handles stack commands like inspect and clear
 */
void *uc_stack_state(void);

/**
 * state variable
 *
 * Handles variable commands like get and set
 */
void *uc_variable_state(void);

/**
 * state variable
 *
 * Handles getting values from vartable
 */
void *uc_variable_get_state(void);

/**
 * state variable
 *
 * Handles setting values in vartable
 */
void *uc_variable_set_state(void);

#endif