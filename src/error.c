#include "UpperCase/error.h"
#include "UpperCase/program_io.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Function for throwing errors
 *
 * @param uc_err the error being thrown
 *
 * @return NULL pointer
 */
void *uc_throw_error(uc_error_type uc_err)
{
	printf("ERROR: ");
	switch(uc_err)
	{
		case UC_INPUT_CHAR_INVALD:
			printf("'%c' is invalid! Must be an uppercase letter!\n", uc_current_character());
			return NULL;
		case UC_REGISTRY_MODULE_SLOT_FILLED:
			printf("'%c' is already registered to another function!\n", uc_current_character());
			return NULL;
		case UC_REGISTRY_MODULE_NOT_FOUND:
			printf("'%c' Module not found in registry\n", uc_current_character());
			return NULL;
		default:
			printf("Undefined error %i\n", uc_err);
			return NULL;
	}
}
