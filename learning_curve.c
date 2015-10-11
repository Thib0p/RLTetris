/** @file learning_curve.c
 * @brief Functionality for saving a learning curve to file, and plotting it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "learning_curve.h"

/** The name of the file the learning curve will be written to. */
static char*  filename;

/** The file the learning curve will be written to. */
static FILE*  file;


void learning_curve_open_file(char* program_name) {
  // If your program's name is "rl_grid1D_random", the learning curve 
  // filename will be "learning_curve_rl_grid1D_random.txt"

  // In argv, the program is preceded by the current directory './'
  // This removes those first two characters, by moving along 2 positions in the char array.
  program_name = &(program_name[2]);
   filename = malloc((strlen(program_name)+strlen("learning_curve.txt")+2000)*sizeof(char));
  sprintf( filename,"lc_%s_learning_curve.txt",program_name);
  // Open the file with the filename above for writing
   file = fopen( filename,"w");
}

void learning_curve_add_measurement(reward_t episode_return) 
{
  fprintf( file,"%1.2f\n",episode_return);
}

void learning_curve_close_file(void) {
  // Finish up with the learning curve
  fclose( file); // Close file
}

void learning_curve_plot(void) {
  printf("\n\nSaved learning curve in %s. Now plotting it.\n\n", filename);  
  // Plot the learning curve using the gnuplot program
  FILE *pipe = popen("gnuplot -persist","w");
  // Pass this command to the gnuplot program through the pipe
  fprintf(pipe, "plot '%s' with lines\n", filename); 
  pclose(pipe);
}

