/** @file agent.h
 * @brief The interface an agent should conform to
 *
 * The interface mostly conforms to RLGlue. For an example, see: http://code.google.com/p/rl-library/source/browse/trunk/projects/packages/examples/mines-sarsa-c/SampleSarsaAgent.c
 *
 * In the main loop of the agent-environment interface, these functions will usually be called as folllows:
 * \code
env_create()
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
 * \endcode
 */
#ifndef AGENT_H
#define AGENT_H

#include "rl.h"

/** The opaque representation of an agent
 * \c agent_impl_t is to be defined in specific implementations modules,
 * wheres \c agent_t* can be used as \b opaque \b reference to it.
 */
typedef struct agent_impl_t agent_t;

/** Creates a new agent.
 *  @param n_states Number of possible states the agent can make
 *  @param n_actions Number of possible action the agent can perform
 * \return A reference to a newly created agent.
 */
agent_t* agent_create(unsigned long long int n_states, unsigned int n_actions,int n_episodes,int max_n_actions);


/** Start an episode with state 'initial_state', return first action
 *  @param p_agent Pointer to the agent
 *  @param initial_state The first states the agent makes
 *  @return The first action the agent performs
 */
action_t agent_start(agent_t* p_agent, state_t initial_state);

/** One step of the agent in the reinforcement learning loop.
 *  Usually, this function will do two things:
 *  \li Use the reward to update values
 *  \li Call the agent's policy to determine the next action, given the state
 *  @param p_agent Pointer to the agent
 *  @param reward The reward recieved for performing the previous action in the previous state
 *  @param state The state at the current time step
 *  @return The action returned for the state at the current time step
 */
action_t agent_step(agent_t* p_agent, reward_t reward, state_t state);

/** Ends an episode
 *  @param p_agent Pointer to the agent
 */
void agent_end(agent_t* p_agent);

/*!
 * Destroy an agent created by \c agent_create.
 * @param pp_agent pass-by-reference of a pointer to the agent to be destroyed.
 *
 * This function set the passed pointer to NULL on destruction of the pointee
 * in order to avoid unintended reuse of the dangling pointer.
 */
void agent_destroy(agent_t** pp_agent);

void print_result(agent_t** pp_agent);
unsigned int random_action(agent_t* p_agent, state_t state);
unsigned int determined_action(agent_t* p_agent, state_t state);

/** The policy of an agent.
 *  Returns an action, given the current state.
 *  @param p_agent Pointer to the agent
 *  @param state The state the agent makes.
 *  @return The action the agent performs.
 */
action_t agent_policy(agent_t* p_agent, state_t state);

/** Get the values the agent assigns to each state.
 *  If the agent does not compute values, this should return NULL.
 *  @param p_agent Pointer to the agent
 *  @return The values, one for each state.
 */
double* agent_get_values(agent_t* p_agent);


/** Get the Q-values the agent assigns to each state/action pair.
 *  If the agent does not compute values, this should return NULL.
 *  @param p_agent Pointer to the agent
 *  @return The values, one for each state/action pair.
 */
double** agent_get_qvalues(agent_t* p_agent);


#endif //  #ifndef AGENT_H

