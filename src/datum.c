#include "UpperCase/datum.h"

/**
 * Headers being used
 */
#include <stdio.h>
#include <stdlib.h>

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
 * Prints the given data to the console
 *
 * @param d the data being printed
 */
void uc_datum_print(uc_datum *d)
{
	switch(d->type)
	{
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
		case BOOLEAN:
			printf("boolean: %c", (d->value.boolean_value > 0 ? 'T' : 'F'));
			return;
		case FLOAT:
			printf("float %f", d->value.float_value);
			return;
		case CHAR:
			switch (d->value.char_value)
			{
				case '\n':
					printf("char: '\\n'");
					return;
				case '\t':
					printf("char: '\\t'");
					return;
				case '\r':
					printf("char: '\\r'");
					return;
				default:
					printf("char: '%c'", d->value.char_value);
					return;
			}
		case INT:
			printf("int: %d", d->value.integer_value);
			return;
		default:
			printf("unknown type");
			return;
	}
}