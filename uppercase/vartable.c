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
#include "helper.h"
#include "vartable.h"
#include "datum.h"

// Libraries being used
#include <stdio.h>

/**
 * Create a new vartable
 */
struct uc_vartable* uc_vartable_new(void)
{
	struct uc_vartable* vartable = NEW(struct uc_vartable);
	for (int i = 0; i < UC_VARTABLE_LENGTH; ++i)
	{
		vartable->table[i] = NULL;
	}
	return vartable;
}

/**
 * Sets the given leter address of the vartable to the given uc_datum value
 *
 * @param vartable the vartable to modify
 * @param address  the address (A to Z) to set
 * @param value    the value being set at the address
 */
void uc_vartable_set(struct uc_vartable* vartable, char address, uc_datum* value)
{
	vartable->table[address - 'A'] = value;
}

/**
 * Gets the uc_datum value at the given letter address in the vartable
 *
 * @param vartable the vartable to access
 * @param address  the address (A to Z) to get
 *
 * @return the value at the address
 */
uc_datum* uc_vartable_get(struct uc_vartable* vartable, char address)
{
	return uc_datum_from_reference(vartable->table[address - 'A']);
}

/**
 * Prints a detailed description of the data stored in the vartable
 *
 * @param vartable the vartable to access
 */
void uc_vartable_inspect(struct uc_vartable* vartable)
{
	printf("Set variables:\n");
	for (int i = 0; i < UC_VARTABLE_LENGTH; ++i)
	{
		if (vartable->table[i] != NULL)
		{
			printf("    %c -> ", (char)(i + 'A'));
			uc_datum_inspect(vartable->table[i]);
			printf("\n");
		}
	}
}

/**
 * Destroy vartable
 */
void uc_vartable_destroy(struct uc_vartable** vartableloc)
{
	// For each variable in the vartable
	for (int i = 0; i < UC_VARTABLE_LENGTH; ++i)
	{
		// Destroy variable if variable is not null
		if ((*vartableloc)->table[i] != NULL)
		{
			uc_datum_destroy((*vartableloc)->table[i]);
		}

		// Set variable to null
		(*vartableloc)->table[i] = NULL;
	}

	// Destroy vartable
	free(*vartableloc);
	*vartableloc = NULL;
}