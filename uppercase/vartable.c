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
#include "uppercase/vartable.h"
#include "uppercase/datum.h"

// Libraries being used
#include <stdio.h>

/**
 * Holds the vartable values
 */
static uc_datum *uc_vartable[UC_VARTABLE_LENGTH];

/**
 * Initializes the vartable
 */
void uc_vartable_init(void)
{
	for (int i = 0; i < UC_VARTABLE_LENGTH; ++i)
	{
		uc_vartable[i] = NULL;
	}
}

/**
 * Sets the given leter address of the vartable to the given uc_datum value
 *
 * @param address the address (A to Z) to set
 * @param value   the value being set at the address
 */
void uc_vartable_set(char address, uc_datum* value)
{
	uc_vartable[address - 'A'] = value;
}

/**
 * Gets the uc_datum value at the given letter address in the vartable
 *
 * @param address the address (A to Z) to get
 *
 * @return the value at the address
 */
uc_datum* uc_vartable_get(char address)
{
	return uc_datum_from_reference(uc_vartable[address - 'A']);
}

/**
 * Prints a detailed description of the data stored in the vartable
 */
void uc_vartable_inspect(void)
{
	printf("Set variables:\n");
	for (int i = 0; i < UC_VARTABLE_LENGTH; ++i)
	{
		if (uc_vartable[i] != NULL)
		{
			printf("    %c -> ", (char)(i + 'A'));
			uc_datum_inspect(uc_vartable[i]);
			printf("\n");
		}
	}
}

/**
 * Clears all of the data in the vartable
 */
void uc_vartable_clear()
{
	// For each variable in the vartable
	for (int i = 0; i < UC_VARTABLE_LENGTH; ++i)
	{
		// Destroy variable if variable is not null
		if (uc_vartable[i] != NULL)
		{
			uc_datum_destroy(uc_vartable[i]);
		}

		// Set variable to null
		uc_vartable[i] = NULL;
	}
}
