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

#include "UpperCase/program_error.h"
#include "UpperCase/program_io.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Function for throwing errors
 *
 * @param uc_err the error being thrown
 * @param state_description the description of the current state
 *
 * @return NULL pointer
 */
void *uc_throw_error(uc_error_type uc_err, const char* state_description)
{
	printf("ERROR in %s: ", state_description);
	switch(uc_err)
	{
		case UC_INPUT_CHAR_INVALD:
			printf("'%c' is invalid! Must be an uppercase letter!\n", uc_current_character());
			return NULL;
		case UC_CHAR_NOT_FOUND:
			printf("'%c' character not found!\n", uc_current_character());
			return NULL;
		case UC_REGISTRY_MODULE_SLOT_FILLED:
			printf("'%c' is already registered to another function!\n", uc_current_character());
			return NULL;
		case UC_REGISTRY_MODULE_NOT_FOUND:
			printf("'%c' Module not found in registry\n", uc_current_character());
			return NULL;
		case UC_STACK_FULL:
			printf("Stack is full!\n");
			return NULL;
		case UC_CHAR_STACK_FULL:
			printf("Char stack is full\n");
			return NULL;
		default:
			printf("Undefined error %i\n", uc_err);
			return NULL;
	}
}
