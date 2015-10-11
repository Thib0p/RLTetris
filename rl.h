/** @file rl.h
    @brief Contains action and state types, required to interface between the agent and the environment.
*/

#ifndef RL_H
#define RL_H

/** Reinforcement learning action.
 *  In discrete environments, actions can be described as whole numbers
 */
typedef unsigned int action_t;

/** Reinforcement learning state.
 *  It is a very large int, to enable large state spaces
 */
typedef unsigned long long int state_t;

/** Reinforcement learning reward.
 */
typedef double reward_t;

#endif

/*! \mainpage IN104 Reinforcement Learning Project Documentation

\section sec_intro Introduction

Reinforcement learning aims at learning to perform the right behavior from only rewards; the task of the teacher is thus to give rewards for good behavior, which is usually much easier than specifying the right behavior itself.
For instance, reinforcement learning algorithms have been able to learn Backgammon almost as good as the world champions (<a href="http://en.wikipedia.org/wiki/TD-Gammon" target="_blank">http://en.wikipedia.org/wiki/TD-Gammon</a>), and to perform robotics tricks such as ball-in-cup <a href="http://www.youtube.com/watch?v=qtqubguikMk" target="_blank">http://www.youtube.com/watch?v=qtqubguikMk</a>) and flipping pancakes (<a href="http://www.youtube.com/watch?v=W_gxLKSsSIE" target="_blank">http://www.youtube.com/watch?v=W_gxLKSsSIE</a>).
These tasks would be extremely difficult to program by hand, and therefore it is preferable to design algorithms that are able to \em learn them.
In this project, you will implement several reinforcement learning agents, and have them learn different tasks in different environments, ranging from simple grid worlds to the game of Tetris.

\section sec_aims Objectives

Our objectives in this project are two-fold. 

\li We want you to learn about the important concepts in reinforcement learning, and how to implement them. Core reinforcement learning concepts which you should be able to explain after this project include: the \b agent-environment \b interface, an agent's \b policy, \b value \b functions, \b learning value functions, \b learning \b curves.

\li We want you to learn how to manage, implement and document a C project. This includes setting intermediate \b goals, writing \b doxygen \b documentation, and thinking about the \b design of your program before you implement it. A particularly important concept which we want you to understand is the difference between \b declarations \b and \b definitions in C, as they are essential to designing modular code in C. 

\section sec_project_development Project Development

\htmlonly This documentation is structured into several phases, which are described on separate pages in this HTML documentation, and in separate chapters in the main PDF document which is available on the project website (sujet.pdf). 
To get started and to get a general overview of the project we recommend to use the PDF version. To browse the code and understand it more deeply, this HTML documentation is preferable. If you are reading longer pages of text in your browser, we recommend to not make it full screen; this leads to very long lines...
\endhtmlonly

\latexonly This project is structured into several phases, which correspond to the chapters of this document:
\endlatexonly

\li \ref phase1
\li \ref phase2 
\li \ref phase3
\li \ref phase4 
\li \ref phase5 

Each phase is split into three parts: 
\li a part where new reinforcement learning concepts are introduced
\li a part where we explain how these concepts have been (by us) or could be (by you) implemented in C
\li a list of questions that you should be able to answer before proceeding to the next phase.

We expect you to finish Phase 1-3 within the duration of the course. Phase 4 should certainly be possible also. Achieving Phase 5 would be an excellent achievement.

\section Evaluation 

Your project will be evaluated by the following files you submit at the end of the project: 

\li \b src.tgz -
Your source code.
\li \b html.tgz -
A file containing the doxygen documentation. Is the documentation complete? Are all functions and structures documented? Is it accurate? (documentation may be in French)
\li \b rl_grid1D_random, \b rl_grid2D_qvalues, etc. -
Executables that run different agents on different environments, and demonstrate that the agent learns the task successfully.
\li \b Answers to a list of questions about reinforcement learning and modular programming. These questions are part of the code documentation. (answers may be in French)

If you're just getting started, please continue to \ref phase1. This first phase is about understanding the fundamentals of reinforcement learning, and the source code that is provided to you. Therefore, Phase 1 spans almost half of this document.
*/

 

