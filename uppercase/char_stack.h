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
#ifndef _UC_CHAR_STACK_H_
#define _UC_CHAR_STACK_H_

// Headers being used
#include "uppercase/datum.h"

/**
 * The maximum number of characters that can be added into the char stack
 */
#define UC_CHAR_STACK_LENGTH 512

/**
 * Initializes the stack
 */
void uc_char_stack_init(void);

/**
 * Adds a character to the char stack
 *
 * @param c the character to add to the stack
 *
 * @return true if the character is added successfully
 */
int uc_char_stack_push(char c);

/**
 * Returns a string datum from the char stack
 *
 * @return a string datum from the char stack
 */
uc_datum *uc_char_stack_get_string(void);

/**
 * Returns an integer datum from the char stack
 *
 * @return an integer datum from the char stack
 */
uc_datum *uc_char_stack_get_integer(void);

/**
 * Returns a float datum from the char stack
 *
 * @return a float datum from the char stack
 */
uc_datum *uc_char_stack_get_float(void);

/**
 * Clears the char stack
 */
void uc_char_stack_clear(void);

#endif
