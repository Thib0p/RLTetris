/** @file environment_print.h
 * Various functions to print an environment.
 * See also \ref environment.h
 */
#ifndef ENVIRONMENT_PRINT_H
#define ENVIRONMENT_PRINT_H

#include "environment.h"

/** Get a 2D char array representation of the environment. 
 * This is useful for visualization of the state of the environment. 
 * For a 2D grid, this 2D array may contain for instance:
 *
 * \verbatim
'T' '.' '.' '.' '.'
'.' '.' '.' '.' '.'
'W' 'W' '.' 'W' 'W'
'.' '.' '.' '.' '.'
'.' '.' 'A' '.' '.'
\endverbatim
 *
 * Where 'A' is the agent, 'T' is a terminal state, 'W' is a wall, and '.' is an empty cell.
 *
 * @param p_env Pointer to an environment
 * @param char_array_2D The 2D char array which will be filled with values
 * @param n_rows The number of rows in the 2D char array
 * @param n_cols The number of columns in the 2D char array
 */
void env_get_char_array_2D(env_t* p_env);


/** Print the current state of the environment. 
 * Should be implemented by the environment, not the agent!
 * @param p_env Pointer to an environment
 * @param state The state to be printed.
 */
void env_print_state(env_t* p_env);

/** Print an action. 
 * Should be implemented by the environment, not the agent!
 * @param action The action to be printed.
 */
void env_print_action(action_t action);

/** Print a value function. 
 * One value for each state
 * Should be implemented by the environment, not the agent!
 * @param p_env Pointer to an environment
 * @param values A 1D array of length "n_states" of state values.
 */
void env_print_values(env_t* p_env, double* values);

/** Print a q-value function. 
 * One value for each state/action pair
 * Should be implemented by the environment, not the agent!
 * @param p_env Pointer to an environment
 * @param qvalues A 2D array (n_states x n_actions) of Q-values
 */
void env_print_qvalues(env_t* p_env, double** qvalues);

#endif        //  #ifndef ENVIRONMENT_PRINT_H

