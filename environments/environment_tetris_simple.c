/** @file environment_tetris_simple.c
 *  L'environnement de tetris mais avec des monoblocs 1x1. 
 *  You can change the number of cells in the grid by calling the executable as follows:
 *  <tt>./rl_grid2D_agent 10</tt>
 */
 
#include "../environment.h"
#include "../environment_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
/**
 * Implementation of the 1D grid environment structure
 */
 struct env_impl_t {

  /** The current state of the environment */
  unsigned long long int cell;
  
  /** Number of cells in the 1D grid */
  unsigned long long int n_cells;
  int n_lignes_detruites;
  /** Number of possible actions */
  unsigned int n_actions;
  int n_rows;
  int n_cols;
  int** grid;
};



unsigned long long int power(unsigned long long int a, int b) // renvoie b^a
{
  int i;
  unsigned long long int output = b;
  for(i=0;i<a;i++)
  {
    output= output*b;
  }
  return output;
}

void gridtostate(env_t *p_env)
{
  state_t state=0;
  int i,j;
  for(i=0;i<(p_env->n_rows);i++)
  {
    for(j=0;j<(p_env->n_cols);j++)
    {
      //printf("%d",p_env->grid[i][j]);
      state = state+p_env->grid[i][j]*power(i*p_env->n_cols+j,2);
      //printf("i : %d\nj : %d\n",i,j);
    }
    

  }

  p_env->cell = state;

    //printf("\n%llu\n",p_env->cell);

}
void create_grid(env_t* p_env)// Fonction qui permet de créer les grid(walls)
{
  unsigned long long int i;
  unsigned long long int j;
  int colonnes = p_env->n_cols;
  int lignes = p_env->n_rows;
  p_env->n_lignes_detruites=0;


  p_env->grid = malloc(lignes*sizeof(int*));
  for(i=0;i<lignes;i++)
    p_env->grid[i] = malloc(colonnes*sizeof(int));

  for (i=0;i<lignes;i++)
  {
    for (j=0;j<colonnes;j++)
    {
      p_env->grid[i][j]=0;
      //printf("%d",p_env->grid[i][j]);
    }
  }
  gridtostate(p_env);
}

double max(double a, double b)
{
  return (a>b?a:b);
}


env_t* env_create(int argc, char** argv) 
{ // Fonction pour la création de l'environnement 
env_t* p_env = malloc(sizeof(struct env_impl_t));
assert(p_env!=NULL);
p_env->n_actions = 4;
p_env->n_rows = 4;
p_env->n_cols = 4;
p_env->n_lignes_detruites=1;
p_env->n_cells = power(p_env->n_cols*p_env->n_rows,2);
if (argc>1) {
  if (strcmp(argv[1],"--help")==0)
  { 
    printf("env_init for grid2D takes parameters [number of cells (int)]\n");
    return NULL;
  }
    else
    {
      p_env->n_rows = atoi(argv[1]);
      p_env->n_cols = atoi(argv[2]);
      p_env->n_cells = p_env->n_cols*p_env->n_rows;
    }
}
printf("Initialized environment grid2D: n_cells=%llu\n",p_env->n_cells);
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
int is_terminal_state(env_t* p_env, unsigned long long int state,int *win) { // A priori on a pas besoind e l'état en cours
  assert(p_env!=NULL);
  int j;
  int somme;
  if (p_env->n_lignes_detruites==5)
  {
    *win=0;
    return 0;
  }
  for(j=0;j<(p_env->n_cols);j++)
  {
    somme+=p_env->grid[0][j];
  } 
  if(somme==p_env->n_cols)
  {
    *win=0;
    return 1;
  }
  return 0;
}
//---------------------------------------------------------------------------------------------------------------------
void env_print_state(env_t* p_env) //permet d'afficher la grille, utile pour le debuggage
{
  int n_rows = p_env->n_rows;
  int n_cols = p_env->n_cols;
  //printf("\n\n\nState : %llu\n\n\n",p_env->cell);
  printf("\nLignes :%d\n colonnes:%d\n",n_rows,n_cols);
  int i;
  int j;
  for(i=0;i<n_rows;i++)
  {
    for(j=0;j<n_cols;j++)
    {
      printf("%d",p_env->grid[i][j]);
    }
    printf("\n");
  }
}
//---------------------------------------------------------------------------------------------------------------------

void remove_line(int ligne, env_t *p_env)
{
  int j;
  int i;
  for (j = 0; j < p_env->n_cols; j++)
  {
    for (i = ligne; i>=1;i--)
    {
              p_env->grid[i][j] = p_env->grid[i-1][j];
    }
    p_env->grid[0][j]=0;
  }
  p_env->n_lignes_detruites+=1;
}
state_t env_observe_state(env_t* p_env) 
{
  assert(p_env!=NULL);
  return p_env->cell;
}

state_t env_start(env_t* p_env) {
  assert(p_env!=NULL);
  //p_env->cell = p_env->n_cells-1;
  // Put agent at random position (but not in a terminal state)
  create_grid(p_env);
  // Return first observed state
  return env_observe_state(p_env);
}

state_t env_step(env_t* p_env, action_t action, double* reward, int* terminal) {
  assert(p_env!=NULL);
  int n_rows = p_env->n_rows;
  int n_cols = p_env->n_cols;
  int block_dropped=0;
  int somme=0;
  int i,j;
  int win=0; //Si l'état terminal verifié plus tard est un état vainqueur ou perdant
  (*reward)=0;
  if(p_env->grid[0][action]==1)
  {
    (*reward)+=-10.0;
}
  else
    for (i = n_rows-1; i>=0; i--)
    {
      //printf("boucle for");
      if(p_env->grid[i][action]==0 && block_dropped==0)
      {
        p_env->grid[i][action]=1;
        for (j = 0; j < n_cols; j++)
        {
          somme+=p_env->grid[i][j];
        }
        if(somme==n_cols)
        {
          remove_line(i,p_env);
          (*reward)=100.0;
        }
        block_dropped =1;
      }
    }
    //printf("apres for");
    gridtostate(p_env);
    (*terminal) = is_terminal_state(p_env,p_env->cell,&win);

  if (*terminal) //calcul des points
  {
    //printf("%llu",p_env->cell);
    if(win)
      (*reward)+=1000.0;
    else
      (*reward)+=-1000.0;
  }
  (*reward)-=1.0;
  return env_observe_state(p_env);

}

/** Print an action. 
 * @param action The action to be printed.
 */
 void env_print_action(action_t action) {
  printf("\nAction : %d\n",action);
}

void env_print_values(env_t* p_env, double* values)
{

  assert(p_env!=NULL);
  printf("    values=[ "); 
    unsigned long long int n_states = env_get_number_of_possible_states(p_env);
    state_t state;
    for (state=0; state<n_states; state++) 
      printf(" %5.2f",values[state]);
    printf(" ]");

  }
/*
  void env_print_qvalues(env_t* p_env, double** qvalues)
  {
    assert(p_env!=NULL);
    unsigned int n_actions = env_get_number_of_possible_actions(p_env);
    unsigned long long int n_states = env_get_number_of_possible_states(p_env);

    state_t state;
    action_t action;

    printf("\nQ-values\n         state : "); 
    for (state=0; state<n_states; state++) 
    {
      if (is_terminal_state(p_env,state))
        printf("   TERMI");
      else
        printf("      %02llu",state);
    }
    printf("\n");

    for (action=0; action<n_actions; action++) 
    {
      printf("  action="); 
      env_print_action(action);
      printf(": "); 
      for (state=0; state<n_states; state++) 
        printf("  %6.2f",qvalues[state][action]);
      printf("\n");
    }
    printf("   greedy pol. : "); 
    for (state=0; state<n_states; state++)
    {
      if (is_terminal_state(p_env,state)) {
        printf("   TERMI");
      } else {
        printf("  ");
        env_print_action(max(max(qvalues[state][LEFT],qvalues[state][RIGHT]),max(qvalues[state][UP],qvalues[state][DOWN])));
      }

    }
    printf("\n");

  }
*/
  void env_destroy(env_t** p_env) {
    free(*p_env);
    (*p_env) = NULL;
  }




