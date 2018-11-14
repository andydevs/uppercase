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

#include "UpperCase/data.h"
#include "UpperCase/state_machine.h"
#include "UpperCase/io.h"
#include "UpperCase/stack.h"
#include "UpperCase/error.h"

//----------------------------HELPER HEADERS-----------------------------

/**
 * Parses an uppercase letter from the current character
 *
 * @returns uppercase letter parsed from the current character
 */
static char uc_uppercase(void);

/**
 * Parses a lowercase letter from the current character
 *
 * @returns lowercase letter parsed from the current character
 */
static char uc_lowercase(void);

/**
 * Parses a whitespace character from the current character
 *
 * @returns whitespace character from the current character
 */
static char uc_whitespace(void);

/**
 * Parses a punctuation character from the current character
 *
 * @returns punctuation character from the current character
 */
static char uc_punctuation(void);

/**
 * Parses an integer digit from the current character
 *
 * @returns integer digit from the current character
 */
static char uc_integer_digit(void);

/**
 * Parses a float digit from the current character
 *
 * @returns float digit from the current character
 */
static char uc_float_digit(void);

/**
 * Adds the given character as a datum to the stack
 *
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character_data(char c, void* next_state, const char* state_description);

/**
 * Adds the given character to the char stack
 *
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character(char c, void* next_state, const char* state_description);

/**
 * Terminates a long data sequence and adds it to the stack as the given type
 *
 * @param type 				the type of the datum to add from the char stack 
 *							(must be string, float, or int)
 * @param state_description the description of the current state to print
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_end_long_data(uc_datum_type type, const char* state_description);



//----------------------------DATA STATE----------------------------

/**
 * The data state
 */
void *uc_data_state(void)
{
	switch(uc_current_character())
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
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data");
	}
}



//---------------------------STRING STATE---------------------------

/**
 * state string
 *
 * Handles string data types
 */
void *uc_string_state(void)
{
	switch(uc_current_character())
	{
		case 'L':
			return (void*)&uc_string_letter_state;
		case 'W':
			return (void*)&uc_string_whitespace_state;
		case 'P':
			return (void*)&uc_string_punctuation_state;
		case 'E':
			return uc_end_long_data(STRING, "main -> data -> string");
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> string");
	}
}

/**
 * state string_letter
 *
 * Handles letters in strings
 */
void *uc_string_letter_state(void)
{
	switch(uc_current_character())
	{
		case 'U':
			return (void *)&uc_string_uppercase_state;
		case 'L':
			return (void *)&uc_string_lowercase_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> string -> string_letter");
	}	
}

/**
 * state string_uppercase
 *
 * Handles uppercase letters in strings
 */
void *uc_string_uppercase_state(void)
{
	return uc_add_character(uc_uppercase(), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

/**
 * state string_lowercase
 *
 * Handles lowercase letters in strings
 */
void *uc_string_lowercase_state(void)
{
	return uc_add_character(uc_lowercase(), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

/**
 * state string_whitespace
 *
 * Handles whitespace characters in strings
 */
void *uc_string_whitespace_state(void)
{
	return uc_add_character(uc_whitespace(), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

/**
 * state string_punctuation
 *
 * Handles punctuation in strings
 */
void *uc_string_punctuation_state(void)
{
	return uc_add_character(uc_punctuation(), (void*)&uc_string_state, "main -> data -> string -> string_punctuation");
}

//--------------------------CHARACTER STATE-------------------------

/**
 * state character
 * 
 * Handles string data types
 */
void *uc_character_state(void)
{
	switch(uc_current_character())
	{
		case 'L':
			return (void *)&uc_character_letter_state;
		case 'W':
			return (void *)&uc_character_whitespace_state;
		case 'P':
			return (void *)&uc_character_punctuation_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character");
	}
}

/**
 * state character_letter
 *
 * Handles letters
 */
void *uc_character_letter_state(void)
{
	switch(uc_current_character())
	{
		case 'U':
			return (void *)&uc_character_uppercase_state;
		case 'L':
			return (void *)&uc_character_lowercase_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> character_letter");
	}
}

/**
 * state character_uppercase
 *
 * Handles uppercase letters
 */
void *uc_character_uppercase_state(void)
{
	return uc_add_character_data(uc_uppercase(), (void*)&uc_main_state, "main -> data -> character -> character_letter -> character_uppercase");
}

/**
 * state character_lowercase
 *
 * Handles lowercase letters
 */
void *uc_character_lowercase_state(void)
{
	return uc_add_character_data(uc_lowercase(), (void*)&uc_main_state, "main -> data -> character -> character_letter -> character_lowercase");
}

/**
 * state character_whitespace
 *
 * Handles whitespace characters
 */
void *uc_character_whitespace_state(void)
{
	return uc_add_character_data(uc_whitespace(), (void*)&uc_main_state, "main -> data -> character -> character_whitespace");
}

/**
 * state character_punctuation
 *
 * Handles punctuation
 */
void *uc_character_punctuation_state(void)
{
	return uc_add_character_data(uc_punctuation(), (void*)&uc_main_state, "main -> data -> character -> character_punctuation");
}



//----------------------------NUMBER STATE--------------------------

/**
 * state boolean
 *
 * Handles booleans
 */
void *uc_boolean_state(void)
{
	switch(uc_current_character())
	{
		case 'T':
			uc_stack_push(uc_datum_from_boolean(1));
			return (void*)&uc_main_state;
		case 'F':
			uc_stack_push(uc_datum_from_boolean(0));
			return (void*)&uc_main_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> boolean");
	}
}

/**
 * state integer
 *
 * Handles integers
 */
void *uc_integer_state(void)
{
	if (uc_current_character() == 'E')
	{
		return uc_end_long_data(INT, "main -> data -> integer");
	}
	else
	{
		return uc_add_character(uc_integer_digit(), (void*)&uc_integer_state, "main -> data -> integer");
	}
}

/**
 * state float
 *
 * Handles floats
 */
void *uc_float_state(void)
{
	if (uc_current_character() == 'E')
	{
		return uc_end_long_data(FLOAT, "main -> data -> float");
	}
	else
	{
		return uc_add_character(uc_float_digit(), (void*)&uc_float_state, "main -> data -> float");
	}
}



//----------------------------HELPER FUNCTIONS----------------------------

/**
 * Parses an uppercase letter from the current character
 *
 * @returns uppercase letter parsed from the current character
 */
static char uc_uppercase(void)
{
	return uc_current_character();
}

/**
 * Parses a lowercase letter from the current character
 *
 * @returns lowercase letter parsed from the current character
 */
static char uc_lowercase(void)
{
	return (char)(uc_current_character() + 32);
}

/**
 * Parses a whitespace character from the current character
 *
 * @returns whitespace character from the current character
 */
static char uc_whitespace(void)
{
	switch(uc_current_character())
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
 * @returns punctuation character from the current character
 */
static char uc_punctuation(void)
{
	switch(uc_current_character())
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
 * @returns integer digit from the current character
 */
static char uc_integer_digit(void)
{
	switch(uc_current_character())
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
 * @returns float digit from the current character
 */
static char uc_float_digit(void)
{
	switch(uc_current_character())
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
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character(char c, void* next_state, const char* state_description)
{
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, state_description);
	}
	else if (uc_char_stack_push(c))
	{
		return next_state;
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, state_description);
	}
}

/**
 * Adds the given character to the char stack
 *
 * @param c 		 		the character to add
 * @param next_state 		the next state to transition to 
 * 					 		if the character is successfully added
 * @param state_description the description of the current state to print 
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_end_long_data(uc_datum_type type, const char* state_description)
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
		if (uc_stack_push(d))
		{
			return (void*)&uc_main_state;
		}
		else
		{
			return uc_throw_error(UC_STACK_FULL, state_description);
		}
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, state_description);
	}
}

/**
 * Terminates a long data sequence and adds it to the stack as the given type
 *
 * @param type 				the type of the datum to add from the char stack 
 *							(must be string, float, or int)
 * @param state_description the description of the current state to print
 *							if an error is thrown
 *
 * @return the next state depending on if the character is successfully added
 */
static void* uc_add_character_data(char c, void* next_state, const char* state_description)
{
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, state_description);
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return next_state;
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, state_description);
	}
}
