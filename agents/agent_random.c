/** @file agent_random.c
 *  @brief An agent that returns random actions.
 */

#include "../agent.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * Implementation of the random agent structure
 */
struct agent_impl_t {
  /** How many possible actions can this agent perform? */
  unsigned int n_actions;
};

agent_t* agent_create(unsigned long long int n_states, unsigned int n_actions,int n_episodes_max,int max_n_step) {
  agent_t* p_agent = malloc(sizeof(struct agent_impl_t));
  assert(p_agent!=NULL);
  p_agent->n_actions = n_actions;
  return p_agent;
}

void agent_destroy(agent_t** p_agent) {
  free(*p_agent);
  (*p_agent) = NULL;
}



action_t agent_start(agent_t* p_agent, state_t initial_state) 
{
  return agent_policy(p_agent, initial_state);
}

action_t agent_step(agent_t* p_agent, reward_t reward, state_t state)  
{
  return agent_policy(p_agent, state);
}

/** Return a random action. Ignores the state. 
 *  @param state The state the agent makes.
 *  @return The action the agent performs.
 */
action_t agent_policy(agent_t* p_agent, state_t state) {
  assert(p_agent!=NULL);
  //printf("%d",p_agent->n_actions);
  return (rand()%p_agent->n_actions); // Return a random action  
  }

void agent_end(agent_t* p_agent) {};

// Random agent doesn't keep track of values. Return NULL. 
// This will only become relevant in Phase 2
double*  agent_get_values(agent_t* p_agent)  { return NULL; }
double** agent_get_qvalues(agent_t* p_agent) { return NULL; }

