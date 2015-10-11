// Doxygen page for Phase 3
/*!
\page phase3 Phase 3: Adding a new environment

\section sec_phase3 Phase 3: Adding a new environment

\b Aim: Realize a novel 2D grid environment. Let your agents learn in this environment.

\subsection sec_code3 Implementation in C: A new environment for all agents


It may help to base your 2D grid on the provided code for the 1D grid.
\code
cp environments/environment_grid1D.c environments/environment_grid2D.c
gcc -Wall -g environments/environment_grid2D.c agents/agent_random.c main.c -o rl_grid2D_random
\endcode

Whereas the state of the 1D grid could be descibed by a single unsigned int, the state of the 2D grid is slightly more complicated. How will you encode this state? The env_step() function returns only one unsigned (long long) int as an state. How will you convert the 2D state of the environment into a single integer value?

Compile this new environment against your agent_vlearning.c and agent_qlearning.c, and run the programs. What do you see?

\subsubsection sec_code3_walls Adding walls 

By adding walls, you can turn your 2D grid into a maze that the agent should find its way through. Since it is rather stupid to bump into walls, penalize the agent for every time it bumps into a wall, i.e. it performs the action left, but there is a wall to the left. How will you represent these walls in the .c file? Which functions in environment_grid2D.c are affected by this addition?

Run the agent_vlearning and agent_qlearning in this environment. What do you see? 

\subsection sec_questions3 Questions Phase 3

Your answers, which you should include in the file answers.txt, will count for your grade.

\li Q3.1 When you run your reinforcement learning agents on this new environment, how do the values in the grid change over time as learning progresses?

\li Q3.2 How does adding walls influence the learning of values? What is the difference if you add/remove the penalty for bumping into walls?

Once you have answered these questions, you are ready for the next phase.

*/
