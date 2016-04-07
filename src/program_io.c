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