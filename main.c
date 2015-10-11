/** @file main.c
 *  @brief Main program for running reinforcement learning
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "environment.h"
#include "environment_print.h"
#include "agent.h"
#include "learning_curve.h"

#define PLOT 0  // plot si 1, sinon non.
#define PRECISION_PLOT 1000
#define NOMBRE_EP_FINAUX 5

static int n_episodes = 400000;
static int max_n_step = 200;
static int P=0;

/** Print a 2 dimensional array of characters.
 *  @param char_array_2D The 2D char array to be printed 
 *  @param n_rows The number of rows in the 2D char array 
 *  @param n_cols The number of columns in the 2D char array 
 */
 void print_char_array_2D(char** char_array_2D, unsigned int n_rows, unsigned int n_cols)
 {
  if (n_rows>1)
    printf("\n");

  int i,j;
  for (i=0; i<n_rows; i++) 
  {
    printf("|");
    for (j=0; j<n_cols; j++) 
      printf("%c",char_array_2D[i][j]);
    printf("|");
    if (n_rows>1)
      printf("\n");
  }  
}

/** Print an environment that has just been initialized (no action performed yet).
 *  @param p_env Pointer to an environment
 */

 void print_initialized_environment(env_t* p_env)
 {
  // Print this first environment

  printf("==   INIT ================> "); 
  env_print_state(p_env);
  printf("\n");
}

/** Print one step in the agent-environment loop. 
 * @param p_env Pointer to an environment
 * @param p_agent Pointer to an agent
 * @param action The action performed by the agent in the current step
 * @param reward The reward received by the agent in the current step
 */
 void print_step(env_t* p_env, agent_t* p_agent, action_t action, reward_t reward)
 {

  printf("== "); 
  env_print_action(action); 
  printf(" == "); 
  printf("(R=% 6.1f)",reward);
  printf(" ==> "); 
  // Print state of the environment
  env_print_state(p_env);
  printf("\n");
  
}


/** Run one episode.
 *
 *  Integrate the environment-agent loop until a terminal state is reached, or a maximum number of
 *  actions.
 *  @param p_env Pointer to an environment
 *  @param p_agent Pointer to an agent
 *  @param max_n_actions Maximum number of actions before an episode is terminated.
 */
 reward_t run_episode(env_t* p_env, agent_t* p_agent, int max_n_step) {

  // Initialize and first state  
  state_t state =  env_start(p_env);
  // char c;
  // Print output
  if(P==1){
    print_initialized_environment(p_env);
  }

  // Get action for first step
  action_t action = agent_start(p_agent,state);
  int terminal = 0;
  reward_t reward = 0.0;
  reward_t total_reward = 0.0;
  int n_actions = 0;

  while (!terminal && n_actions++<max_n_step) {
   // c = getc(stdin);
    // Update the state, and get the reward and next state
    state = env_step(p_env, action, &reward, &terminal);    
    total_reward += reward;
    
    // Print output
    if(P==1){ print_step(p_env,p_agent,action,reward); }
    // Get the next action for this state 
    action = agent_step(p_agent,reward,state);
  }
  agent_end(p_agent);
  
  return total_reward;
}

/** main function
 *  Initializes agent, and 
 *  @param argc Number of input arguments
 *  @param argv Input arguments; an array of strings
 */
 int main(int argc, char** argv) {

  float* average_of_reward;
  int i=0,k=0;
  float sum=0;
  float a,b;
  average_of_reward = malloc(PRECISION_PLOT*sizeof(float));
  // Create the environment
  env_t* p_env = env_create(argc,argv); // Arguments (if any) are passed to the environment
  assert(p_env!=NULL); // Check if environment was really createdt

  // Create the agent
  unsigned long long int n_states = env_get_number_of_possible_states(p_env);
  unsigned int n_actions = env_get_number_of_possible_actions(p_env);
  agent_t* p_agent = agent_create(n_states,n_actions,n_episodes,max_n_step);
  assert(p_agent!=NULL); // Check if agent was really created

  if (PLOT == 1) {learning_curve_open_file(argv[0]);}
  reward_t total_reward;    
  int episode;
  printf("Avancement : en pourcentage\n");
  for (episode=1; episode<=n_episodes; episode++) {

a=100*episode%n_episodes;
b=100*episode/n_episodes;
   if (a == 0 ) {printf("%.f \n",b);}
   // printf("Episode %d/%d starting.\n",episode,n_episodes);  

   if (PLOT == 1) {
    if (episode<PRECISION_PLOT) {
      total_reward = run_episode(p_env,p_agent,max_n_step);
      average_of_reward[i]=total_reward;
      i++;
    }
    else {
      total_reward = run_episode(p_env,p_agent,max_n_step);
      average_of_reward[i]=total_reward;
      i++;
      k=0;
      sum=0;
      for (k=0;k<PRECISION_PLOT;k++) {
        sum = sum + average_of_reward[k];
      }
      if(episode%PRECISION_PLOT == 0) { 
        learning_curve_add_measurement(sum/PRECISION_PLOT);
        i=0;
      }
    }
  }
  else {
    total_reward = run_episode(p_env,p_agent,max_n_step);
  }
}

if (PLOT == 1) {
learning_curve_close_file();
learning_curve_plot();
}


P=1;
for(i=0;i<NOMBRE_EP_FINAUX;i++) {
total_reward = run_episode(p_env,p_agent,max_n_step);
episode++;
printf("Episode %d/%d done. Total reward: %1.2f\n",episode,n_episodes,total_reward); 
}

// Free memory
env_destroy(&p_env);
agent_destroy(&p_agent);
return 0;
}

