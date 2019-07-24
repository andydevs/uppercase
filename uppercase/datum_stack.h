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
 * Handles the stack
 */
#ifndef _UC_DATUM_STACK_H_
#define _UC_DATUM_STACK_H_

// Headers being used
#include "uppercase/datum.h"

/**
 * The maximum number of values that can be added in the stack
 */
#define UC_STACK_LENGTH 1024

/**
 * Initializes the stack
 */
void uc_datum_stack_init(void);

/**
 * Adds a datum to the stack
 *
 * @param d the data to add to the stack
 *
 * @return true if data was successfully added
 */
int uc_datum_stack_push(uc_datum *d);

/**
 * Removes the last datum added to the stack and returns it
 *
 * @return the last datum added to the stack
 */
uc_datum *uc_datum_stack_pop(void);

/**
 * Prints the entire stack
 */
void uc_datum_stack_print(void);

/**
 * Prints a detailed description of the data in the stack
 */
void uc_datum_stack_inspect(void);

/**
 * Clears all of the data from the stack
 */
void uc_datum_stack_clear(void);

#endif
