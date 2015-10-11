/** @file environment.h
 * The interface an environment should conform to.
 *
 * The interface mostly conforms to RLGlue. For an example, see:  http://code.google.com/p/rl-library/source/browse/trunk/projects/packages/examples/mines-sarsa-c/SampleMinesEnvironment.c
 *
 * In the main loop of the agent-environment interface, these functions will usually be called as folllows:
 * \code
int main(int argc, char** argv)
{
  env_create(argc,argv)
  agent_create()
  for (episode=0; episode<n_episodes; episode++)
  {
    env_start()
    agent_start()
    while(!terminal)
    { 
      env_step()   => calls env_observe_state() to get state
      agent_step() => calls agent_policy() to get action
    }
  }
}
 * \endcode
 */
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "rl.h"


/** The opaque representation of an environment
 * \c env_impl_t is to be defined in specific implementations modules,
 * wheres \c env_t* can be used as \b opaque \b reference to it.
 */
typedef struct env_impl_t env_t;


/** Get the number of actions that the agent can execute in this environment. 
 *  @param p_env Pointer to an environment
 *  @return The number of possible actions
 */
unsigned int env_get_number_of_possible_actions(env_t* p_env);

/** Get number of possible states the agent can make in this environment.
 *  @param p_env Pointer to an environment
 *  @return The number of possible states
 */
unsigned long long int env_get_number_of_possible_states(env_t* p_env);

/** Creates a new environment
 *  Call your program with "--help" to see what these arguments are for a particular environment.  
 *  @param argc Number of input arguments
 *  @param argv Input arguments; an array of strings
 *  @return Pointer to an environment
 */
env_t* env_create(int argc, char** argv);

/** Sets an initial state and returns the corresponding state.
 *  @param p_env Pointer to an environment
 */
state_t env_start(env_t* p_env);

/** Project environment one step into the future.
 *
 * Given an action, compute the reward and next state, and whether next_state is terminal
 * Conforms to RLGLue
 *
 * @param p_env Pointer to an environment
 * @param action The action the agent is performing
 * @param reward The reward the agent recieves for performing action in the current state
 * @param terminal Whether the state resulting from applying the action is a terminal state
 * @return The state made in the updated state
 */
state_t env_step(env_t* p_env, action_t action, reward_t* reward, int* terminal);


/** Observe the state of the environment. 
 * @param p_env Pointer to an environment
 * @return The state
 */
state_t env_observe_state(env_t* p_env);

/*!
 * Destroy an env created by \c env_create.
 * \param pp_env pass-by-reference of a pointer to the env to be destroyed.
 *
 * This function set the passed pointer to NULL on destruction of the pointee
 * in order to avoid unintended reuse of the dangling pointer.
 */
void initialize_char_array_2D(env_t* p_env);
 unsigned int convert_frontiere_to_etat_frontiere(env_t* p_env);
 int is_a_wall_around(env_t* p_env);
 int is_a_wall_here(env_t* p_env);
void env_destroy(env_t** pp_env);
unsigned long long int power(unsigned long long int a, int b) ;
void gridtostate(env_t *p_env);
void create_grid(env_t* p_env);
void print_grid(env_t* p_env) ;
void remove_line(int ligne, env_t *p_env);
#endif        //  #ifndef ENVIRONMENT_H

