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

// Headers being used
#include "uppercase/char_stack.h"
#include "uppercase/helper.h"

// Headers being used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Creates a char stack
 *
 * @return new char stack
 */
struct uc_char_stack *uc_char_stack_new(void) {
	struct uc_char_stack* cstack = NEW(struct uc_char_stack);	
	for (int i = 0; i < UC_CHAR_STACK_LENGTH; ++i)
	{
		cstack->stack_data[i] = 0;
	}
	cstack->stack_cursor = 0;
	return cstack;
}

/**
 * Adds a character to the char stack
 *
 * @param cstack the char stack
 * @param c the character to add to the stack
 *
 * @return true if the character is added successfully
 */
int uc_char_stack_push(struct uc_char_stack* cstack, char c)
{
	if (cstack->stack_cursor < UC_CHAR_STACK_LENGTH)
	{
		cstack->stack_data[cstack->stack_cursor] = c;
		cstack->stack_cursor++;
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * Returns a string datum from the char stack
 *
 * @param cstack the char stack
 *
 * @return a string datum from the char stack
 */
uc_datum* uc_char_stack_get_string(struct uc_char_stack* cstack)
{
	char* string = (char*)malloc(cstack->stack_cursor*sizeof(char));
	strcpy(string, cstack->stack_data);
	return uc_datum_from_string(string);
}

/**
 * Returns an integer datum from the char stack
 *
 * @param cstack the char stack
 *
 * @return an integer datum from the char stack
 */
uc_datum *uc_char_stack_get_integer(struct uc_char_stack* cstack)
{
	return uc_datum_from_integer(atoi(cstack->stack_data));
}

/**
 * Returns a float datum from the char stack
 *
 * @param cstack the char stack
 *
 * @return a float datum from the char stack
 */
uc_datum *uc_char_stack_get_float(struct uc_char_stack* cstack)
{
	return uc_datum_from_float(atof(cstack->stack_data));
}

/**
 * Clears the char stack
 *
 * @param cstack the char stack
 */
void uc_char_stack_clear(struct uc_char_stack* cstack)
{
	for (int i = 0; i < UC_CHAR_STACK_LENGTH; ++i)
	{
		cstack->stack_data[i] = 0;
	}
	cstack->stack_cursor = 0;
}

/**
 * Destroys the stack
 *
 * @param cstack the char stack
 */
void uc_char_stack_destroy(struct uc_char_stack **cstack)
{
	if (*cstack) free(*cstack);
	*cstack = NULL;
}

