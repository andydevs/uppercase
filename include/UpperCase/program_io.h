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

/**
 * Sets the program to the given filename
 *
 * @param filename the name of the file
 * 
 * @return true if the program was opened successfully
 */
int uc_open_program(const char *filename);

/**
 * Returns the current character
 * 
 * @return the current character
 */
char uc_current_character();

/**
 * Returns true if the current character is not an uppercase letter
 *
 * @return true if the current character is not an uppercase letter
 */
int uc_invalid_character();

/**
 * Advances to the next character in the program file
 *
 * @return true if the next character is not the end of file
 */
int uc_next_character();

/**
 * Closes the program
 */
void uc_close_program();

#endif