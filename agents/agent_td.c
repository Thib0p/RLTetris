#include "../agent.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define alpha 0.1
#define gamma 0.5
#define n_col 6

struct agent_impl_t {
  unsigned int n_actions;
  double* av_rewS[4];
  float reward_previous_state;
  unsigned long long int previous_state;
  int n_step;
  int n_ep;
  unsigned int previous_action;
  float epsilon;
  unsigned int n_states;
};

agent_t* agent_create(unsigned long long int n_states, unsigned int n_actions,int n_episodes_max,int max_n_step) {
  agent_t* p_agent = malloc(sizeof(struct agent_impl_t));
  assert(p_agent!=NULL);
  p_agent->n_actions = n_actions;
  p_agent->n_states=n_states;
  p_agent->n_step=0;
  p_agent->n_ep=0;
  p_agent->epsilon=1;

  int i,j;
  for (i=0;i<n_actions;i++) {
    (p_agent->av_rewS)[i] = malloc(n_states*sizeof(double)); 
    for (j=0;j<n_states;j++) {
      (p_agent->av_rewS)[i][j]=0;
    }
    printf("\n");
  }
  return p_agent;
}

void agent_destroy(agent_t** p_agent) {
  print_result(p_agent);
  free(*p_agent);
  (*p_agent) = NULL;
}

action_t agent_start(agent_t* p_agent, state_t initial_state) 
{
  p_agent->n_ep++;
  return agent_policy(p_agent, initial_state);
}

action_t agent_step(agent_t* p_agent, reward_t reward, state_t state)  
{
  int action;
  action = agent_policy(p_agent, state);
  p_agent->n_step++;

  if (p_agent->n_step == 1){ 
p_agent->previous_state = state;
p_agent->previous_action = action;
  }

else {
  double a,b;
  a=reward+gamma*(p_agent->av_rewS[action][state])-p_agent->av_rewS[p_agent->previous_action][p_agent->previous_state];
  b=p_agent->av_rewS[p_agent->previous_action][p_agent->previous_state];
  b=b+alpha*a;
  p_agent->av_rewS[p_agent->previous_action][p_agent->previous_state]=b;
  p_agent->av_rewS[p_agent->previous_action][p_agent->previous_state] = p_agent->av_rewS[p_agent->previous_action][p_agent->previous_state] + alpha*a;

p_agent->previous_state = state;
p_agent->previous_action = action;
}


  return action;
}

/** Return a random action. Ignores the state. 
 *  @param state The state the agent makes.
 *  @return The action the agent performs.
 */
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

void agent_end(agent_t* p_agent) {
 
if (p_agent->n_ep > 10000) { p_agent->epsilon=p_agent->epsilon*0.999;}
}

unsigned int random_action(agent_t* p_agent, state_t state) {
  return(rand()%p_agent->n_actions);
}

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

void print_result(agent_t** p_agent) {
  printf("\n");
  int i,j,k;
  int* tab;
  unsigned int n_actions=(*p_agent)->n_actions;
  unsigned int n_states=(*p_agent)->n_states;
  float epsilon = (*p_agent)->epsilon;
  tab = malloc(n_states*sizeof(int));

  printf("av_rewS[i][j]\n\n");
  for (k=0;k<n_col;k++) {
    printf("ligne %d \n",k);
    for (i=0;i<n_actions;i++){
      for (j=k*n_col;j<(k+1)*n_col;j++) {
        printf(" %.lf ",(*p_agent)->av_rewS[i][j]);  
      }
      printf("\n");
    }
    printf("\n");
  }

  for (i=0;i<n_states;i++) {
    tab[i]=determined_action(*p_agent, i);
  }
  printf("T");
  for (i=1;i<n_col;i++) {
    printf("%d",tab[i]);
  }
  printf("\n");

  for (k=1;k<n_col;k++) {
    for (i=k*n_col;i<(k+1)*n_col;i++) {
      printf("%d",tab[i]);
    }
    printf("\n");
  }
  printf("\n\n");
  printf("epsilon : %f\n",epsilon);
}