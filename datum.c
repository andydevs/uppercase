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

// Headers being used
#include "datum.h"

// Libraries being used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------HELPER HEADERS-----------------------------

//--------------ALLOCATE-------------

/**
 * Allocates space for a uc_datum object
 *
 * @return pointer to allocated space
 */
static uc_datum* uc_datum_allocate();

//--------------GETTYPE-------------

/**
 * Allocates space for a uc_datum object
 *
 * @return pointer to allocated space
 */
static uc_datum_type uc_datum_raw_type(uc_datum* d);

//--------------INSPECT--------------

/**
 * Prints a representation of the given character for inspection
 *
 * @param c the character to inspect
 */
static void uc_inspect_character(char c);


//-----------STRING CONCAT-----------

/**
 * Returns the concatenation of the two string data
 *
 * @param a the first string datum
 * @param b the second string datum
 *
 * @return the concatenation of the two string data
 */
static uc_datum* uc_datum_string_concat(uc_datum* a, uc_datum* b);

/**
 * Returns a string representing the datum
 *
 * @param a the datum to represent as a string
 *
 * @return a string representing the datum
 */
static char* uc_datum_repr_string(uc_datum* a);


//------------CHAR CONCAT------------

/**
 * Returns the concatenation of the two char data
 *
 * @param a the first char datum
 * @param b the second char datum
 *
 * @return the concatenation of the two char data
 */
static uc_datum* uc_datum_char_concat(uc_datum* a, uc_datum* b);


//-----------INTEGER OPERATIONS-----------

/**
 * Returns the addition of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the addition of the two integer data
 */
static uc_datum* uc_datum_integer_add(uc_datum* a, uc_datum* b);

/**
 * Returns the subtraction of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the subtraction of the two integer data
 */
static uc_datum* uc_datum_integer_subtract(uc_datum* a, uc_datum* b);

/**
 * Returns the multiplication of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the multiplication of the two integer data
 */
static uc_datum* uc_datum_integer_multiply(uc_datum* a, uc_datum* b);

/**
 * Returns the division of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the division of the two integer data
 */
static uc_datum* uc_datum_integer_divide(uc_datum* a, uc_datum* b);

/**
 * Returns the modulus of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the modulus of the two integer data
 */
static uc_datum* uc_datum_integer_modulus(uc_datum* a, uc_datum* b);

/**
 * Returns a integer representing the datum
 *
 * @param a the datum to represent as a integer
 *
 * @return a integer representing the datum
 */
static int uc_datum_repr_integer(uc_datum* a);


//-----------FLOAT OPERATIONS-----------

/**
 * Returns the addition of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the addition of the two float data
 */
static uc_datum* uc_datum_float_add(uc_datum* a, uc_datum* b);

/**
 * Returns the subtraction of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the subtraction of the two float data
 */
static uc_datum* uc_datum_float_subtract(uc_datum* a, uc_datum* b);

/**
 * Returns the multiplication of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the multiplication of the two float data
 */
static uc_datum* uc_datum_float_multiply(uc_datum* a, uc_datum* b);

/**
 * Returns the division of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the division of the two float data
 */
static uc_datum* uc_datum_float_divide(uc_datum* a, uc_datum* b);

/**
 * Returns a float representing the datum
 *
 * @param a the datum to represent as a float
 *
 * @return a float representing the datum
 */
static double uc_datum_repr_float(uc_datum* a);




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
	uc_datum *d = uc_datum_allocate();
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
	uc_datum *d = uc_datum_allocate();
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
	uc_datum *d = uc_datum_allocate();
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
	uc_datum *d = uc_datum_allocate();
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
	uc_datum *d = uc_datum_allocate();
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
	uc_datum *d = uc_datum_allocate();
	d->type = STRING;
	d->value.string_value = (char*)malloc(strlen(value));
	strcpy(d->value.string_value, value);
	return d;
}

/**
 * Creates a new reference uc_datum value from the given uc_datum
 *
 * @param value the reference value of the uc_datum
 *
 * @return a new reference uc_datum value from the given uc_datum
 */
uc_datum *uc_datum_from_reference(uc_datum *value)
{
	uc_datum *d = uc_datum_allocate();
	d->type = REFERENCE;
	d->value.reference_value = value;
	return d;
}

/**
 * Creates a new undefined uc_datum value
 *
 * @return a new undefined uc_datum value
 */
uc_datum *uc_datum_undefined()
{
	uc_datum *d = uc_datum_allocate();
	d->type = UNDEFINED;
	return d;
}



//------------------------------OPERATORS-------------------------------

/**
 * Returns the addition of the two given data
 *
 * @param a the first datum
 * @param b the second datum
 *
 * @return the addition of te two given data
 */
uc_datum* uc_datum_add(uc_datum* a, uc_datum* b)
{
	if (uc_datum_raw_type(a) == UNDEFINED || uc_datum_raw_type(b) == UNDEFINED)
	{
		return uc_datum_undefined();
	}
	else if (uc_datum_raw_type(a) == STRING || uc_datum_raw_type(b) == STRING)
	{
		return uc_datum_string_concat(a, b);
	}
	else if (uc_datum_raw_type(a) == CHAR && uc_datum_raw_type(b) == CHAR)
	{
		return uc_datum_char_concat(a, b);
	}
	else if (uc_datum_raw_type(a) == FLOAT || uc_datum_raw_type(b) == FLOAT)
	{
		return uc_datum_float_add(a, b);
	}
	else
	{
		return uc_datum_integer_add(a, b);
	}
}

/**
 * Returns the subtraction of the two given data
 *
 * @param a the first datum
 * @param b the second datum
 *
 * @return the subtraction of te two given data
 */
uc_datum* uc_datum_subtract(uc_datum* a, uc_datum* b)
{
	if (uc_datum_raw_type(a) == UNDEFINED || uc_datum_raw_type(b) == UNDEFINED 
		|| uc_datum_raw_type(a) == STRING || uc_datum_raw_type(b) == STRING)
	{
		return uc_datum_undefined();
	}
	else if (uc_datum_raw_type(a) == FLOAT || uc_datum_raw_type(b) == FLOAT)
	{
		return uc_datum_float_subtract(a, b);
	}
	else
	{
		return uc_datum_integer_subtract(a, b);
	}
}

/**
 * Returns the multiplication of the two given data
 *
 * @param a the first datum
 * @param b the second datum
 *
 * @return the multiplication of te two given data
 */
uc_datum* uc_datum_multiply(uc_datum* a, uc_datum* b)
{
	if (uc_datum_raw_type(a) == UNDEFINED || uc_datum_raw_type(b) == UNDEFINED 
		|| uc_datum_raw_type(a) == STRING || uc_datum_raw_type(b) == STRING)
	{
		return uc_datum_undefined();
	}
	else if (uc_datum_raw_type(a) == FLOAT || uc_datum_raw_type(b) == FLOAT)
	{
		return uc_datum_float_multiply(a, b);
	}
	else
	{
		return uc_datum_integer_multiply(a, b);
	}
}

/**
 * Returns the division of the two given data
 *
 * @param a the first datum
 * @param b the second datum
 *
 * @return the division of te two given data
 */
uc_datum* uc_datum_divide(uc_datum* a, uc_datum* b)
{
	if (uc_datum_raw_type(a) == UNDEFINED || uc_datum_raw_type(b) == UNDEFINED 
		|| uc_datum_raw_type(a) == STRING || uc_datum_raw_type(b) == STRING)
	{
		return uc_datum_undefined();
	}
	else if (uc_datum_raw_type(a) == FLOAT || uc_datum_raw_type(b) == FLOAT)
	{
		return uc_datum_float_divide(a, b);
	}
	else
	{
		return uc_datum_integer_divide(a, b);
	}
}

/**
 * Returns the modulus of the two given data
 *
 * @param a the first datum
 * @param b the second datum
 *
 * @return the modulus of te two given data
 */
uc_datum* uc_datum_modulus(uc_datum* a, uc_datum* b)
{
	if (uc_datum_raw_type(a) == UNDEFINED || uc_datum_raw_type(b) == UNDEFINED 
		|| uc_datum_raw_type(a) == STRING || uc_datum_raw_type(b) == STRING
		|| uc_datum_raw_type(a) == FLOAT || uc_datum_raw_type(b) == FLOAT)
	{
		return uc_datum_undefined();
	}
	else
	{
		return uc_datum_integer_modulus(a, b);
	}
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
		case REFERENCE:
			uc_datum_print(d->value.reference_value);
			return;
		case UNDEFINED:
			printf("undefined\n");
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
		case REFERENCE:
			printf("&");
			uc_datum_inspect(d->value.reference_value);
			return;
		case UNDEFINED:
			printf("undefined\n");
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

//--------------ALLOCATE-------------

/**
 * Allocates space for a uc_datum object
 *
 * @return pointer to allocated space
 */
static uc_datum* uc_datum_allocate()
{
	return (uc_datum*)malloc(sizeof(uc_datum));
}


//--------------GETTYPE-------------

/**
 * Allocates space for a uc_datum object
 *
 * @return pointer to allocated space
 */
static uc_datum_type uc_datum_raw_type(uc_datum* d)
{
	if (d->type == REFERENCE)
	{
		return uc_datum_raw_type(d->value.reference_value);
	}
	else
	{
		return d->type;
	}
}

//--------------INSPECT--------------

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


//-----------STRING CONCAT-----------

/**
 * Returns the concatenation of the two string data
 *
 * @param a the first string datum
 * @param b the second string datum
 *
 * @return the concatenation of the two string data
 */
static uc_datum* uc_datum_string_concat(uc_datum* a, uc_datum* b)
{
	char* stra = uc_datum_repr_string(a);
	char* strb = uc_datum_repr_string(b);

	char* strc = (char*)malloc(strlen(stra) + strlen(strb) - 1);
	strcpy(strc, stra);
	strcat(strc, strb);

	free(stra);
	free(strb);

	return uc_datum_from_string(strc);
}

/**
 * Returns a string representing the datum
 *
 * @param a the datum to represent as a string
 *
 * @return a string representing the datum
 */
static char* uc_datum_repr_string(uc_datum* d)
{
	char* string;
	if (d->type == REFERENCE)
	{
		return uc_datum_repr_string(d->value.reference_value);
	}
	else if (d->type == CHAR || d->type == BOOLEAN)
	{
		string = (char*)malloc(2);
		string[1] = '\0';

		if (d->type == BOOLEAN)
		{
			string[0] = d->value.boolean_value ? 'T' : 'F';
		}
		else
		{
			string[0] = d->value.char_value;
		}

		return string;
	}
	else
	{
		string = (char*)malloc(UC_STRING_MAX_LENGTH);
		memset(string, '\0', UC_STRING_MAX_LENGTH);
		switch(d->type)
		{
			case STRING:
				strcpy(string, d->value.string_value);
				break;
			case FLOAT:
				sprintf(string, "%f", d->value.float_value);
				break;
			case INT:
				sprintf(string, "%d", d->value.integer_value);
				break;
			default:
				break;
		}
		string = (char*)realloc(string, strlen(string) + 1);

		return string;
	}
}


//------------CHAR CONCAT------------

/**
 * Returns the concatenation of the two char data
 *
 * @param a the first char datum
 * @param b the second char datum
 *
 * @return the concatenation of the two char data
 */
static uc_datum* uc_datum_char_concat(uc_datum* a, uc_datum* b)
{
	char* string = (char*)malloc(3);
	string[0] = a->value.char_value;
	string[1] = b->value.char_value;
	string[2] = '\0';
	return uc_datum_from_string(string);
}


//-----------INTEGER OPERATIONS-----------

/**
 * Returns the addition of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the addition of the two integer data
 */
static uc_datum* uc_datum_integer_add(uc_datum* a, uc_datum* b)
{
	int inta = uc_datum_repr_integer(a);
	int intb = uc_datum_repr_integer(b);
	return uc_datum_from_integer(inta + intb);
}

/**
 * Returns the subtration of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the subtration of the two integer data
 */
static uc_datum* uc_datum_integer_subtract(uc_datum* a, uc_datum* b)
{
	int inta = uc_datum_repr_integer(a);
	int intb = uc_datum_repr_integer(b);
	return uc_datum_from_integer(inta - intb);
}

/**
 * Returns the multiplication of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the multiplication of the two integer data
 */
static uc_datum* uc_datum_integer_multiply(uc_datum* a, uc_datum* b)
{
	int inta = uc_datum_repr_integer(a);
	int intb = uc_datum_repr_integer(b);
	return uc_datum_from_integer(inta * intb);
}

/**
 * Returns the division of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the division of the two integer data
 */
static uc_datum* uc_datum_integer_divide(uc_datum* a, uc_datum* b)
{
	int inta = uc_datum_repr_integer(a);
	int intb = uc_datum_repr_integer(b);
	return uc_datum_from_integer(inta / intb);
}

/**
 * Returns the modulus of the two integer data
 *
 * @param a the first integer datum
 * @param b the second integer datum
 *
 * @return the modulus of the two integer data
 */
static uc_datum* uc_datum_integer_modulus(uc_datum* a, uc_datum* b)
{
	int inta = uc_datum_repr_integer(a);
	int intb = uc_datum_repr_integer(b);
	return uc_datum_from_integer(inta % intb);	
}

/**
 * Returns a integer representing the datum
 *
 * @param a the datum to represent as a integer
 *
 * @return a integer representing the datum
 */
static int uc_datum_repr_integer(uc_datum* a)
{
	switch(a->type)
	{
		case BOOLEAN:
			return (int)a->value.boolean_value;
		case FLOAT:
			return (int)a->value.float_value;
		case CHAR:
			return (int)a->value.char_value;
		case INT:
			return (int)a->value.integer_value;
		case REFERENCE:
			return uc_datum_repr_integer(a->value.reference_value);
		default:
			return 0;
	}
}


//-----------FLOAT OPERATIONS-----------

/**
 * Returns the addition of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the addition of the two float data
 */
static uc_datum* uc_datum_float_add(uc_datum* a, uc_datum* b)
{
	double floata = uc_datum_repr_float(a);
	double floatb = uc_datum_repr_float(b);
	return uc_datum_from_float(floata + floatb);
}

/**
 * Returns the subtraction of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the subtraction of the two float data
 */
static uc_datum* uc_datum_float_subtract(uc_datum* a, uc_datum* b)
{
	double floata = uc_datum_repr_float(a);
	double floatb = uc_datum_repr_float(b);
	return uc_datum_from_float(floata - floatb);
}

/**
 * Returns the multiplication of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the multiplication of the two float data
 */
static uc_datum* uc_datum_float_multiply(uc_datum* a, uc_datum* b)
{
	double floata = uc_datum_repr_float(a);
	double floatb = uc_datum_repr_float(b);
	return uc_datum_from_float(floata * floatb);
}

/**
 * Returns the division of the two float data
 *
 * @param a the first float datum
 * @param b the second float datum
 *
 * @return the division of the two float data
 */
static uc_datum* uc_datum_float_divide(uc_datum* a, uc_datum* b)
{
	double floata = uc_datum_repr_float(a);
	double floatb = uc_datum_repr_float(b);
	return uc_datum_from_float(floata / floatb);
}


/**
 * Returns a float representing the datum
 *
 * @param a the datum to represent as a float
 *
 * @return a float representing the datum
 */
static double uc_datum_repr_float(uc_datum* a)
{
	switch(a->type)
	{
		case BOOLEAN:
			return (double)a->value.boolean_value;
		case FLOAT:
			return (double)a->value.float_value;
		case CHAR:
			return (double)a->value.char_value;
		case INT:
			return (double)a->value.integer_value;
		case REFERENCE:
			return uc_datum_repr_float(a->value.reference_value);
		default:
			return 0.0;
	}
}
