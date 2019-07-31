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
 * Handles IO between the program file in UpperCase
 */
#ifndef _UC_PROGRAM_IO_H_
#define _UC_PROGRAM_IO_H_

/**
 * The number of uppercase letters in the alphabet
 */
#define NUMBER_OF_LETTERS 26

// Includes
#include <stdio.h>

/**
 * The program file data structure
 */
struct uc_program {
	FILE* file;
	char current;
};

/**
 * Opens an uppercase program from the given filename
 *
 * @param filename the name of the file
 * 
 * @return program data structure
 */
struct uc_program* uc_program_open(const char* filename);

/**
 * Returns the current character in the program
 *
 * @param program uppercase program struct 
 *
 * @return the current character in the program
 */
char uc_program_current_character(struct uc_program* program);

/**
 * Returns true if the current character is not an uppercase letter
 *
 * @param program uppercase program struct 
 *
 * @return true if the current character is not an uppercase letter
 */
int uc_program_invalid_character(struct uc_program* program);

/**
 * Advances to the next character in the program file
 *
 * @param program uppercase program struct 
 */
void uc_program_next(struct uc_program* program);

/**
 * Returns true if the next character is not the end of file
 *
 * @param program uppercase program struct 
 *
 * @return true if the next character is not the end of file
 */
int uc_program_continue(struct uc_program* program);

/**
 * Closes the program
 * 
 * @param program pointer to uppercase program struct  
 */
void uc_program_close(struct uc_program** program);

#endif
