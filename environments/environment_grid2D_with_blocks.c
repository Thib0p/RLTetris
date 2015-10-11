/** @file environment_grid2D_with_blocks.c
 *  @brief L'environnement 2D avec les blocks(walls)
 *  L'environnement 2D avec les blocks (walls). Les blocs sont codés en dur dans la fonction void create_blocks(env_t* p_env)
 *  Par defaut une grille 5x5 est lancée. Pour spécifier d'autres valeurs vous pouvez utiliser :
 * <tt>./filename nbre_lignes nbre_colonnes</tt>
 */
 
#include "../environment.h"
#include "../environment_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define NOMBRE_LIGNES 5
#define NOMBRE_COLONNES 5
static char** char_array_2D=NULL;
/** Convenient enum for the possible actions. */
 enum actions 
 {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

/**
 * Implementation of the 1D grid environment structure
 */
 struct env_impl_t {

  /** The current state of the environment: in which cell is the agent? */
  unsigned long long int cell;
  
  /** Number of cells in the 1D grid */
  unsigned long long int n_cells;
  
  /** Number of possible actions */
  unsigned int n_actions;
  unsigned long long int n_rows;
  unsigned long long int n_cols;
  char** blocks;
};
/**Permet de créer les murs et le système de gestion des murs
 * @param *p_env pointeur vers l'environnement
 */
void create_blocks(env_t* p_env)// Fonction qui permet de créer les blocks(walls)
{
  unsigned long long int i;
  unsigned long long int j;
  unsigned long long int colonnes = p_env->n_cols;
  unsigned long long int lignes = p_env->n_rows;
  p_env->blocks = malloc(lignes*sizeof(int*));
  for(i=0;i<lignes;i++)
    p_env->blocks[i] = malloc(colonnes*sizeof(int));

  for (i=0;i<lignes;i++)
  {
    for (j=0;j<colonnes;j++)
    {
      p_env->blocks[i][j]=0;
    }
  }
  p_env->blocks[0][3]=1;
  p_env->blocks[1][3]=1;
  p_env->blocks[2][2]=1;

}

double max(double a, double b)
{
  return (a>b?a:b);
}

/** Création de l'environnement. 
 *  @param argc nombre de paramètres fournies à l'executable
 *  @param argv paramètres fournis à l'executable
 */
env_t* env_create(int argc, char** argv) { // Fonction pour la création de l'environnement 
srand(time(NULL));
  env_t* p_env = malloc(sizeof(struct env_impl_t));
  assert(p_env!=NULL);
  p_env->n_actions = 4;
  p_env->n_rows = NOMBRE_LIGNES;
  p_env->n_cols = NOMBRE_COLONNES;
  p_env->n_cells = p_env->n_cols*p_env->n_rows;
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
    initialize_char_array_2D(p_env);
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
 int is_terminal_state(env_t* p_env, unsigned int state) {
  assert(p_env!=NULL);
  // La cellule en bas à droite est un état terminal
  if (state==0)
    return 1;
  // Right cell is also a terminal state
  //if (state==p_env->n_cells-1)
  //  return 1;
  return 0;
}

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
  //p_env->cell = p_env->n_cells-1;
  // Put agent at random position (but not in a terminal state)
  create_blocks(p_env);
  do {
    p_env->cell = rand()%p_env->n_cells;
   // printf("Mur : %d\nnumero de la cellule:%llu\nligne:%llu\ncolonne:%llu\n",is_a_wall_here(p_env),p_env->cell,p_env->cell/p_env->n_cols,p_env->cell%p_env->n_rows);
  } while (is_terminal_state(p_env,p_env->cell) || is_a_wall_here(p_env));
  // Return first observed state
  return env_observe_state(p_env);
}
/** renvoie 1 si la p_env->cell contient un mur  et 0 sinon
 *  @param *p_env un pointeur vers l'environnement
*/
int is_a_wall_here(env_t* p_env)
{
  unsigned long long int num_cell = p_env->cell;
  unsigned long long int num_row = num_cell/p_env->n_cols;
  unsigned long long int num_col = num_cell%p_env->n_rows;
  if(p_env->blocks[num_row][num_col]==1)
    return 1;
  return 0;
}
/** mise à jour de l'environnement à chaque step
 *  @param *p_env un pointeur vers l'environnement
 *  @param action l'action envoyée par l'agent
 *  @param *reward renvoie le reward
 *  @param *terminal renvoie si l'état est terminal
*/
state_t env_step(env_t* p_env, action_t action, double* reward, int* terminal) {
  assert(p_env!=NULL);
  unsigned long long int n_rows = p_env->n_rows;
  unsigned long long int n_cols = p_env->n_cols;
  int has_touched_wall=0;
  if (action==LEFT && (p_env->cell%n_cols)>0 ) //On verifie que l'action est possible ( on est pas sur un bord)
  {
    if(p_env->blocks[(p_env->cell/n_cols)][(p_env->cell%n_rows)-1]==0)//On verifie que l'action est possible (il n'y a pas un mur qui bloque)
      p_env->cell--;//on effectue l'action
    else
      has_touched_wall=1;//On indique qu'on a rencontré un mur pour les pénalités.
  }

  if (action==RIGHT && p_env->cell%n_cols<(n_cols-1))
  {
    if(p_env->blocks[p_env->cell/n_cols][(p_env->cell%n_rows)+1]==0)
      p_env->cell++;
    else
      has_touched_wall=1;
  }
  if (action==UP && n_cols-1<p_env->cell)
  {
    if(p_env->blocks[(p_env->cell/n_cols)-1][p_env->cell%n_rows]==0)
      p_env->cell = p_env->cell-n_cols;
    else
      has_touched_wall=1;
  }
  if (action==DOWN && p_env->cell<(n_cols*(n_rows-1)))
  {
    if(p_env->blocks[(p_env->cell/n_cols)+1][p_env->cell%n_rows]==0)
      p_env->cell =  p_env->cell+n_cols;
    else
      has_touched_wall=1;
  }
  (*terminal) = is_terminal_state(p_env,p_env->cell);
  if (*terminal) //calcul des points
    (*reward)=10000.0;
  else if (has_touched_wall==1)
    (*reward)=-100.0;
  else
    (*reward)=-1.0;
  
  return env_observe_state(p_env);

}



/** initialisation du tableau d'affichage avec les caractères
 * @param *p_env poiteur vers l'environnement.
 */
void initialize_char_array_2D(env_t* p_env)
{
  unsigned long long int colonnes = p_env->n_cols;
  unsigned long long int lignes = p_env->n_rows;
  unsigned long long int i;
  
  if ((char_array_2D)==NULL)
  {
    // Initialize 2D array with only one row
    (char_array_2D) = malloc(lignes*sizeof(char*));
    for(i=0;i<lignes;i++)
    {
    (char_array_2D)[i] = malloc(colonnes*sizeof(char));
  }
  }
}
/** Mise à jour du tableau de caractères
 * @param *p_env poiteur vers l'environnement.
 */
void env_get_char_array_2D(env_t* p_env)
{
  assert(p_env!=NULL);
  int colonnes = p_env->n_cols;
  int lignes = p_env->n_rows;
  int i,j;
  for (i=0; i<lignes; i++) 
  {
    for (j=0; j<colonnes; j++) 
    {
      if (p_env->cell==i*colonnes+j)
      char_array_2D[i][j] = 'A'; // Agent
    else if (is_terminal_state(p_env,i*colonnes+j))
      char_array_2D[i][j] = 'T'; // Terminal state
    else
      char_array_2D[i][j] = '.'; // Empty cell
    if(p_env->blocks[i][j]==1)
    {
    char_array_2D[i][j] = 'X'; // block
  }
}
}
}
/** Affichage de l'état 
 * @param *p_env poiteur vers l'environnement.
 */
void env_print_state(env_t* p_env) 
{
  int n_rows  = p_env->n_rows;
  int n_cols  = p_env->n_cols;
  env_get_char_array_2D(p_env);
  assert(p_env!=NULL);
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

/** Print an action. 
 * @param action The action to be printed.
 */
 void env_print_action(action_t action) {
  if (action==LEFT)
    printf("  LEFT");
  else if (action==RIGHT)
    printf("  RIGHT");
  else if (action==UP)
    printf("  UP");
  else
    printf(" DOWN");
}
/** Libère la mémoire
 *  @param *p_env un pointeur vers l'environnement
*/
  void env_destroy(env_t** p_env) {
    free(*p_env);
    (*p_env) = NULL;
  }




