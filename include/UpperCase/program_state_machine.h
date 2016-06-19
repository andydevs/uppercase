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
 * Handles state machine code
 */
#ifndef _UC_STATE_MACHINE_H_
#define _UC_STATE_MACHINE_H_

//----------------------------THE FOUNDATION-----------------------------

/**
 * The uc_state type is a function pointer which returns a void pointer
 */
typedef void *(*uc_state)(void);

/**
 * Runs the UpperCase state machine.
 *
 * @return true if the state machine ran unsuccessfully
 */
int uc_state_machine_run(void);

/**
 * state main
 * 
 * This is where the state machine starts
 */
void *uc_main_state(void);


//----------------------------MODULE SYSTEM-----------------------------

/**
 * Registers the given state function (representing a module) to the registry used by the main state
 * 
 * @param name the letter name to be used to call the function
 * @param function the function being set to the name
 *
 * @return status code indicating successful registration of module to letter
 */
int uc_register_module(char name, uc_state function);

/**
 * Returns the module represented by the current character
 *
 * @return the module represented by the current character
 */
uc_state uc_registry_get_module();

#endif