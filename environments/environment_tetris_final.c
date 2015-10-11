/** @file environment_tetris_final.c
 *  L'environnement complet de Tetris
 *  La taille de l'environnement se change via les #define NOMBRE_LIGNES et NOMBRE_COLONNES
 */
 
#include "../environment.h"
#include "../environment_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
#define NOMBRE_LIGNES 10
#define NOMBRE_COLONNES 10
/**
 * Implémentation de la strcuture de l'environnemnt Tetris
 */
 struct env_impl_t {

  /** The current state of the environment */
  unsigned long long int cell;
  
  /** Number of cells in the 1D grid */
  unsigned long long int n_cells;
  int n_lignes_detruites;
  /** Number of possible actions */
  unsigned int n_actions;
  /** Number of possible formes */
  int n_formes;
  /** Toutes les formes qu'il est possible de poser */
  int formes[6][4][4][4]; // contient les formes possibles dans une grille 4*4 rotations comprises
  /** La forme actuellement en attente d'être déposée */
  int forme;
  /** Précision du sens de la forme (rotation) */
  int rotation_forme;
  /** Frontière basse de la forme. */
  int frontiere_forme[4];
  /** Nombre de lignes de la grille */
  int n_rows;
  /** Nombre de colonnesde la grille */
  int n_cols;
  /** la représentation de la grille avec des 0 dans les cases vides et des 1 dans les cases pleines. */
  int** grid;
  /** La frontière haute actuelle de la grille */
  unsigned int frontiere[NOMBRE_COLONNES]; // frontiere ( n_colonnes)

};


/** Permet d'élever un nombre à une puissance.
@param a la puissance
@param b le nombre élevé à la puissance donnée
*/
unsigned long long int power(unsigned long long int a, int b) // renvoie b^a
{
  int i;
  unsigned long long int output = 1;
  for(i=0;i<a;i++)
  {
    output= output*b;
  }
  return output;
}
/**convertit la grille dans laquelle il est simple de travailler en un état standard sur lequel peut travailler l'agent
@param *p_env pointeur vers l'environnement
*/
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
  state = state+power(p_env->n_cols*p_env->n_cols+p_env->forme,2);
  p_env->cell = state;

    //printf("\n%llu\n",p_env->cell);

}

/**Initialise la grille avec des zeros partout
@param *p_env pointeur vers l'environnement
*/
void reinitialize_grid(env_t* p_env)
{
  unsigned  i,j;
  int colonnes = p_env->n_cols;
  int lignes = p_env->n_rows;
  p_env->n_lignes_detruites=0;
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
/**Alloue de la mémoire pour créer la grille du tetris
@param *p_env pointeur vers l'environnement
*/
void create_grid(env_t* p_env)// Fonction qui permet de créer les grid(walls)
{
  unsigned  i;
  int colonnes = p_env->n_cols;
  int lignes = p_env->n_rows;
  p_env->grid = malloc(lignes*sizeof(int*));
  for(i=0;i<lignes;i++)
    p_env->grid[i] = malloc(colonnes*sizeof(int));
}

double max(double a, double b)
{
  return (a>b?a:b);
}



/**Initialise la liste des formes
@param *p_env pointeur vers l'environnement
*/
void initialisation_formes(env_t *p_env)
{
  int i,j,k,l;
  for ( i = 0; i < 6; i++)
  {
    for ( j = 0; j < 4; j++)
    {
      for ( k = 0; k < 4; k++)
      {
        for (l = 0; l < 4; l++)
        {
          p_env->formes[i][j][k][l]=0;
        }
      }
    }
  }
    /*
forme :
-----------------------------------------------------------------------
0)
                                        x
                                        x
                                        x
                                        x


*/
/*
0 degrès
*/
p_env->formes[0][0][0][0] = 1;
p_env->formes[0][0][1][0] = 1;
p_env->formes[0][0][2][0] = 1;
p_env->formes[0][0][3][0] = 1;
/*
90 degrès (trigo)
*/

p_env->formes[0][1][3][0] = 1;
p_env->formes[0][1][3][1] = 1;
p_env->formes[0][1][3][2] = 1;
p_env->formes[0][1][3][3] = 1;
/*
180 degrès (trigo)
*/
p_env->formes[0][2][0][0] = 1;
p_env->formes[0][2][1][0] = 1;
p_env->formes[0][2][2][0] = 1;
p_env->formes[0][2][3][0] = 1;
/*
270 degrès (trigo)
*/
p_env->formes[0][3][3][0] = 1;
p_env->formes[0][3][3][1] = 1;
p_env->formes[0][3][3][2] = 1;
p_env->formes[0][3][3][3] = 1;
/*
1)
-------------------------------------------------------------------------------
                                                    xx
                                                    xx
*/
/*
0 degrès
*/
p_env->formes[1][0][3][0] = 1;
p_env->formes[1][0][3][1] = 1;
p_env->formes[1][0][2][0] = 1;
p_env->formes[1][0][2][1] = 1;
/*
90 degrès (trigo)
*/

p_env->formes[1][1][3][0] = 1;
p_env->formes[1][1][3][1] = 1;
p_env->formes[1][1][2][0] = 1;
p_env->formes[1][1][2][1] = 1;
/*
180 degrès (trigo)
*/
p_env->formes[1][2][3][0] = 1;
p_env->formes[1][2][3][1] = 1;
p_env->formes[1][2][2][0] = 1;
p_env->formes[1][2][2][1] = 1;
/*
270 degrès (trigo)
*/
p_env->formes[1][3][3][0] = 1;
p_env->formes[1][3][3][1] = 1;
p_env->formes[1][3][2][0] = 1;
p_env->formes[1][3][2][1] = 1;

/*
2)
--------------------------------------------------------------------------
                                                                  x
                                                                  x
                                                                  xx
*/
/*
0 degrès (trigo)
*/
p_env->formes[2][0][1][0] = 1;
p_env->formes[2][0][2][0] = 1;
p_env->formes[2][0][3][0] = 1;
p_env->formes[2][0][3][1] = 1;

/*
90 degrès (trigo)
*/

p_env->formes[2][1][3][0] = 1;
p_env->formes[2][1][3][1] = 1;
p_env->formes[2][1][3][2] = 1;
p_env->formes[2][1][2][2] = 1;
/*
180 degrès (trigo)
*/
p_env->formes[2][2][1][0] = 1;
p_env->formes[2][2][1][1] = 1;
p_env->formes[2][2][2][1] = 1;
p_env->formes[2][2][3][1] = 1;
/*
270 degrès (trigo)
*/
p_env->formes[2][3][3][0] = 1;
p_env->formes[2][3][2][0] = 1;
p_env->formes[2][3][2][1] = 1;
p_env->formes[2][3][2][2] = 1;


/*
-----------------------------------------------------------------------
3)

                                                                xx
                                                                 xx
*/
                                                                 /*
0 degrès
*/
p_env->formes[3][0][2][0] = 1;
p_env->formes[3][0][2][1] = 1;
p_env->formes[3][0][3][1] = 1;
p_env->formes[3][0][3][2] = 1;
/*
90 degrès (trigo)
*/

p_env->formes[3][1][2][0] = 1;
p_env->formes[3][1][3][0] = 1;
p_env->formes[3][1][2][1] = 1;
p_env->formes[3][1][1][1] = 1;
/*
180 degrès (trigo)
*/
p_env->formes[3][2][2][0] = 1;
p_env->formes[3][2][2][1] = 1;
p_env->formes[3][2][3][1] = 1;
p_env->formes[3][2][3][2] = 1;
/*
270 degrès (trigo)
*/
p_env->formes[3][3][2][0] = 1;
p_env->formes[3][3][3][0] = 1;
p_env->formes[3][3][2][1] = 1;
p_env->formes[3][3][1][1] = 1;
/*
4)
-----------------------------------------------------------------------

                                                             xx
                                                            xx
*/
/*
0 degrès
*/
p_env->formes[4][0][3][0] = 1;
p_env->formes[4][0][3][1] = 1;
p_env->formes[4][0][2][1] = 1;
p_env->formes[4][0][2][2] = 1;
/*
90 degrès (trigo)
*/

p_env->formes[4][1][1][0] = 1;
p_env->formes[4][1][2][0] = 1;
p_env->formes[4][1][2][1] = 1;
p_env->formes[4][1][3][1] = 1;
/*
180 degrès (trigo)
*/
p_env->formes[4][2][3][0] = 1;
p_env->formes[4][2][3][1] = 1;
p_env->formes[4][2][2][1] = 1;
p_env->formes[4][2][2][2] = 1;
/*
270 degrès (trigo)
*/
p_env->formes[4][3][1][0] = 1;
p_env->formes[4][3][2][0] = 1;
p_env->formes[4][3][2][1] = 1;
p_env->formes[4][3][3][1] = 1;

/*
-----------------------------------------------------------------------
5)
                                                                    xxx
                                                                     x
*/
p_env->formes[5][0][2][0] = 1;
p_env->formes[5][0][2][1] = 1;
p_env->formes[5][0][2][2] = 1;
p_env->formes[5][0][3][1] = 1;
/*
90 degrès (trigo)
*/

p_env->formes[5][1][3][0] = 1;
p_env->formes[5][1][2][0] = 1;
p_env->formes[5][1][1][0] = 1;
p_env->formes[5][1][2][1] = 1;
/*
180 degrès (trigo)
*/
p_env->formes[5][2][3][0] = 1;
p_env->formes[5][2][3][1] = 1;
p_env->formes[5][2][3][2] = 1;
p_env->formes[5][2][2][1] = 1;
/*
270 degrès (trigo)
*/
p_env->formes[5][3][1][1] = 1;
p_env->formes[5][3][2][0] = 1;
p_env->formes[5][3][2][1] = 1;
p_env->formes[5][3][3][1] = 1;

}

/**Crée l'environnement
@param *p_env pointeur vers l'environnement
*/
env_t* env_create(int argc, char** argv) 
{ // Fonction pour la création de l'environnement 
env_t* p_env = malloc(sizeof(struct env_impl_t));
assert(p_env!=NULL);
initialisation_formes(p_env);
p_env->n_actions = NOMBRE_COLONNES+4;
p_env->n_rows = NOMBRE_LIGNES;
p_env->n_cols = NOMBRE_COLONNES;
p_env->n_formes=6;
p_env->rotation_forme=0;
p_env->n_lignes_detruites=1;
p_env->n_cells = power(p_env->n_cols*p_env->n_rows,2);
create_grid(p_env);
if (argc>1) {
  if (strcmp(argv[1],"--help")==0)
  { 
    printf("env_init for grid2D takes parameters [number of cells (int)]\n");
    return NULL;
  }
  else
  {
    p_env->n_cells = atoi(argv[1]);
  }
}
int i;
for(i=0;i<p_env->n_cols;i++) {
  p_env->frontiere[i]=8;
}
printf("Initialized environment grid2D: n_cells=%llu\n",p_env->n_cells);
return p_env;
}



/** Get number of possible states */
unsigned long long int env_get_number_of_possible_states(env_t* p_env) {
  assert(p_env!=NULL);
  unsigned long long int a=p_env->n_rows+1;
  a = (p_env->n_rows+1)+
  power(1,p_env->n_rows+1)*(p_env->n_rows+1)+
  power(2,p_env->n_rows+1)*(p_env->n_rows+1)+
  power(3,p_env->n_rows+1)*(p_env->n_rows+1)+
  6*power(4,p_env->n_rows+1)+
  4*power(4,p_env->n_rows+1)*6;
  printf("\na : %llu\n",a);
  return a; 
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
  *win=1;
  return 1;
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

/** Affiche la grille
 *  @param *p_env un pointeur vers l'environnement
 */
//---------------------------------------------------------------------------------------------------------------------
 void env_print_state(env_t* p_env)
 {
  int n_rows = p_env->n_rows;
  int n_cols = p_env->n_cols;
  //printf("\n\n\nState : %llu\n\n\n",p_env->cell);
  printf("\nLignes :%d\n colonnes:%d\n",p_env->n_rows,p_env->n_cols);
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
/** Determine la largeur de la pièce qui va tomber. On a preferé ne pas coder cette largeur en dure comme ça on peut rajouter n'importe quelle forme en ne codant que les pixels de la forme ! (plus amusant non ? :-)   )
 *  @param *p_env un pointeur vers l'environnement
 */
 int largeur_piece(env_t *p_env)
 {
  int i,j;
  int largeur = 4;
  int somme;
  for(j=0;j<4;j++)
  {
    somme = 0;
    for(i=0;i<4;i++)
    {
      somme = somme+ p_env->formes[p_env->forme][p_env->rotation_forme][i][j];
    }
    if(somme != 0)
      largeur = j+1;


  }
  return largeur;
}

/** Calcule pour chaque colonne de la forme actuelle la frontière basse, c'est à dire la distance qui sépare son pixel inferieur de la bordure basse
 *  @param *p_env un pointeur vers l'environnement
 */
 void calcul_distance_bas_forme(env_t* p_env)
 {
  int i,j,test;

  for(j=0;j<4;j++)
  {
    test=0;
    for(i=3;i>=0;i--)
    {
      if(p_env->formes[p_env->forme][p_env->rotation_forme][i][j]==1&&test==0)
      {
        p_env->frontiere_forme[j]=3-i;
        test =1;
      }
    }
  }
}


/** effectue l'action sur l'environnement
 *  @param *p_env un pointeur vers l'environnement
 */
 void action_f(env_t* p_env,action_t action,int* terminal)
 {
  int min=p_env->n_rows;
  int largeur,j,i;
  action_t action_reelle = action;
  if(action>p_env->n_cols)
  {
    p_env->rotation_forme=action-p_env->n_cols;
  }
  else
  {
    largeur = largeur_piece(p_env);
    if(action_reelle+largeur>p_env->n_cols)
    {
      action_reelle = p_env->n_cols-largeur;
    }
    //printf("test01 : \nLignes :%d\n colonnes:%d\n",p_env->n_rows,p_env->n_cols);
    calcul_distance_bas_forme(p_env);
    
    env_observe_state(p_env);
    for(j=0;j<largeur;j++)
    {
      if(min>(p_env->frontiere[j+action_reelle]+p_env->frontiere_forme[j]))
      {
        min = p_env->frontiere[j+action_reelle]+p_env->frontiere_forme[j];
      }
    }
    for(j=0;j<largeur;j++)
      for (i = 3; i>=0; i--)
      {
        if(min-i-1>=0){
          p_env->grid[min-i-1][action_reelle+j]=p_env->grid[min-i-1][action_reelle+j]+p_env->formes[p_env->forme][p_env->rotation_forme][3-i][j];
        }
        else
        {
          if(p_env->formes[p_env->forme][p_env->rotation_forme][i][j]==1)
          {
            *terminal =1;
          }
        }
      }
      p_env->forme = (rand()%p_env->n_formes);
      p_env->rotation_forme = (rand()%4);
    }
  }

/** Gère toute la partie de supression de ligne et la mise à jour de l'environnement lorsqu'une ligne a été remplie
 *  @param ligne le numero de la ligne à supprimer
 *  @param *p_env un pointeur vers l'environnement
 */
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
/** Observe l'état pour le renvoyer à l'agent.
 *  @param *p_env un pointeur vers l'environnement
*/
 state_t env_observe_state(env_t* p_env) 
 {
  assert(p_env!=NULL);
  int i,j,a;
  unsigned int etat_frontiere;
  for(j=0;j<p_env->n_cols;j++) {
    if ( p_env->grid[p_env->n_rows-1][j] == 0 ) {
     a=p_env->n_rows;
   }
   for(i=p_env->n_rows-1;i>=0;i--) {
    if ( (p_env->grid)[i][j] == 1 ) { a=i;}

  }
  p_env->frontiere[j]=a;
}
etat_frontiere = convert_frontiere_to_etat_frontiere(p_env);
return etat_frontiere;
}
/** Convertit la frontière en un état envoyable directement à l'agent : c'est la première optimisation majeure du tetris
 *  @param *p_env un pointeur vers l'environnement
*/
 unsigned int convert_frontiere_to_etat_frontiere(env_t* p_env)
 {
  unsigned int etat_frontiere;
  etat_frontiere = p_env->frontiere[0]+
  power(1,p_env->n_rows+1)*p_env->frontiere[1]+
  power(2,p_env->n_rows+1)*p_env->frontiere[2]+
  power(3,p_env->n_rows+1)*p_env->frontiere[3]+
  p_env->forme*power(4,p_env->n_rows+1)+
  p_env->rotation_forme*power(4,p_env->n_rows+1)*p_env->n_formes;
  return(etat_frontiere);
}
/** Initialisation de l'environnement à chaque épisode
 *  @param *p_env un pointeur vers l'environnement
*/
 state_t env_start(env_t* p_env) {
  assert(p_env!=NULL);
  reinitialize_grid(p_env);
  p_env->forme = (rand()%p_env->n_formes);
  return env_observe_state(p_env);
}
/** mise à jour de l'environnement à chaque step
 *  @param *p_env un pointeur vers l'environnement
*/

 state_t env_step(env_t* p_env, action_t action, double* reward, int* terminal) {
  assert(p_env!=NULL);
  int n_rows = p_env->n_rows;
  int n_cols = p_env->n_cols;
  int somme=0;
  int i,j;
  int win=0; //Si l'état terminal verifié plus tard est un état vainqueur ou perdant
  (*reward)=0;
  action_f(p_env,action,terminal);
  for(i=0;i<n_rows;i++)
  {
    somme=0;
    for(j = 0; j < n_cols; j++)
    {
      somme+=p_env->grid[i][j];
    }
    if(somme==n_cols)
    {
      remove_line(i,p_env);
      (*reward)=10000.0;
    }
  }
  gridtostate(p_env);
  if(*terminal!=1)
    (*terminal) = is_terminal_state(p_env,p_env->cell,&win);

  if(action > p_env->n_rows) { 
    (*reward)-=10.0;
  }
  if (*terminal) //calcul des points
  {
    if(win)
      (*reward)+=10000.0;
  }
  (*reward)+=1.0;

  return env_observe_state(p_env);
}

/** Print an action. 
 * @param action The action to be printed.
 */
 void env_print_action(action_t action) {
  printf("\nAction : %d\n",action);
}
/** Libère la mémoire
 *  @param *p_env un pointeur vers l'environnement
*/
 void env_destroy(env_t** p_env) {
  free(*p_env);
  (*p_env) = NULL;
}




