#ifndef _UC_DATUM_H_
#define _UC_DATUM_H_

//-----------------------STACK DATA----------------------

/**
 * Represents a type of data
 *
 * Can be either boolean, float, char, or integer
 */
typedef enum 
{
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

#endif