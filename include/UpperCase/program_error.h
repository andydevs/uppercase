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

/**
 * Handles errors in the program
 */
#ifndef _UC_ERROR_H_
#define _UC_ERROR_H_

/**
 * Defines error types
 */
typedef enum 
{
	UC_INPUT_CHAR_INVALD,
	UC_CHAR_NOT_FOUND,
	
	UC_REGISTRY_MODULE_SLOT_FILLED,
	UC_REGISTRY_MODULE_NOT_FOUND,

	UC_STACK_FULL,
	UC_CHAR_STACK_FULL,
} 
uc_error_type;

/**
 * Function for throwing errors
 *
 * @param uc_err the error being thrown
 * @param state_description the description of the current state
 *
 * @return NULL pointer
 */
void *uc_throw_error(uc_error_type uc_err, const char* state_description);

#endif