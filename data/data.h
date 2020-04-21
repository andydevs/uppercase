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
 * Handles reading data from the UpperCase language.
 */
#ifndef _UC_MODULE_DATA_H_
#define _UC_MODULE_DATA_H_

// Include program
#include "uppercase/program.h"
#include "uppercase/char_stack.h"
#include "uppercase/datum_stack.h"

//----------------------------DATA STATE----------------------------

/**
 * state data
 *
 * The data state
 */
void *uc_data_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);


//---------------------------STRING STATE---------------------------

/**
 * state string
 *
 * Handles string data types
 */
void *uc_string_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state string_letter
 *
 * Handles letters in strings
 */
void *uc_string_letter_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state string_uppercase
 *
 * Handles uppercase letters in strings
 */
void *uc_string_uppercase_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state string_lowercase
 *
 * Handles lowercase letters in strings
 */
void *uc_string_lowercase_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state string_whitespace
 *
 * Handles whitespace characters in strings
 */
void *uc_string_whitespace_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state string_punctuation
 *
 * Handles punctuation in strings
 */
void *uc_string_punctuation_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);


//--------------------------CHARACTER STATE-------------------------

/**
 * state character
 *
 * Handles character data types
 */
void *uc_character_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state character_letter
 *
 * Handles letters
 */
void *uc_character_letter_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state character_uppercase
 *
 * Handles uppercase letters
 */
void *uc_character_uppercase_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state character_lowercase
 *
 * Handles lowercase letters
 */
void *uc_character_lowercase_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state character_whitespace
 *
 * Handles whitespace characters
 */
void *uc_character_whitespace_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state character_punctuation
 *
 * Handles punctuation
 */
void *uc_character_punctuation_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);


//----------------------------NUMBER STATE--------------------------

/**
 * state boolean
 *
 * Handles booleans
 */
void *uc_boolean_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state integer
 *
 * Handles integers
 */
void *uc_integer_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

/**
 * state integer
 *
 * Handles integers
 */
void *uc_float_state(struct uc_program* program, struct uc_datum_stack* dstack, struct uc_char_stack* cstack);

#endif
