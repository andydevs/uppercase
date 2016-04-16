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

#include "UpperCase/module_math.h"
#include "UpperCase/state_machine.h"
#include "UpperCase/program_io.h"
#include "UpperCase/stack.h"
#include "UpperCase/error.h"

//--------------------------HELPER HEADERS--------------------------

/**
 * Adds the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_add(void);

//----------------------------MATH STATE----------------------------

/**
 * state math
 *
 * Handles math operations
 */
void *uc_math_state(void)
{
	switch(uc_current_character())
	{
		case 'A':
			uc_add();
			return (void*)&uc_main_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> math");
	}
}



//------------------------HELPER FUNCTIONS--------------------------

/**
 * Adds the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_add(void)
{
	uc_datum* b = uc_stack_pop();
	uc_datum* a = uc_stack_pop();
	uc_datum* c = uc_datum_add(a, b);
	uc_datum_destroy(a);
	uc_datum_destroy(b);
	uc_stack_push(c);
}