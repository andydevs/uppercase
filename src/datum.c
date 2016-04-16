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

#include "UpperCase/datum.h"

/**
 * Headers being used
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------HELPER HEADERS-----------------------------

/**
 * Prints a representation of the given character for inspection
 *
 * @param c the character to inspect
 */
static void uc_inspect_character(char c);



//-----------------------------CONSTRUCTORS-----------------------------

/**
 * Creates a new boolean uc_datum value from the given value
 * 
 * @param value the boolean value of the uc_datum
 * 
 * @return a new boolean uc_datum value from the given value
 */
uc_datum *uc_datum_from_boolean(int value)
{
	uc_datum *d = (uc_datum *)malloc(sizeof(uc_datum));
	d->type = BOOLEAN;
	d->value.boolean_value = value > 0;
	return d;
}

/**
 * Creates a new boolean uc_datum value from the given value
 *
 * @param value the boolean value of the uc_datum
 *
 * @return a new boolean uc_datum value from the given value
 */
uc_datum *uc_datum_from_float(double value)
{
	uc_datum *d = (uc_datum *)malloc(sizeof(uc_datum));
	d->type = FLOAT;
	d->value.float_value = value;
	return d;
}

/**
 * Creates a new char uc_datum value from the given value
 *
 * @param value the char value of the uc_datum
 *
 * @return a new char uc_datum value from the given value
 */
uc_datum *uc_datum_from_char(char value)
{
	uc_datum *d = (uc_datum *)malloc(sizeof(uc_datum));
	d->type = CHAR;
	d->value.char_value = value;
	return d;
}

/**
 * Creates a new integer uc_datum value from the given value
 *
 * @param value the integer value of the uc_datum
 *
 * @return a new integer uc_datum value from the given value
 */
uc_datum *uc_datum_from_integer(int value)
{
	uc_datum *d = (uc_datum *)malloc(sizeof(uc_datum));
	d->type = INT;
	d->value.integer_value = value;
	return d;
}

/**
 * Creates a new string uc_datum value from the given value
 *
 * @param value the string value of the uc_datum
 *
 * @return a new string uc_datum value from the given value
 */
uc_datum *uc_datum_from_string(char *value)
{	
	uc_datum *d = (uc_datum *)malloc(sizeof(uc_datum));
	d->type = STRING;
	d->value.string_value = value;
	return d;
}

/**
 * Creates a new string uc_datum value from the given value (as a const char*)
 *
 * @param value the string value of the uc_datum (as a const char*)
 *
 * @return a new string uc_datum value from the given value
 */
uc_datum *uc_datum_from_const_string(const char *value)
{
	uc_datum *d = (uc_datum *)malloc(sizeof(uc_datum));
	d->type = STRING;
	d->value.string_value = (char*)malloc(strlen(value));
	strcpy(d->value.string_value, value);
	return d;
}



//------------------------------FUNCTIONS-------------------------------

/**
 * Prints the given data to the console
 *
 * @param d the data being printed
 */
void uc_datum_print(uc_datum *d)
{
	switch(d->type)
	{
		case STRING:
			printf("%s", d->value.string_value);
			return;
		case BOOLEAN:
			printf("%c", (d->value.boolean_value > 0 ? 'T' : 'F'));
			return;
		case FLOAT:
			printf("%f", d->value.float_value);
			return;
		case CHAR:
			printf("%c", d->value.char_value);
			return;
		case INT:
			printf("%d", d->value.integer_value);
			return;
		default:
			return;
	}
}

/**
 * Prints a detailed description of the datum to the console
 *
 * @param d the datum being inspected
 */
void uc_datum_inspect(uc_datum *d)
{
	switch(d->type)
	{
		case STRING:
			printf("string: \"");
			for (int i = 0; i < strlen(d->value.string_value); ++i)
			{
				uc_inspect_character(d->value.string_value[i]);
			}
			printf("\"");
			return;
		case BOOLEAN:
			printf("boolean: %c", (d->value.boolean_value > 0 ? 'T' : 'F'));
			return;
		case FLOAT:
			printf("float: %f", d->value.float_value);
			return;
		case CHAR:
			printf("char: '");
			uc_inspect_character(d->value.char_value);
			printf("'");
			return;
		case INT:
			printf("int: %d", d->value.integer_value);
			return;
		default:
			printf("unknown type");
			return;
	}
}



//------------------------------DESTRUCTOR-------------------------------

/**
 * Destroys the given datum
 *
 * @param d the datum to destroy
 */
void uc_datum_destroy(uc_datum *d)
{
	if (d->type == STRING)
	{
		free(d->value.string_value);
	}
	free(d);
}



//---------------------------HELPER FUNCTIONS----------------------------

/**
 * Prints a representation of the given character for inspection
 *
 * @param c the character to inspect
 */
static void uc_inspect_character(char c)
{
	switch(c)
	{
		case '\n':
			printf("\\n");
			return;
		case '\t':
			printf("\\t");
			return;
		case '\r':
			printf("\\r");
			return;
		default:
			printf("%c", c);
			return;
	}
}