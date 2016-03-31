#include "UpperCase/state_machine.h"
#include "UpperCase/program_io.h"

#include <stdio.h>
#include <stdlib.h>


//---------------------------THE FOUNDATION---------------------------

/**
 * Runs the UpperCase state machine.
 *
 * @return true if the state machine ran successfully
 */
int uc_run(void)
{
	error = OKAY;
	void *(*current)(void) = &uc_main_state;
	while (current != NULL)
	{
		current = current();
	}
	return error != OKAY;
}

/**
 * The main state of the program
 * This is where the state machine starts
 */
void *uc_main_state(void)
{
	printf("%c --> main\n", current_character());
	
	if (!next_character())
	{
		return NULL;
	}

	if (invalid_character())
	{
		error = INVALID_CHAR;
		return (void*)&uc_error_state;
	}

	return (void*)&uc_main_state;
}



//---------------------------ERROR HANDLING---------------------------

/**
 * Handles errors.
 */
void *uc_error_state(void)
{
	printf("ERROR: ");
	switch(error)
	{
		case OKAY:
			printf("Unindicated.\n");
			break;
		case INVALID_CHAR:
			printf("%c is invalid! must be an uppercase letter!\n", current_character());
			break;
		default:
			printf("Undefined error %i\n", error);
			break;
	}
	return NULL;
}