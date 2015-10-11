/** @file learning_curve.h
 * @brief Functionality for saving a learning curve to file, and plotting it.
 */
#ifndef LEARNING_CURVE_H
#define LEARNING_CURVE_H

#include "rl.h"

/** Open the file to which the learning curve will be saved. 
 *  If your executables' name is 'rl_grid1D_random', then the name of the file will be
 *  rl_grid1D_random_learning_curve.txt 
 *  @param program_name The name of the executable being called.
 */
void learning_curve_open_file(char* program_name);

/** Save one measurement to the learning curve file. 
 *  @param episode_reward The reward measurment to be saved to file 
 */
void learning_curve_add_measurement(reward_t episode_return);

/** Close the file to which the learning curve was saved. */
void learning_curve_close_file(void);

/** Plot the learning curve with gnuplot. */
void learning_curve_plot(void);


#endif        //  #ifndef LEARNING_CURVE_H

