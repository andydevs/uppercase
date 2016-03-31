/**
 * Handles IO between the program file in UpperCase
 */
#ifndef _PROGRAM_IO_H_
#define _PROGRAM_IO_H_

/**
 * Sets the program to the given filename
 *
 * @param filename the name of the file
 * 
 * @return true if the program was opened successfully
 */
int open_program(const char *filename);

/**
 * Returns the current character
 * 
 * @return the current character
 */
char current_character();

/**
 * Returns true if the current character is not an uppercase letter
 *
 * @return true if the current character is not an uppercase letter
 */
int invalid_character();

/**
 * Advances to the next character in the program file
 *
 * @return true if the next character is not the end of file
 */
int next_character();

/**
 * Closes the program
 */
void close_program();

#endif