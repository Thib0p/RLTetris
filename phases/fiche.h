// Doxygen page for the "fiche du projet".
/*!
\page fiche `Fiche' of the project ``Reinforcement Learning'' 

\section sec_fiche `Fiche' of the project ``Reinforcement Learning'' 

Dogs are trained  by giving rewards (dog cookies, ``good dog!'') and punishments (``bad dog!''). By giving the appropriate reinforcements (rewards/punishments), dogs can learn quite sophisticated tasks (fetch a stick, roll over). This form of learning is known as `reinforcement learning'.
Reinforcement learning is very useful when we cannot communicate what should be done -- dogs don't speak human language, at least not a lot
\htmlonly (<a  href="http://www.youtube.com/watch?v=BCKhTCVnrbE" target="_blank">http://www.youtube.com/watch?v=BCKhTCVnrbE</a>) \endhtmlonly
-- or when we don't know exactly how to achieve the task ourselves -- which is often the case for robots. Because we usually know what we want the robot to do, but not exactly how it should actually achieve it, reinforcement learning is becoming more and more popular in robotics.

\image html dog_annotated.png
\image latex dog_annotated.png "" height=4cm

In this project, you will implement several reinforcement learning algorithms, and apply them to several environments and tasks. The environments considered increase in complexity, which increases the demands on the ability of your agents to learn.

\subsection objectives Objectives

The main aims of this project are to: 1) understand the reinforcement learning problem, and the basic algorithms for solving such problems. 2) learn to write modular code, in which learning algorithms and enviroments can easily be exchanged without modifying the code.

<b>Different learning agents.</b>
An initial simple agent will be provided by us as C code. This agent just performs random action, and does not learn anything. Your goal will be to replace this agent with 1) an agent that learns the \em value of each state. The value is a prediction about future reward the agent expects to receive. Knowing the optimal values of the states allows the agent to choose the best actions. 2) an agent that uses \em Q-learning. Q-learning is much like value learning, but the agent now learns the value of performing an action in a certain state, rather than the value of the state itself.

<b>Different environments.</b>
An initial 1D grid environment will be provided by us as C code. In this environment, a reward is given when the agent enters left-most grid cell. Your goal will be to implement a 2D grid environment, optionally with walls, and test your different agents in these environments.
Once the agents are able to learn in the 2D grid world, you may try them on the game of `Tetris'. 
We will provide the source code of three variations of Tetris of increasing complexity.
The most complex one, which is the one played around the world, is \em very difficult to solve. If you achieve this, you should join our research group, because you are ready for reinforcement learning on real robots!

\image html environments.png
\image latex environments.pdf "The different environments to be considered. The 1D grid is provided; you will implement the 2D grid. Source code for the Tetris variants is also provided. Being able to learn the `Melax' variant is quite challenging. Learning full Tetris is really \em very difficult; if you achieve it, you are ready for reinforcement learning on real robots!" width=\textwidth

\subsection development Project Development  

There will be five `séances de TP'; the first three are 2 hours, and the last two are 3 hours.
The `séances' of 23 April and 7 May are used to evaluate the intermediate objectives, which are known as ``mile-stones''. 
For the first mile-stone, you should have successfully implemented the value and Q-learning agents, and for advanced programmers also the 2D grid environment.
For the second mile-stone, you should have implemented the 2D grid environment. Advanced programmers may attempt to solve the Tetris variants.
It is very difficult to achieve these goals if you code only during the TPs. You are explicitely asked to make progress by coding outside of the TPs as well.

\subsection criteria Evaluation Criteria 

The project will be evaluated based on the following deliverables:

\li \c html.tgz A file containing the doxygen documentation. Is the documentation complete? Are all functions and structures documented? Is it accurate? (documentation may be in French)

\li \c rl_grid1D_qvalues, \c rl_grid2D_random, Executables that run different agents on different environments, and demonstrate that the agent learns the task successfully.

\li \c answers.pdf The answers to a list of questions (to be provided during the course) about the performance of the agents on the tasks. Examples: Does Q-learning outperform value learning? How do the parameters of the algorithms influence learning?  


 */

