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

#include "UpperCase/module_data.h"
#include "UpperCase/state_machine.h"
#include "UpperCase/program_io.h"
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
 * Ends the current string
 *
 * @return the next state which depends on 
 *		   if the current string was ended successfully
 */
static void* uc_end_string(void);




//----------------------------STATE FUNCTIONS----------------------------

/**
 * The data state
 */
void *uc_data_state(void)
{
	switch(uc_current_character())
	{
		case 'C':
			return (void*)&uc_character_state;
		case 'S':
			uc_char_stack_clear();
			return (void*)&uc_string_state;
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
			return uc_end_string();
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
	char c = uc_uppercase();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> string -> string_letter -> string_uppercase");
	}
	else if (uc_char_stack_push(c))
	{
		return (void *)&uc_string_state;
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, "main -> data -> string -> string_letter -> string_uppercase");
	}
}

/**
 * state string_lowercase
 *
 * Handles lowercase letters in strings
 */
void *uc_string_lowercase_state(void)
{
	char c = uc_lowercase();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> string -> string_letter -> string_lowercase");
	}
	else if (uc_char_stack_push(c))
	{
		return (void *)&uc_string_state;
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, "main -> data -> string -> string_letter -> string_lowercase");
	}
}

/**
 * state string_whitespace
 *
 * Handles whitespace characters in strings
 */
void *uc_string_whitespace_state(void)
{
	char c = uc_whitespace();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> string -> string_whitespace");
	}
	else if (uc_char_stack_push(c))
	{
		return (void *)&uc_string_state;
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, "main -> data -> string -> string_whitespace");
	}
}

/**
 * state string_punctuation
 *
 * Handles punctuation in strings
 */
void *uc_string_punctuation_state(void)
{
	char c = uc_punctuation();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> string -> string_punctuation");
	}
	else if (uc_char_stack_push(c))
	{
		return (void *)&uc_string_state;
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, "main -> data -> string -> string_punctuation");
	}
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
	char c = uc_uppercase();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> character_letter -> character_uppercase");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> character_letter -> character_uppercase");
	}
}

/**
 * state character_lowercase
 *
 * Handles lowercase letters
 */
void *uc_character_lowercase_state(void)
{
	char c = uc_lowercase();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> character_letter -> character_lowercase");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> character_letter -> character_lowercase");
	}
}

/**
 * state character_whitespace
 *
 * Handles whitespace characters
 */
void *uc_character_whitespace_state(void)
{
	char c = uc_whitespace();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> character_whitespace");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> character_whitespace");
	}
}

/**
 * state character_punctuation
 *
 * Handles punctuation
 */
void *uc_character_punctuation_state(void)
{
	char c = uc_punctuation();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> character_punctuation");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> character_punctuation");
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
 * Ends the current string
 *
 * @return the next state which depends on 
 *		   if the current string was ended successfully
 */
static void* uc_end_string(void)
{
	if (uc_char_stack_push('\0'))
	{
		if (uc_stack_push(uc_char_stack_get_string()))
		{
			return (void*)&uc_main_state;
		}
		else
		{
			return uc_throw_error(UC_STACK_FULL, "main -> data -> string -> end");
		}
	}
	else
	{
		return uc_throw_error(UC_CHAR_STACK_FULL, "main -> data -> string -> end");
	}
}
