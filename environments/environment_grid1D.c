/** @file environment_grid1D.c
 *  @brief A 1D grid environment. 
 *  You can change the number of cells in the grid by calling the executable as follows:
 *  <tt>./rl_grid1D_agent 10</tt>
 */
 
#include "../environment.h"
#include "../environment_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/** Convenient enum for the possible actions. */
enum actions 
{
  LEFT,
  RIGHT
};

/**
 * Implementation of the 1D grid environment structure
 */
struct env_impl_t {
  
  /** The current state of the environment: in which cell is the agent? */
  unsigned int cell;
  
  /** Number of cells in the 1D grid */
  unsigned int n_cells;
  
  /** Number of possible actions */
  unsigned int n_actions;
  
};
/** Création de l'environnement. 
 *  @param argc nombre de paramètres fournies à l'executable
 *  @param argv paramètres fournis à l'executable
 */
env_t* env_create(int argc, char** argv) {
  env_t* p_env = malloc(sizeof(struct env_impl_t));
  assert(p_env!=NULL);
  
  p_env->n_actions = 2;
  p_env->n_cells = 8;
  if (argc>1) {
    if (strcmp(argv[1],"--help")==0)
    { 
      printf("env_init for grid1D takes parameters [number of cells (int)]\n");
      return NULL;
    }
    else
    {
      p_env->n_cells = atoi(argv[1]);
    }
  }
  printf("Initialized environment grid1D: n_cells=%d\n",p_env->n_cells);
  
  return p_env;
}



/** Get number of possible states */
unsigned long long int env_get_number_of_possible_states(env_t* p_env) {
  assert(p_env!=NULL);
  return p_env->n_cells; 
}

/** Get number of possible actions */
unsigned int env_get_number_of_possible_actions(env_t* p_env) {
  assert(p_env!=NULL);
  return p_env->n_actions; 
}

/** Determine whether a state is terminal or not. 
 *  @param p_env The environment in which 'terminality' is to be determined
 *  @param state The state whose 'terminality' is to be determined
 */
int is_terminal_state(env_t* p_env, unsigned int state) {
  assert(p_env!=NULL);
  // Left cell is a terminal state
  if (state==0)
    return 1;
  // Right cell is also a terminal state
  //if (state==p_env->n_cells-1)
  //  return 1;
  return 0;
}
/** Observe l'état pour le renvoyer à l'agent.
 *  @param *p_env un pointeur vers l'environnement
*/
state_t env_observe_state(env_t* p_env) 
{
  assert(p_env!=NULL);
  return p_env->cell;
}
/** Initialisation de l'environnement à chaque épisode 
 *  @param *p_env paramètre
 */
state_t env_start(env_t* p_env) {
  assert(p_env!=NULL);
  // Put agent at far right
  //p_env->cell = p_env->n_cells-1;
  // Put agent at random position (but not in a terminal state)
  do {
    p_env->cell = rand()%p_env->n_cells;
  } while (is_terminal_state(p_env,p_env->cell));
  // Return first observed state
  return env_observe_state(p_env);
}
/** mise à jour de l'environnement à chaque step
 *  @param *p_env un pointeur vers l'environnement
 *  @param action l'action envoyée par l'agent
 *  @param *reward renvoie le reward
 *  @param *terminal renvoie si l'état est terminal
*/
state_t env_step(env_t* p_env, action_t action, double* reward, int* terminal) {
  assert(p_env!=NULL);
  
  if (action==LEFT && p_env->cell>0)
    p_env->cell--;
  if (action==RIGHT && p_env->cell<(p_env->n_cells-1))
    p_env->cell++;
  
  (*terminal) = is_terminal_state(p_env,p_env->cell);
  if (*terminal) 
    (*reward)=100.0;
  else
    (*reward)=-1.0;
  
  return env_observe_state(p_env);
      
}


/** Genère un tableau de caractères pour afficher l'environnement
 *  @param *p_env un pointeur vers l'environnement
 *  @param state l'état actuel
*/
void env_print_state(env_t* p_env) 
{
  state_t state = p_env->cell;
  assert(p_env!=NULL);
  int i;
  printf("|");
  for (i=0; i<p_env->n_cells; i++) 
  {
    if (state==i)
    {
      printf("A");
    }
    else if (i==0)
    {
      printf("T");
    }
    else
    {
      printf(".");
    }
  }
  printf("|");
  
}

/** Print an action. 
 * @param action The action to be printed.
 */
void env_print_action(action_t action) {
  if (action==LEFT)
    printf("  LEFT");
  else
    printf(" RIGHT");
}

/** Libère la mémoire
 *  @param *p_env un pointeur vers l'environnement
*/
void env_destroy(env_t** p_env) {
  free(*p_env);
  (*p_env) = NULL;
}


