#include "UpperCase/state_machine.h"
#include "UpperCase/program_io.h"
#include "UpperCase/error.h"

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
	uc_state uc_current_state = &uc_main_state;
	while (uc_current_state != NULL && uc_next_character())
	{
		if (uc_invalid_character())
		{
			uc_throw_error(UC_INPUT_CHAR_INVALD);
			return 1;
		}
		uc_current_state = uc_current_state();
	}
	return 0;
}

/**
 * The main state of the program
 * This is where the state machine starts
 */
void *uc_main_state(void)
{
	return (void*)uc_registry_get_module();
}


//---------------------------REGISTRY SYSTEM--------------------------

/**
 * The registry used by the main state
 */
static uc_state uc_main_registry[26];

/**
 * Registers the given state function (representing a module) to the registry used by the main state
 * 
 * @param name the letter name to be used to call the function
 * @param function the function being set to the name
 *
 * @return status code indicating successful registration of module to letter
 */
int uc_register_module(char name, uc_state function)
{
	if (!(name >= 'A' && name <= 'Z'))
	{
		uc_throw_error(UC_INPUT_CHAR_INVALD);
		return 1;
	}

	if (uc_main_registry[name - 'A'] != NULL)
	{
		uc_throw_error(UC_REGISTRY_MODULE_SLOT_FILLED);
		return 1;
	}

	uc_main_registry[name - 'A'] = function;
	return 0;
}

/**
 * Returns the module represented by the current character
 *
 * @return the module represented by the current character
 */
uc_state uc_registry_get_module()
{
	if (uc_main_registry[uc_current_character() - 'A'] == NULL)
	{
		return uc_throw_error(UC_REGISTRY_MODULE_NOT_FOUND);
	}

	return uc_main_registry[uc_current_character() - 'A'];
}