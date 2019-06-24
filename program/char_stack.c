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
#include "stack.h"

// Headers being used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * The character stack
 */
static char uc_char_stack[UC_STRING_MAX_LENGTH];

/**
 * The current position in the char stack
 * Also the number of elements in the char stack
 */
static int uc_char_stack_cursor;

/**
 * Initializes the stack
 */
void uc_char_stack_init(void)
{
	for (int i = 0; i < UC_CHAR_STACK_LENGTH; ++i)
	{
		uc_char_stack[i] = 0;
	}
	uc_char_stack_cursor = 0;
}

/**
 * Adds a character to the char stack
 *
 * @param c the character to add to the stack
 *
 * @return true if the character is added successfully
 */
int uc_char_stack_push(char c)
{
	if (uc_char_stack_cursor < UC_CHAR_STACK_LENGTH)
	{
		uc_char_stack[uc_char_stack_cursor] = c;
		uc_char_stack_cursor++;
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
 * @return a string datum from the char stack
 */
uc_datum* uc_char_stack_get_string(void)
{
	char* string = (char*)malloc(uc_char_stack_cursor*sizeof(char));
	strcpy(string, uc_char_stack);
	return uc_datum_from_string(string);
}

/**
 * Returns an integer datum from the char stack
 *
 * @return an integer datum from the char stack
 */
uc_datum *uc_char_stack_get_integer(void)
{
	return uc_datum_from_integer(atoi(uc_char_stack));
}

/**
 * Returns a float datum from the char stack
 *
 * @return a float datum from the char stack
 */
uc_datum *uc_char_stack_get_float(void)
{
	return uc_datum_from_float(atof(uc_char_stack));
}

/**
 * Clears the char stack
 */
void uc_char_stack_clear(void)
{
	for (int i = 0; i < uc_char_stack_cursor; ++i)
	{
		uc_char_stack[i] = 0;
	}
	uc_char_stack_cursor = 0;
}
