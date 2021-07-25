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
#include "datum_stack.h"
#include "helper.h"

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
	dstack->head = NULL;
	return dstack;
};

/**
 * Adds a uc_datum to the uc_stack
 *
 * @param d the data to add
 */
void uc_datum_stack_push(struct uc_datum_stack* dstack, uc_datum *d)
{
	uc_datum_stack_node* node = NEW(uc_datum_stack_node);
	node->datum = d;
	node->next = dstack->head;
	dstack->head = node;
}

/**
 * Removes the last uc_datum added to the uc_stack and returns it
 *
 * @return the last uc_datum added to the uc_stack
 */
uc_datum* uc_datum_stack_pop(struct uc_datum_stack* dstack)
{
	if (dstack->head == NULL) 
	{
		return NULL;
	}
	else
	{
		uc_datum_stack_node* node = dstack->head;
		dstack->head = node->next;
		uc_datum* d = node->datum;
		free(node);
		return d;
	}
}

/**
 * Prints the entire uc_stack
 */
void uc_datum_stack_print(struct uc_datum_stack* dstack)
{
	// Print all of the data stored in the uc_stack
	for (uc_datum_stack_node* node = dstack->head; node != NULL; node = node->next)
	{
		uc_datum_print(node->datum);
	}
}

/**
 * Prints a detailed description of the data in the stack
 */
void uc_datum_stack_inspect(struct uc_datum_stack* dstack)
{
	printf("Stack has these items:\n");
	// Print all of the data stored in the uc_stack
	for (uc_datum_stack_node* node = dstack->head; node != NULL; node = node->next)
	{
		printf("    ");
		uc_datum_inspect(node->datum);
		printf("\n");
	}	
}

/**
 * Clears all of the data from the uc_stack
 */
void uc_datum_stack_clear(struct uc_datum_stack* dstack)
{
	uc_datum* pop = uc_datum_stack_pop(dstack);
	while(pop != NULL)
	{
		uc_datum_destroy(pop);
		pop = uc_datum_stack_pop(dstack);
	}
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
