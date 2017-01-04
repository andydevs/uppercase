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

// Program files being used
#include "UpperCase/Program/state_machine.h"
#include "UpperCase/Program/io.h"
#include "UpperCase/Program/error.h"
#include "UpperCase/Program/stack.h"
#include "UpperCase/Program/vartable.h"

// Modules being used
#include "UpperCase/Module/data.h"
#include "UpperCase/Module/system.h"
#include "UpperCase/Module/math.h"

// Libraries being used
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
 * state main
 *
 * This is where the state machine starts
 */
void *uc_main_state(void)
{
	switch(uc_current_character())
	{
		case 'D':
			return &uc_data_state;
		case 'S':
			return &uc_system_state;
		case 'M':
			return &uc_math_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main");
	}
}