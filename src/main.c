#include <stdio.h>
#include "UpperCase/main.h"

/**
 * The main method of the program
 * 
 * @param argc the number of command line arguments (must be 2)
 * @param argv the command line arguments (second argument specifies the name of the file being read)
 *
 * @return the exit status of the program
 */
int main(int argc, char const *argv[])
{
	// Test if filename is given (print error if not)
	if (argc < 2)
	{
		printf("ERROR! Filename must be specified in arguments!\n");
		return 1;
	}

	// Open the file (return error if failed)
	program = fopen(argv[1], "r");
	if (program == NULL)
	{
		printf("ERROR! Something went wrong when reading the file\n");
		return 1;
	}

	// Read for each character in the file
	char c;
	while((c = fgetc(program)) != EOF)
	{
		// Validate that character is an uppercase letter
		// If not, print error message and end program with exit status 1
		if (!(c >= 'A' && c <= 'Z'))
		{
			printf(" --> ERROR: Invalid character! Must be an uppercase letter!\n");
			fclose(program);	
			return 1;
		}

		// Print character
		printf("%c\n", c);
	}

	// Close file and exit the program
	fclose(program);
	return 0;
}