#include "UpperCase/module_data.h"
#include "UpperCase/state_machine.h"
#include "UpperCase/program_io.h"

#include <stdlib.h>
#include <stdio.h>

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



//----------------------------STATE FUNCTIONS----------------------------

/**
 * The data state
 */
void *uc_data_state(void)
{
	switch(uc_current_character())
	{
		case 'S':
			return (void *)&uc_string_state;
		default:
			return NULL;
	}
}

/**
 * Handles string data types
 */
void *uc_string_state(void)
{
	switch(uc_current_character())
	{
		case 'L':
			return (void *)&uc_letter_state;
		case 'W':
			return (void *)&uc_whitespace_state;
		case 'E':
			return (void *)&uc_main_state;
		default:
			return NULL;
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
			return NULL;
	}
}

/**
 * Handles uppercase letters
 */
void *uc_uppercase_state(void)
{
	printf("%c", uc_uppercase());
	return (void *)&uc_string_state;
}

/**
 * Handles lowercase letters
 */
void *uc_lowercase_state(void)
{
	printf("%c", uc_lowercase());
	return (void *)&uc_string_state;
}

/**
 * Handles whitespace characters
 */
void *uc_whitespace_state(void)
{
	printf("%c", uc_whitespace());
	return (void *)&uc_string_state;
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
 */
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