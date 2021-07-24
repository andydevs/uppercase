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

#include "system/system.h"
#include "uppercase/statemachine.h"
#include "uppercase/error.h"
#include "uppercase/vartable.h"

#include <stdio.h>

//----------------------------HELPER HEADERS-----------------------------

/**
 * Prints the last datum on the stack, then destroys it
 */
static void uc_print(struct uc_datum_stack* dstack);

/**
 * Inspects the last datum on the stack, then destroys it
 */
static void uc_inspect(struct uc_datum_stack* dstack);

//----------------------------STATE FUNCTIONS----------------------------

/**
 * state system
 *
 * Handles system commands like print
 */
void *uc_system_state(struct uc_program *program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack)
{
	switch(uc_program_current_character(program))
	{
		case 'P':
			uc_print(dstack);
			return &uc_main_state;
		case 'I':
			uc_inspect(dstack);
			return &uc_main_state;
		case 'S':
			return &uc_stack_state;
		case 'V':
			return &uc_variable_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> system");
	}
}

/**
 * state stack
 *
 * Handles stack commands like inspect and clear
 */
void *uc_stack_state(struct uc_program *program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack)
{
	switch(uc_program_current_character(program))
	{
		case 'I':
			uc_datum_stack_inspect(dstack);
			return &uc_main_state;
		case 'C':
			uc_datum_stack_clear(dstack);
			return &uc_main_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> system -> stack");
	}
}

/**
 * state variable
 *
 * Handles variable commands like get and set
 */
void *uc_variable_state(struct uc_program *program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack)
{
	switch(uc_program_current_character(program))
	{
		case 'S':
			return &uc_variable_set_state;
		case 'G':
			return &uc_variable_get_state;
		case 'I':
			uc_vartable_inspect();
			return &uc_main_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> system -> variable");
	}
}

/**
 * state variable
 *
 * Handles getting values from vartable
 */
void *uc_variable_get_state(struct uc_program *program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack)
{
	uc_datum *d = uc_vartable_get(uc_program_current_character(program));
	uc_datum_stack_push(dstack, d);
	return &uc_main_state;
}

/**
 * state variable
 *
 * Handles setting values in vartable
 */
void *uc_variable_set_state(struct uc_program *program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack)
{
	uc_datum *d = uc_datum_stack_pop(dstack);
	uc_vartable_set(uc_program_current_character(program), d);
	return &uc_main_state;
}

//----------------------------HELPER FUNCTIONS----------------------------

/**
 * Prints the last datum on the stack, then destroys it
 */
static void uc_print(struct uc_datum_stack* dstack)
{
	uc_datum *d = uc_datum_stack_pop(dstack);
	uc_datum_print(d);
	uc_datum_destroy(d);
}

/**
 * Inspects the last datum on the stack, then destroys it
 */
static void uc_inspect(struct uc_datum_stack* dstack)
{
	uc_datum *d = uc_datum_stack_pop(dstack);
	uc_datum_inspect(d);
	uc_datum_destroy(d);
	printf("\n");
}
