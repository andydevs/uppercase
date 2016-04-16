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

#ifndef _UC_DATUM_H_
#define _UC_DATUM_H_

/**
 * Represents a type of data
 *
 * Can be either boolean, float, char, or integer
 */
typedef enum 
{
	STRING,
	BOOLEAN,
	FLOAT,
	CHAR,
	INT
}
uc_datum_type;

/**
 * Represents a unit of data of arbitrary type
 *
 * Defines the type of that data, and the value 
 * as a union of boolean, float, char, and integer
 */
typedef struct
{
	uc_datum_type type;
	union
	{
		char *string_value;
		int boolean_value:2;
		double float_value;
		char char_value;
		int integer_value;
	}
	value;
}
uc_datum;

/**
 * Creates a new boolean uc_datum value from the given value
 *
 * @param value the boolean value of the uc_datum
 *
 * @return a new boolean uc_datum value from the given value
 */
uc_datum *uc_datum_from_boolean(int value);

/**
 * Creates a new float uc_datum value from the given value
 *
 * @param value the float value of the uc_datum
 *
 * @return a new float uc_datum value from the given value
 */
uc_datum *uc_datum_from_float(double value);

/**
 * Creates a new char uc_datum value from the given value
 *
 * @param value the char value of the uc_datum
 *
 * @return a new char uc_datum value from the given value
 */
uc_datum *uc_datum_from_char(char value);

/**
 * Creates a new integer uc_datum value from the given value
 *
 * @param value the integer value of the uc_datum
 *
 * @return a new integer uc_datum value from the given value
 */
uc_datum *uc_datum_from_integer(int value);

/**
 * Creates a new string uc_datum value from the given value
 *
 * @param value the string value of the uc_datum
 *
 * @return a new string uc_datum value from the given value
 */
uc_datum *uc_datum_from_string(char *value);

/**
 * Creates a new string uc_datum value from the given value (as a const char*)
 *
 * @param value the string value of the uc_datum (as a const char*)
 *
 * @return a new string uc_datum value from the given value
 */
uc_datum *uc_datum_from_const_string(const char *value);

/**
 * Prints the given datum to the console
 *
 * @param d the datum being printed
 */
void uc_datum_print(uc_datum *d);

/**
 * Prints a detailed description of the datum to the console
 *
 * @param d the datum being inspected
 */
void uc_datum_inspect(uc_datum *d);

/**
 * Destroys the given datum
 *
 * @param d the datum to destroy
 */
void uc_datum_destroy(uc_datum *d);

#endif