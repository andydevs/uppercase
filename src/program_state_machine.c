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

#include "UpperCase/program_state_machine.h"
#include "UpperCase/program_io.h"
#include "UpperCase/program_error.h"
#include "UpperCase/program_stack.h"
#include "UpperCase/program_vartable.h"

#include <stdio.h>
#include <stdlib.h>

//---------------------------THE FOUNDATION---------------------------

/**
 * Runs the UpperCase state machine.
 *
 * @return true if the state machine ran unsuccessfully
 */
int uc_state_machine_run(void)
{
	// Initialize stack, vartable, current character, and current state
	uc_stack_init();
	uc_vartable_init();
	uc_next_character();
	uc_state uc_current_state = &uc_main_state;

	// Run the state machine loop
	// While there are still more characters and states
	while (uc_current_state != NULL && uc_continue())
	{
		// If an invalid character is spotted
		if (uc_invalid_character())
		{
			// Throw error
			uc_throw_error(UC_INPUT_CHAR_INVALD, "[RUN]");

			// Don't forget to clear the stack and vartable
			uc_stack_clear();
			uc_vartable_clear();

			// Return error
			return 1;
		}

		// Run the current state and retrieve the next state
		uc_current_state = uc_current_state();

		// Get next character
		uc_next_character();
	}

	// Clear the stack
	uc_stack_clear();
	uc_vartable_clear();

	// Return program success
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
		printf("REGISTRY ERROR: Invalid character slot: '%c'\n", name);
		return 0;
	}

	if (uc_main_registry[name - 'A'] != NULL)
	{
		printf("REGISTRY ERROR: Slot filled: '%c'\n", name);
		return 0;
	}

	uc_main_registry[name - 'A'] = function;
	return 1;
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
		return uc_throw_error(UC_REGISTRY_MODULE_NOT_FOUND, "main");
	}

	return uc_main_registry[uc_current_character() - 'A'];
}