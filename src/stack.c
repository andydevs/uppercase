#include "UpperCase/stack.h"

/**
 * Headers being used
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * The uc_stack
 */
static uc_datum *uc_stack[UC_STACK_LENGTH];

/**
 * The current position in the uc_stack
 * Also the number of elements in the uc_stack
 */
static int uc_stack_cursor;

/**
 * Initializes the uc_stack
 */
void uc_stack_init(void)
{
	// Set all data in the uc_stack to null
	for (int i = 0; i < UC_STACK_LENGTH; ++i)
	{
		uc_stack[i] = NULL;
	}

	// Set full to zero
	uc_stack_cursor = 0;
}

/**
 * Adds a uc_datum to the uc_stack
 *
 * @param d the data to add
 */
int uc_stack_push(uc_datum *d)
{
	// Add the data if the uc_stack is not full, and return True
	// Else, return false
	if (uc_stack_cursor < UC_STACK_LENGTH)
	{
		uc_stack[uc_stack_cursor] = d;
		uc_stack_cursor++;
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
uc_datum *uc_stack_pop(void)
{
	// Remove data from uc_stack and return it if there is any
	// Else return NULL
	if (uc_stack_cursor > 0)
	{
		uc_datum *d = uc_stack[uc_stack_cursor];
		uc_stack[uc_stack_cursor] = NULL;
		uc_stack_cursor--;
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
void uc_stack_print(void)
{
	// Print all of the data stored in the uc_stack
	for (int i = 0; i < uc_stack_cursor; ++i)
	{
		uc_datum_print(uc_stack[i]);
	}
}

/**
 * Prints a detailed description of the data in the stack
 */
void uc_stack_inspect(void)
{
	printf("Stack has %d items:\n", uc_stack_cursor);
	// Print all of the data stored in the uc_stack
	for (int i = 0; i < uc_stack_cursor; ++i)
	{
		printf("    ");
		uc_datum_inspect(uc_stack[i]);
		printf("\n");
	}	
}

/**
 * Clears all of the data from the uc_stack
 */
void uc_stack_clear(void)
{
	// Free all data in the uc_stack and set to null
	for (int i = 0; i < UC_STACK_LENGTH; ++i)
	{
		if (((unsigned long)uc_stack[i]) > 0)
		{
			free(uc_stack[i]);
		}
	}

	// Set cursor to zero
	uc_stack_cursor = 0;
}