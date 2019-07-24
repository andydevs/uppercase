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

// Program files being used
#include "uppercase/program.h"
#include "uppercase/statemachine.h"

#include <stdio.h>

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
		printf("ERROR! File must be specified!\n");
		return 1;
	}

	// Open the file (return error if failed)
	if (!uc_open_program(argv[1]))
	{
		printf("ERROR! Something went wrong when reading the file!\n");
		return 1;
	}

	// Run program
	int status = uc_state_machine_run();

	// Close program 
	uc_close_program();
	
	// Exit status
	return status;
}
