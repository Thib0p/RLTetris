/** @file agent_smithLvlUp
*  @brief An agent with TD learning and use of epsilon alea.
*/

#include "../agent.h" 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define START_EPSILON_GREEDY 80  // en pourcentage
#define COEF_EPSILON 0.99

/** Structure of the clever agent */
struct agent_impl_t {
  /** Nuber of actions this agent can perform */
  unsigned int n_actions;       
  /** How many states this agent can reach */
  unsigned long long int n_states;   
  /** Memorization of the state at the i step */
  unsigned int* iniS_ep_step;        
  /**    Memorization of the action at the i step*/
  int* firstAction_step;      
  /** Memorization of the reward from the i step*/
  double* rew_ep_step;           
  /**   Sum up of the starts per state per action*/
  unsigned int** startsS;    
  /**     Sum up of the rewards per state per action*/
  double** av_rewS;        
  /** For Epsilon-greedy exploration*/
  float epsilon;                 
  /** Nomber of step of the episode*/
  unsigned int n_step;           
  /** Nomber of episode */
  unsigned int n_ep;  
/** Nomber total of episodes */
  int n_episodes_max;
/** Nomber total of step */
  int max_n_step;
};

/** 
@param n_states the number of states
@param n_actions the number of actions
@return Return the created agent to the main
*/

agent_t* agent_create(unsigned long long int n_states, unsigned int n_actions,int n_episodes_max,int max_n_step) {
  agent_t* p_agent = malloc(sizeof(struct agent_impl_t));
  assert(p_agent!=NULL);
  p_agent->n_actions = n_actions;
  p_agent->n_states = n_states;
  p_agent->epsilon=1;
  p_agent->n_ep=0;
  p_agent->max_n_step=max_n_step;
  p_agent->n_episodes_max = n_episodes_max;

// allocation of the memory for each table 
  (p_agent->iniS_ep_step) = malloc(max_n_step*sizeof(unsigned int));
  (p_agent->firstAction_step) = malloc(max_n_step*sizeof(int));
  (p_agent->rew_ep_step) = malloc(max_n_step*sizeof(double));

  int i;
  unsigned long long int j;
  p_agent->startsS = malloc(n_actions*sizeof(unsigned int*)); 
  p_agent->av_rewS= malloc(n_actions*sizeof(double*)); 
  for (i=0;i<n_actions;i++) {
    (p_agent->startsS)[i] = malloc(n_states*sizeof(unsigned int)); 
    (p_agent->av_rewS)[i] = malloc(n_states*sizeof(double)); 
    for (j=0;j<n_states;j++) {
      (p_agent->startsS)[i][j]=0;
      (p_agent->av_rewS)[i][j]=0;
    }
  }
  return p_agent;
}

/** Free the agent */
void agent_destroy(agent_t** p_agent) {
  free(*p_agent);
  (*p_agent) = NULL;
}

action_t agent_start(agent_t* p_agent, state_t initial_state) 
{
  p_agent->n_step = 0;
  p_agent->iniS_ep_step[0]= initial_state;
  p_agent->n_ep++;
  int a,k;
  a=agent_policy(p_agent, initial_state);
  p_agent->firstAction_step[0]=a;
  p_agent->startsS[p_agent->firstAction_step[0]][p_agent->iniS_ep_step[0]]++;
  for (k=0;k<p_agent->max_n_step;k++) {
    p_agent->rew_ep_step[k]=0;
  }
  return a;
}

action_t agent_step(agent_t* p_agent, reward_t reward, state_t state)  
{
 int a;
 a = agent_policy(p_agent, state);                   
 (p_agent->n_step)++;  
 p_agent->iniS_ep_step[p_agent->n_step]= state;
 int i;
 for (i=0;i<p_agent->n_step;i++) {
  p_agent->rew_ep_step[i]=p_agent->rew_ep_step[i]+reward;
}
p_agent->firstAction_step[p_agent->n_step] = a;

int action;
unsigned int step, State;
step = p_agent->n_step;
action = p_agent->firstAction_step[step];
State = p_agent->iniS_ep_step[step];
p_agent->startsS[action][State]++;
return a;
}


action_t agent_policy(agent_t* p_agent, state_t state) {
  assert(p_agent!=NULL);
  float a=rand()%100;
  /** -> epsilon-greedy exploration implemented here */
  if (a < 100*p_agent->epsilon) {   
    return random_action(p_agent, state); 
  }
  else { 
    return determined_action(p_agent, state); 
  }
}


/**
@return An agent a bit more clever
*/
void agent_end(agent_t* p_agent) {
  unsigned long long int m,n;
  m=p_agent->n_ep;
  n=((p_agent->n_episodes_max)/100)*START_EPSILON_GREEDY;
  if ( n < m ) {
    p_agent->epsilon=(p_agent->epsilon)*COEF_EPSILON;
  }
  int k;
  unsigned int a;
  double b;
/** Add of the reward received for a start at each step ( TD0 learning ) */
  for (k=0;k<p_agent->n_step;k++) {
    a=p_agent->startsS[p_agent->firstAction_step[k]][p_agent->iniS_ep_step[k]];   
    b=p_agent->av_rewS[p_agent->firstAction_step[k]][p_agent->iniS_ep_step[k]]; 
    b=( (a-1)*b+(p_agent->rew_ep_step[k]))/a;                                   
    p_agent->av_rewS[p_agent->firstAction_step[k]][p_agent->iniS_ep_step[k]]=b;
  }
}

/** Define the random action
@return The action
*/
unsigned int random_action(agent_t* p_agent, state_t state) {
  return(rand()%p_agent->n_actions);
}

/** Define the determined action
@param p_agent
@param state Allow the agent to choose the action according to the state
@return The action
*/
unsigned int determined_action(agent_t* p_agent, state_t state) {
  double a;
  int i=1;
  unsigned long long int b;
  a=(p_agent->av_rewS)[0][state];
  b=0;
  for (i=0;i<p_agent->n_actions;i++) {
    if (a<(p_agent->av_rewS)[i][state]) { 
      a=(p_agent->av_rewS)[i][state];
      b=i;
    }
  }
  return (b); 
}
