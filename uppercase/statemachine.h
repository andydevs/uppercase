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

#include "uppercase/program.h"
#include "uppercase/char_stack.h"

//----------------------------THE FOUNDATION-----------------------------

/**
 * The uc_state type is a function pointer which returns a void pointer
 */
typedef void *(*uc_state)(struct uc_program* program, struct uc_char_stack* cstack);

/**
 * Runs the UpperCase state machine.
 *
 * @return true if the state machine ran unsuccessfully
 */
int uc_state_machine_run(struct uc_program* program);

/**
 * state main
 * 
 * This is where the state machine starts
 */
void *uc_main_state(struct uc_program* program, struct uc_char_stack* cstack);

#endif
