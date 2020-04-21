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

// Includes
#include "uppercase/datum_stack.h"
#include "uppercase/helper.h"

// Headers being used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------- FUNCTION -------------------------------

/**
 * Creates a new stack
 */
struct uc_datum_stack* uc_datum_stack_new()
{
	struct uc_datum_stack* dstack = NEW(struct uc_datum_stack);
	for (int i = 0; i < UC_STACK_LENGTH; ++i)
	{
		dstack->stack_data[i] = NULL;
	}
	dstack->stack_cursor = 0;
	return dstack;
};

/**
 * Adds a uc_datum to the uc_stack
 *
 * @param d the data to add
 */
int uc_datum_stack_push(struct uc_datum_stack* dstack, uc_datum *d)
{
	// Add the data if the uc_stack is not full, and return True
	// Else, return false
	if (dstack->stack_cursor < UC_STACK_LENGTH)
	{
		dstack->stack_data[dstack->stack_cursor] = d;
		dstack->stack_cursor++;
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * Removes the last uc_datum added to the uc_stack and returns it
 *
 * @return the last uc_datum added to the uc_stack
 */
uc_datum* uc_datum_stack_pop(struct uc_datum_stack* dstack)
{
	// Remove data from uc_stack and return it if there is any
	// Else return NULL
	if (dstack->stack_cursor > 0)
	{
		uc_datum *d = dstack->stack_data[dstack->stack_cursor - 1];
		dstack->stack_data[dstack->stack_cursor - 1] = NULL;
		dstack->stack_cursor--;
		return d;
	}
	else
	{
		return NULL;
	}
}

/**
 * Prints the entire uc_stack
 */
void uc_datum_stack_print(struct uc_datum_stack* dstack)
{
	// Print all of the data stored in the uc_stack
	for (int i = 0; i < dstack->stack_cursor; ++i)
	{
		uc_datum_print(dstack->stack_data[i]);
	}
}

/**
 * Prints a detailed description of the data in the stack
 */
void uc_datum_stack_inspect(struct uc_datum_stack* dstack)
{
	printf("Stack has %d items:\n", dstack->stack_cursor);
	// Print all of the data stored in the uc_stack
	for (int i = 0; i < dstack->stack_cursor; ++i)
	{
		printf("    ");
		uc_datum_inspect(dstack->stack_data[i]);
		printf("\n");
	}	
}

/**
 * Clears all of the data from the uc_stack
 */
void uc_datum_stack_clear(struct uc_datum_stack* dstack)
{
	// Free all data in the uc_stack and set to null
	for (int i = 0; i < UC_STACK_LENGTH; ++i)
	{
		if (dstack->stack_data[i] != NULL)
		{
			uc_datum_destroy(dstack->stack_data[i]);
			dstack->stack_data[i] = NULL;
		}
	}

	// Set cursor to zero
	dstack->stack_cursor = 0;
}

/**
 * Destroys uc datum stack
 */
void uc_datum_stack_destroy(struct uc_datum_stack** dstackloc)
{
	uc_datum_stack_clear(*dstackloc);
	free(*dstackloc);
	*dstackloc = NULL;	
}
