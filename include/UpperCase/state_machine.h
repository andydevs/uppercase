/**
 * Handles state machine code
 */
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

//---------------------------THE FOUNDATION---------------------------

/**
 * Runs the UpperCase state machine.
 *
 * @return true if the state machine ran successfully
 */
int uc_run(void);

/**
 * The main state of the program
 * This is where the state machine starts
 */
void *uc_main_state(void);



//---------------------------ERROR HANDLING---------------------------

/**
 * Handles errors.
 */
void *uc_error_state(void);

/**
 * Defines error types
 */
typedef enum 
{
	OKAY,
	INVALID_CHAR
} 
ErrorType;

/**
 * Holds the error that is thrown
 */
ErrorType error;

#endif