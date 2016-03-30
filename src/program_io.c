#include "UpperCase/program_io.h"

#include <stdio.h>

/**
 * The program file
 */
static FILE *program;

/**
 * The current character
 */
static char current;

/**
 * Sets the program to the given filename
 *
 * @param filename the name of the file
 * 
 * @return true if the program was opened successfully
 */
int open_program(const char *filename)
{
	return (program = fopen(filename, "r")) != NULL;
}

/**
 * Returns the current character
 * 
 * @return the current character
 */
char current_character()
{
	return current;
}

/**
 * Returns true if the current character is not an uppercase letter
 *
 * @return true if the current character is not an uppercase letter
 */
int invalid_character()
{
	return !(current >= 'A' && current <= 'Z');
}

/**
 * Advances to the next character in the program file
 *
 * @return true if the next character is not the end of file
 */
int next_character()
{
	return (current = fgetc(program)) != EOF;
}

/**
 * Closes the program
 */
void close_program()
{
	fclose(program);
}