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

#include "math.h"
#include "statemachine.h"
#include "error.h"

//--------------------------HELPER HEADERS--------------------------

/**
 * Adds the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_add(struct uc_datum_stack* dstack);

/**
 * Subtracts the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_subtract(struct uc_datum_stack* dstack);

/**
 * Multiplies the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_multiply(struct uc_datum_stack* dstack);

/**
 * Divides the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_divide(struct uc_datum_stack* dstack);

/**
 * Performs the modulus on the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_modulus(struct uc_datum_stack* dstack);

//----------------------------MATH STATE----------------------------

/**
 * state math
 *
 * Handles math operations
 */
void *uc_math_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack)
{
	switch(uc_program_current_character(program))
	{
		case 'A':
			uc_add(dstack);
			return (void*)&uc_main_state;
		case 'S':
			uc_subtract(dstack);
			return (void*)&uc_main_state;
		case 'T':
			uc_multiply(dstack);
			return (void*)&uc_main_state;
		case 'D':
			uc_divide(dstack);
			return (void*)&uc_main_state;
		case 'M':
			uc_modulus(dstack);
			return (void*)&uc_main_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> math");
	}
}



//------------------------HELPER FUNCTIONS--------------------------

/**
 * Adds the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_add(struct uc_datum_stack* dstack)
{
	uc_datum* b = uc_datum_stack_pop(dstack);
	uc_datum* a = uc_datum_stack_pop(dstack);
	uc_datum* c = uc_datum_add(a, b);
	uc_datum_destroy(a);
	uc_datum_destroy(b);
	uc_datum_stack_push(dstack, c);
}

/**
 * Subtracts the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_subtract(struct uc_datum_stack* dstack)
{
	uc_datum* b = uc_datum_stack_pop(dstack);
	uc_datum* a = uc_datum_stack_pop(dstack);
	uc_datum* c = uc_datum_subtract(a, b);
	uc_datum_destroy(a);
	uc_datum_destroy(b);
	uc_datum_stack_push(dstack, c);
}

/**
 * Multiplies the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_multiply(struct uc_datum_stack* dstack)
{
	uc_datum* b = uc_datum_stack_pop(dstack);
	uc_datum* a = uc_datum_stack_pop(dstack);
	uc_datum* c = uc_datum_multiply(a, b);
	uc_datum_destroy(a);
	uc_datum_destroy(b);
	uc_datum_stack_push(dstack, c);
}

/**
 * Divides the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_divide(struct uc_datum_stack* dstack)
{
	uc_datum* b = uc_datum_stack_pop(dstack);
	uc_datum* a = uc_datum_stack_pop(dstack);
	uc_datum* c = uc_datum_divide(a, b);
	uc_datum_destroy(a);
	uc_datum_destroy(b);
	uc_datum_stack_push(dstack, c);
}

/**
 * Performs the modulus on the last two data on the stack together, 
 * and pushes the result back onto the stack
 */
void uc_modulus(struct uc_datum_stack* dstack)
{
	uc_datum* b = uc_datum_stack_pop(dstack);
	uc_datum* a = uc_datum_stack_pop(dstack);
	uc_datum* c = uc_datum_modulus(a, b);
	uc_datum_destroy(a);
	uc_datum_destroy(b);
	uc_datum_stack_push(dstack, c);
}
