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
#include "statemachine.h"
#include "program.h"
#include "error.h"
#include "char_stack.h"
#include "datum_stack.h"
#include "vartable.h"

// Modules being used
#include "data.h"
#include "system.h"
#include "math.h"

// Libraries being used
#include <stdio.h>
#include <stdlib.h>

//---------------------------THE FOUNDATION---------------------------

/**
 * Runs the UpperCase state machine.
 *
 * @return true if the state machine ran unsuccessfully
 */
int uc_state_machine_run(struct uc_program* program)
{
	// Setup stuff
	struct uc_char_stack* cstack = uc_char_stack_new();
	struct uc_datum_stack* dstack = uc_datum_stack_new();
	uc_vartable_init();

	// Initialize program
	uc_program_next(program);
	uc_state uc_current_state = &uc_main_state;

	// Run the state machine loop
	// While there are still more characters and states
	while (uc_current_state != NULL && uc_program_continue(program))
	{
		// Error if an invalid character is spotted
		if (uc_program_invalid_character(program))
		{
			// Error and teardown that shit
			uc_throw_error(program, UC_INPUT_CHAR_INVALD, "[RUN]");
			uc_char_stack_destroy(&cstack);
			uc_datum_stack_destroy(&dstack);
			uc_vartable_clear();
			return 1;
		}

		// Run the current state and retrieve the next state and character
		uc_current_state = uc_current_state(program, dstack, cstack);
		uc_program_next(program);
	}

	// Teardown
	uc_char_stack_destroy(&cstack);
	uc_datum_stack_destroy(&dstack);
	uc_vartable_clear();

	// Return program success
	return 0;
}

/**
 * state main
 *
 * This is where the state machine starts
 */
void *uc_main_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack)
{
	switch(uc_program_current_character(program))
	{
		case 'D':
			return &uc_data_state;
		case 'S':
			return &uc_system_state;
		case 'M':
			return &uc_math_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main");
	}
}
