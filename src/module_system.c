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

#include "UpperCase/module_system.h"
#include "UpperCase/program_state_machine.h"
#include "UpperCase/program_io.h"
#include "UpperCase/program_stack.h"
#include "UpperCase/program_error.h"

#include <stdio.h>

//----------------------------HELPER HEADERS-----------------------------

/**
 * Prints the last datum on the stack, then destroys it
 */
static void uc_print(void);

/**
 * Inspects the last datum on the stack, then destroys it
 */
static void uc_inspect(void);



//----------------------------STATE FUNCTIONS----------------------------

/**
 * state system
 *
 * Handles system commands like print
 */
void *uc_system_state(void)
{
	switch(uc_current_character())
	{
		case 'P':
			uc_print();
			return &uc_main_state;
		case 'I':
			uc_inspect();
			return &uc_main_state;
		case 'S':
			return &uc_stack_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> system");
	}
}

/**
 * state stack
 *
 * Handles stack commands like inspect and clear
 */
void *uc_stack_state(void)
{
	switch(uc_current_character())
	{
		case 'I':
			uc_stack_inspect();
			return &uc_main_state;
		case 'C':
			uc_stack_clear();
			return &uc_main_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> system");
	}
}

//----------------------------HELPER FUNCTIONS----------------------------

/**
 * Prints the last datum on the stack, then destroys it
 */
static void uc_print(void)
{
	uc_datum *d = uc_stack_pop();
	uc_datum_print(d);
	uc_datum_destroy(d);
}

/**
 * Inspects the last datum on the stack, then destroys it
 */
static void uc_inspect(void)
{
	uc_datum *d = uc_stack_pop();
	uc_datum_inspect(d);
	uc_datum_destroy(d);
	printf("\n");
}