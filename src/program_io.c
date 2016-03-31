#include "UpperCase/program_io.h"

#include <stdio.h>

/**
 * The program file
 */
static FILE *uc_program;

/**
 * The current character
 */
static char uc_current;

/**
 * Sets the program to the given filename
 *
 * @param filename the name of the file
 * 
 * @return true if the program was opened successfully
 */
int uc_open_program(const char *filename)
{
	return (uc_program = fopen(filename, "r")) != NULL;
}

/**
 * Returns the current character
 * 
 * @return the current character
 */
char uc_current_character()
{
	return uc_current;
}

/**
 * Returns true if the current character is not an uppercase letter
 *
 * @return true if the current character is not an uppercase letter
 */
int uc_invalid_character()
{
	return !(uc_current >= 'A' && uc_current <= 'Z');
}

/**
 * Advances to the next character in the program file
 *
 * @return true if the next character is not the end of file
 */
int uc_next_character()
{
	return (uc_current = fgetc(uc_program)) != EOF;
}

/**
 * Closes the program
 */
void uc_close_program()
{
	fclose(uc_program);
}