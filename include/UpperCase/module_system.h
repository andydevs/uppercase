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
 * Handles stack commands like print and inspect
 */
void *uc_stack_state(void);

#endif