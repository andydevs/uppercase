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
#include "UpperCase/state_machine.h"
#include "UpperCase/program_io.h"
#include "UpperCase/stack.h"
#include "UpperCase/error.h"

//----------------------------HELPER HEADERS-----------------------------

/**
 * Prints the last element in the stack
 */
static void print(void);



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
			uc_datum_print(uc_stack_pop());
			return &uc_main_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> system");
	}
}



//----------------------------HELPER FUNCTIONS----------------------------

/**
 * Prints the last element in the stack
 */
static void print(void)
{
	uc_datum *d = uc_stack_pop();
	uc_datum_print(d);
	uc_datum_destroy(d);
}