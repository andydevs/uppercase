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

#include "data/data.h"
#include "uppercase/statemachine.h"
#include "uppercase/program.h"
#include "uppercase/datum_stack.h"
#include "uppercase/char_stack.h"
#include "uppercase/error.h"

//----------------------------HELPER HEADERS-----------------------------

/**
 * Parses an uppercase letter from the current character
 *
 * @param program uc program struct
 *
 * @returns uppercase letter parsed from the current character
 */
static char uc_uppercase(struct uc_program* program);

/**
 * Parses a lowercase letter from the current character
 *
 * @param program uc program struct
 *
 * @returns lowercase letter parsed from the current character
 */
static char uc_lowercase(struct uc_program* program);

/**
 * Parses a whitespace character from the current character
 *
 * @param program uc program struct
 *
 * @returns whitespace character from the current character
 */
static char uc_whitespace(struct uc_program* program);

/**
 * Parses a punctuation character from the current character
 *
 * @param program uc program struct
 *
 * @returns punctuation character from the current character
 */
static char uc_punctuation(struct uc_program* program);

/**
 * Parses an integer digit from the current character
 *
 * @param program uc program struct
 *
 * @returns integer digit from the current character
 */
static char uc_integer_digit(struct uc_program* program);

/**
 * Parses a float digit from the current character
 *
 * @param program uc program struct
 *
 * @returns float digit from the current character
 */
static char uc_float_digit(struct uc_program* program);

/**
 * Adds the given character as a datum to the stack
 *
 * @param program           uc program struct
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character_data(struct uc_program* program, char c, void* next_state, const char* state_description);

/**
 * Adds the given character to the char stack
 *
 * @param program           uc program struct
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character(struct uc_program* program, char c, void* next_state, const char* state_description);

/**
 * Terminates a long data sequence and adds it to the stack as the given type
 *
 * @param program           uc program struct
 * @param type 				the type of the datum to add from the char stack 
 *							(must be string, float, or int)
 * @param state_description the description of the current state to print
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_end_long_data(struct uc_program* program, uc_datum_type type, const char* state_description);



//----------------------------DATA STATE----------------------------

/**
 * The data state
 */
void *uc_data_state(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'C':
			return (void*)&uc_character_state;
		case 'B':
			return (void*)&uc_boolean_state;
		case 'S':
			uc_char_stack_clear();
			return (void*)&uc_string_state;
		case 'I':
			uc_char_stack_clear();
			return (void*)&uc_integer_state;
		case 'F':
			uc_char_stack_clear();
			return (void*)&uc_float_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> data");
	}
}



//---------------------------STRING STATE---------------------------

/**
 * state string
 *
 * Handles string data types
 */
void *uc_string_state(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'L':
			return (void*)&uc_string_letter_state;
		case 'W':
			return (void*)&uc_string_whitespace_state;
		case 'P':
			return (void*)&uc_string_punctuation_state;
		case 'E':
			return uc_end_long_data(program, STRING, "main -> data -> string");
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> data -> string");
	}
}

/**
 * state string_letter
 *
 * Handles letters in strings
 */
void *uc_string_letter_state(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'U':
			return (void *)&uc_string_uppercase_state;
		case 'L':
			return (void *)&uc_string_lowercase_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> data -> string -> string_letter");
	}	
}

/**
 * state string_uppercase
 *
 * Handles uppercase letters in strings
 */
void *uc_string_uppercase_state(struct uc_program* program)
{
	return uc_add_character(program, uc_uppercase(program), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

/**
 * state string_lowercase
 *
 * Handles lowercase letters in strings
 */
void *uc_string_lowercase_state(struct uc_program* program)
{
	return uc_add_character(program, uc_lowercase(program), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

/**
 * state string_whitespace
 *
 * Handles whitespace characters in strings
 */
void *uc_string_whitespace_state(struct uc_program* program)
{
	return uc_add_character(program, uc_whitespace(program), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

/**
 * state string_punctuation
 *
 * Handles punctuation in strings
 */
void *uc_string_punctuation_state(struct uc_program* program)
{
	return uc_add_character(program, uc_punctuation(program), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

//--------------------------CHARACTER STATE-------------------------

/**
 * state character
 * 
 * Handles string data types
 */
void *uc_character_state(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'L':
			return (void *)&uc_character_letter_state;
		case 'W':
			return (void *)&uc_character_whitespace_state;
		case 'P':
			return (void *)&uc_character_punctuation_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> data -> character");
	}
}

/**
 * state character_letter
 *
 * Handles letters
 */
void *uc_character_letter_state(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'U':
			return (void *)&uc_character_uppercase_state;
		case 'L':
			return (void *)&uc_character_lowercase_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> data -> character -> character_letter");
	}
}

/**
 * state character_uppercase
 *
 * Handles uppercase letters
 */
void *uc_character_uppercase_state(struct uc_program* program)
{
	return uc_add_character_data(program, uc_uppercase(program), (void*)&uc_main_state, "main -> data -> character -> character_letter -> character_uppercase");
}

/**
 * state character_lowercase
 *
 * Handles lowercase letters
 */
void *uc_character_lowercase_state(struct uc_program* program)
{
	return uc_add_character_data(program, uc_lowercase(program), (void*)&uc_main_state, "main -> data -> character -> character_letter -> character_lowercase");
}

/**
 * state character_whitespace
 *
 * Handles whitespace characters
 */
void *uc_character_whitespace_state(struct uc_program* program)
{
	return uc_add_character_data(program, uc_whitespace(program), (void*)&uc_main_state, "main -> data -> character -> character_whitespace");
}

/**
 * state character_punctuation
 *
 * Handles punctuation
 */
void *uc_character_punctuation_state(struct uc_program* program)
{
	return uc_add_character_data(program, uc_punctuation(program), (void*)&uc_main_state, "main -> data -> character -> character_punctuation");
}



//----------------------------NUMBER STATE--------------------------

/**
 * state boolean
 *
 * Handles booleans
 */
void *uc_boolean_state(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'T':
			uc_datum_stack_push(uc_datum_from_boolean(1));
			return (void*)&uc_main_state;
		case 'F':
			uc_datum_stack_push(uc_datum_from_boolean(0));
			return (void*)&uc_main_state;
		default:
			return uc_throw_error(program, UC_CHAR_NOT_FOUND, "main -> data -> boolean");
	}
}

/**
 * state integer
 *
 * Handles integers
 */
void *uc_integer_state(struct uc_program* program)
{
	if (uc_program_current_character(program) == 'E')
	{
		return uc_end_long_data(program, INT, "main -> data -> integer");
	}
	else
	{
		return uc_add_character(program, uc_integer_digit(program), (void*)&uc_integer_state, "main -> data -> integer");
	}
}

/**
 * state float
 *
 * Handles floats
 */
void *uc_float_state(struct uc_program* program)
{
	if (uc_program_current_character(program) == 'E')
	{
		return uc_end_long_data(program, FLOAT, "main -> data -> float");
	}
	else
	{
		return uc_add_character(program, uc_float_digit(program), (void*)&uc_float_state, "main -> data -> float");
	}
}



//----------------------------HELPER FUNCTIONS----------------------------

/**
 * Parses an uppercase letter from the current character
 *
 * @param program uc program struct
 *
 * @returns uppercase letter parsed from the current character
 */
static char uc_uppercase(struct uc_program* program)
{
	return uc_program_current_character(program);
}

/**
 * Parses a lowercase letter from the current character
 *
 * @param program uc program struct
 *
 * @returns lowercase letter parsed from the current character
 */
static char uc_lowercase(struct uc_program* program)
{
	return (char)(uc_program_current_character(program) + 32);
}

/**
 * Parses a whitespace character from the current character
 *
 * @param program uc program struct
 *
 * @returns whitespace character from the current character
 */
static char uc_whitespace(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'S':
			return ' ';
		case 'N':
			return '\n';
		default:
			return 0;
	}
}

/**
 * Parses a punctuation character from the current character
 *
 * @param program uc program struct
 *
 * @returns punctuation character from the current character
 */
static char uc_punctuation(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'P':
			return '.';
		case 'E':
			return '!';
		case 'Q':
			return '?';
		case 'C':
			return ',';
		case 'A':
			return '\'';
		default:
			return 0;
	}
}

/**
 * Parses an integer digit from the current character
 *
 * @param program uc program struct
 *
 * @returns integer digit from the current character
 */
static char uc_integer_digit(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'A':
			return '0';
		case 'B':
			return '1';
		case 'C':
			return '2';
		case 'D':
			return '3';
		case 'F':
			return '4';
		case 'G':
			return '5';
		case 'H':
			return '6';
		case 'I':
			return '7';
		case 'J':
			return '8';
		case 'K':
			return '9';
		default:
			return 0;
	}
}

/**
 * Parses a float digit from the current character
 *
 * @param program uc program struct
 *
 * @returns float digit from the current character
 */
static char uc_float_digit(struct uc_program* program)
{
	switch(uc_program_current_character(program))
	{
		case 'A':
			return '0';
		case 'B':
			return '1';
		case 'C':
			return '2';
		case 'D':
			return '3';
		case 'F':
			return '4';
		case 'G':
			return '5';
		case 'H':
			return '6';
		case 'I':
			return '7';
		case 'J':
			return '8';
		case 'K':
			return '9';
		case 'P':
			return '.';
		default:
			return 0;
	}
}

/**
 * Adds the given character as a datum to the stack
 *
 * @param program           uc program struct
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character(struct uc_program* program, char c, void* next_state, const char* state_description)
{
	if (c == 0)
	{
		return uc_throw_error(program, UC_CHAR_NOT_FOUND, state_description);
	}
	else if (uc_char_stack_push(c))
	{
		return next_state;
	}
	else
	{
		return uc_throw_error(program, UC_CHAR_STACK_FULL, state_description);
	}
}

/**
 * Adds the given character to the char stack
 *
 * @param program           uc program struct
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_end_long_data(struct uc_program* program, uc_datum_type type, const char* state_description)
{
	if (uc_char_stack_push('\0'))
	{
		uc_datum *d;
		switch(type)
		{
			case STRING:
				d = uc_char_stack_get_string();
				break;
			case FLOAT:
				d = uc_char_stack_get_float();
				break;
			case INT:
				d = uc_char_stack_get_integer();
				break;
			default:
				break;
		}
		if (uc_datum_stack_push(d))
		{
			return (void*)&uc_main_state;
		}
		else
		{
			return uc_throw_error(program, UC_STACK_FULL, state_description);
		}
	}
	else
	{
		return uc_throw_error(program, UC_CHAR_STACK_FULL, state_description);
	}
}

/**
 * Terminates a long data sequence and adds it to the stack as the given type
 *
 * @param program           uc program struct
 * @param type 				the type of the datum to add from the char stack 
 *							(must be string, float, or int)
 * @param state_description the description of the current state to print
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character_data(struct uc_program* program, char c, void* next_state, const char* state_description)
{
	if (c == 0)
	{
		return uc_throw_error(program, UC_CHAR_NOT_FOUND, state_description);
	}
	else if (uc_datum_stack_push(uc_datum_from_char(c)))
	{
		return next_state;
	}
	else
	{
		return uc_throw_error(program, UC_CHAR_STACK_FULL, state_description);
	}
}
