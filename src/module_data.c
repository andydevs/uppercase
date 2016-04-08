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



//----------------------------STATE FUNCTIONS----------------------------

/**
 * The data state
 */
void *uc_data_state(void)
{
	switch(uc_current_character())
	{
		case 'C':
			return (void *)&uc_character_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data");
	}
}

/**
 * Handles string data types
 */
void *uc_character_state(void)
{
	switch(uc_current_character())
	{
		case 'L':
			return (void *)&uc_letter_state;
		case 'W':
			return (void *)&uc_whitespace_state;
		case 'P':
			return (void *)&uc_punctuation_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character");
	}
}

/**
 * Handles letters
 */
void *uc_letter_state(void)
{
	switch(uc_current_character())
	{
		case 'U':
			return (void *)&uc_uppercase_state;
		case 'L':
			return (void *)&uc_lowercase_state;
		default:
			return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> letter");
	}
}

/**
 * Handles uppercase letters
 */
void *uc_uppercase_state(void)
{
	char c = uc_uppercase();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> letter -> uppercase");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> letter -> uppercase");
	}
}

/**
 * Handles lowercase letters
 */
void *uc_lowercase_state(void)
{
	char c = uc_lowercase();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> letter -> lowercase");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> letter -> lowercase");
	}
}

/**
 * Handles whitespace characters
 */
void *uc_whitespace_state(void)
{
	char c = uc_whitespace();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> whitespace");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> letter -> whitespace");
	}
}

/**
 * Handles punctuation
 */
void *uc_punctuation_state(void)
{
	char c = uc_punctuation();
	if (c == 0)
	{
		return uc_throw_error(UC_CHAR_NOT_FOUND, "main -> data -> character -> punctuation");
	}
	else if (uc_stack_push(uc_datum_from_char(c)))
	{
		return (void *)&uc_main_state;
	}
	else
	{
		return uc_throw_error(UC_STACK_FULL, "main -> data -> character -> letter -> punctuation");
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