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
 * Handles reading data from the UpperCase language.
 */
#ifndef _UC_MODULE_DATA_H_
#define _UC_MODULE_DATA_H_

/**
 * The data state
 */
void *uc_data_state(void);

/**
 * Handles string data types
 */
void *uc_string_state(void);

/**
 * Handles letters
 */
void *uc_letter_state(void);

/**
 * Handles uppercase letters
 */
void *uc_uppercase_state(void);

/**
 * Handles lowercase letters
 */
void *uc_lowercase_state(void);

/**
 * Handles whitespace characters
 */
void *uc_whitespace_state(void);

#endif