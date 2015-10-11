// Doxygen page for Phase 2
/*!
\page phase2 Phase 2: Adding reinforcement learning agents

\section sec_phase2 Phase 2: Adding reinforcement learning agents

\subsection sec_rl2 Reinforcement Learning: Value Functions

What is it that we are trying to learn in the first place in reinforcement learning? It is to maximize rewards. In the case of episodic RL, we want to optimize the \b return, which is the sum over all the rewards in an episode
\f$ R_t = r_{t+1} +  r_{t+2} \dots r_{T}\f$ ,  
where \f$ T \f$ is the final time step in the episode. Let's have a look at the returns in the 1D grid world. If the agent always goes left, an episode starting in state "4" will look like this:

\verbatim
                             01234567  state
==   INIT ================> |T...A...|
==   LEFT == (R=  -1.0) ==> |T..A....|
==   LEFT == (R=  -1.0) ==> |T.A.....|
==   LEFT == (R=  -1.0) ==> |TA......|
==   LEFT == (R= 100.0) ==> |A.......|
                  97.0
\endverbatim

Thus, the return of this episode is  \f$ R_t = 100-1-1-1 = 97 \f$ . Because the environment and policy are deterministic (the agent always performs the same action in the same state, and the environment always transitions to the same state from a given action and previous state), we may always expect the same return for this state. This \b expected \b return is known as the \b value of a state, which is written as \f$ V^\pi(s)\f$. In the example above, \f$ V^\pi(s=4) \rightarrow 97 \f$. Values are essentially predictions about rewards to be received in the future. \f$ V^\pi(s=4) \rightarrow 97 \f$ thus means: If you are in state 4, and execute policy \f$ \pi \f$ from there onwards, you are predicted to receive a return of 97 for the episode.

The value \f$ V^\pi(s) \f$ depends not only on the state \f$ s \f$ , but also on the policy \f$ \pi \f$. For instance, if the policy would not be to always go left, but choose left and right randomly each with 50%, the values would be very different. This is because the return \f$ R_t \f$ will usually be different for different episodes starting in the same state. Here are two examples starting in state 4:

\verbatim
state                        01234567                 state                        01234567
==   INIT ================> |T...A...|                ==   INIT ================> |T...A...|
==   LEFT == (R=  -1.0) ==> |T..A....|                ==   LEFT == (R=  -1.0) ==> |T..A....|
==  RIGHT == (R=  -1.0) ==> |T...A...|                ==  RIGHT == (R=  -1.0) ==> |T...A...|
==  RIGHT == (R=  -1.0) ==> |T....A..|                ==  RIGHT == (R=  -1.0) ==> |T....A..|
==   LEFT == (R=  -1.0) ==> |T...A...|                ==   LEFT == (R=  -1.0) ==> |T...A...|
==   LEFT == (R=  -1.0) ==> |T..A....|                ==   LEFT == (R=  -1.0) ==> |T..A....|
==   LEFT == (R=  -1.0) ==> |T.A.....|                ==   LEFT == (R=  -1.0) ==> |T.A.....|
==   LEFT == (R=  -1.0) ==> |TA......|                ==   LEFT == (R=  -1.0) ==> |TA......|
==   LEFT == (R=  -1.0) ==> |T.A.....|                ==   LEFT == (R= 100.0) ==> |A.......|
==   LEFT == (R=  -1.0) ==> |TA......|                                  93.0                 
==   LEFT == (R= 100.0) ==> |A.......|                
                  91.0                    
\endverbatim

Changing the policy thus leads to different returns, and therefore to different values. Furtermore, we see that a stochastic (random) policy leads to different returns for each episode. In cases where the environment and/or agent are stochastic, we therefore speak about values as representing the \em expected return; it is not the return you will always get, but it is the return you get on average.
Whereas the return for the "go left" policy for state 4 was \f$ V^\pi(s=4) \rightarrow 97 \f$,  for the random policy is approximately 56. This is because the agent is often just wandering around randomly, and needs on average 44 steps to reach the terminal state to the left. 

Let's summarize. The \b return \f$ R \f$ of an episode is the sum of the rewards received during the episode. The \b value \f$ V^\pi(s)\f$ of a state is the \b expected \b return, i.e. the average return you may expect to get when many episodes are run. Values depend not only on the state \f$ s \f$, but also on the \b policy \f$ \pi \f$. It is important to understand that values are \b predictions about rewards to be received in the \b future.

\subsubsection sec_learning_values_mc Learning values through Monte-Carlo

The most simple way to learn a value for a state is the following:
\verbatim
state_t state = 4; // Or any other state you want to determine the value for 
double total_returns = 0.0;
for (n_episodes=0; n_episode < max_n_episodes; n_episodes++) {
  double total_return_for_this_episode = run_episode(...);
  total_returns += total_return_for_this_episode;

  // value is the average return per episode, gets more and more accurate
  double value = total_returns/n_episodes;  
}
\endverbatim

This algorithm implements exactly the definition of a value: the expected return is the average return over many episodes, which is equivalent to <tt>total_returns/n_episodes</tt>.
Methods that update the value only \em after an episode is completed are known as \b Monte-Carlo \b methods. An agent that uses this learning method is the first type of agent you will implement.

(if you have any trouble understanding the next sections about reinforcement learning, it might help to first implement the Monte-Carlo learning agent as described in \ref sec_code2_values. This experience may help you to understand the RL theory described below)

\subsubsection sec_learning_values_td Learning values through Temporal-Differencing

For Monte-Carlo methods, you have to wait until the end of an episode to update the values. Temporal differencing (TD) allows you to update the values after each step in the agent-environment interface loop; you don't have to wait until the end of an episode.
The math behind temporal difference learning is explained very well on the standard book on RL (Reinforcement Learning: an Introduction, but Sutton and Barto). Please read the following:
Math behind value functions and the "Bellman equation":\n<a href="http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node34.html" target="_blank">http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node34.html</a>.
TD methods are explained here\n<a href="http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node61.html" target="_blank">http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node61.html</a>.\n
There are several variants of TD learning, but for this project, we consider only TD(0). This requires you to make an array of values, and at each agent_step, to update the values as follows (see equation 6.2 on the html page above):

\verbatim
alpha = 0.1; // learning rate
gamma = 1.0; // discount factor
values[s_t] = values[s_t] + alpha*( r_t_1 + gamma*values[s_t_1] - values[s_t])
s_t current state
s_t_1 next state
r_t_1 reward recieved when going from current to next state
\endverbatim

\subsubsection sec_learning_values_dp Learning values through Dynamic Programming

We do not consider dynamic programming in this project, because it requires a model of the environment, and we only implement model-free reinforcement learning.

\subsubsection sec_qvalues Learning Q-values for state/action pairs

Another type of value is the \b Q-value, which assigns values to state/action pairs, i.e. \f$ Q^\pi(s,a) \f$. This value represents the expected return of executing action \f$ a \f$ in state \f$ s \f$ , and following policy \f$ \pi \f$ afterwards. They may also be learned through Monte-Carlo methods or temporal differencing. The between \f$ Q^\pi(s,a) \f$  and \f$ V^\pi(s) \f$  is quite subtle, and the respective advantages of values and Q-values will (hopefully) become clear to you when implementing them.

You can find more information about Q-values here:\n
<a href="http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node52.html" target="_blank">http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node52.html</a>

How to update them with temporal differencing is explained here:\n
<a href="http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node65.html" target="_blank">http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node65.html</a>



\subsection sec_code2 Implementation in C: Extending agent_random.c

The goal is to program three agents, in the following order: V-learning with Monte Carlo methods (vlearning_mc), Q-learning with Monte-Carlo (qlearning_mc), Q-Learning with Temporal Differencing (qlearning_td). Programming one will really help with the next.

\subsubsection sec_code2_values An agent that learns values through Monte-Carlo

First, make a new agent and compile it 

\code
cp agents/agent_random.c agents/agent_vlearning_mc.c
gcc -Wall -g environments/environment_grid1D.c agents/agent_vlearning_mc.c main.c -o rl_grid1D_vlearning_mc
\endcode

Before you implement the pseudo-code for Monte-Carlo methods (see \ref sec_learning_values) in agent_vlearning_mc.c, think about the modifications that are needed. Your agent will have to store values for each state; how are these values stored? How and where should the values be initialized? And how are the values updated? When should they be updated? In which function should they be updated? How does the agent keep track of the total reward?

Please note that the agent you will implement should maintain values for each state, but it does not actually change its behavior due to the values. That is, the policy does not make use of the values. This will come in a later section.

\subsubsection sec_code2_viz_values Visualizing the values.

If you have copied you learning agent from the random agent, you will see a function   agent_get_values(), which currently returns NULL. If you return a pointer to your values here, the value will be visualized by the environment, due to the following lines of code in print_step() in main.c

\code
// Print values, if the agent keeps track of them      
double* values = agent_get_values();
if (values!=NULL)
  env_print_values(values);
\endcode

So far, you haven't seen the output generated by env_print_values, because "values" was always "NULL". If you return a pointer to your values in agent_get_values, this functionality will be turned on. If you are having trouble with this, ask your supervisor. Without a visualization of the values, it will be very difficult to see if and how your agent is learning.

\subsubsection sec_code2_qvalues An agent that learns Q-Values with Monte-Carlo

Make a new agent, called agent_qlearning_mc.c (tip: copy it from agent_vlearning_mc.c, they are very similar). Implement Q-learning with Monte-Carlo methods in this agent.

The main differences with the values above is that you now have to store an Q-value for each action/state pair. How many values will you have to store for the 1D grid? What is a good way to store this information? 

As above, have agent_get_qvalues return a pointer to your table of Q-values, such that they are visualized. If you are having trouble with this, ask your supervisor. Without a visualization of the values, it will be very difficult to see if and how your agent is learning.

\subsubsection sec_code2_qvalues_td An agent that learns Q-Values with TD(0)

Copy agent_qlearning_mc.c to agent_qlearning_td.c, and implement TD(0) (formula given above) in this agent. Note that Monte-Carlo methods update values after an episode is completed, whereas TD methods update values at each step in the agent-environment loop. From which function to which will the value updating move when going from Monte-Carlo to TD learning?

\subsubsection sec_code2_epsilon An agent that does epsilon-greedy exploration

If your agent is learning Q-values well, it can use those Q-values to determine a better policy. One strategy to do so is the  so-called \f$\epsilon\f$ greedy exploration strategy, which is implemented by modifying the agent_policy() function such that it
\li Returns a random action with probability \f$\epsilon\f$ 
\li Returns the action that has the highest Q-value for the current state with probability \f$ 1-\epsilon\f$ 

If you set \f$\epsilon\f$ to 1 at the beginning of learning, the agent will return random actions, and do lots of exploration to learn a good Q-function. If you then decay \f$\epsilon\f$ to 0 over time, the agent will start \em using those Q-values to determine the best policy.

This Q-learning agent is the same one you will apply to all the other environments in this project!

\subsection sec_questions2 Questions Phase 2

Your answers, which you should include in the file answers.txt, will count for your grade.

\li Q2.1 What is a value? What is a Q-value?

\li Q2.2 What is \f$\epsilon\f$-greedy exploration? Why is it not good to always explore? Why is it not good to always exploit?

\li Q2.3 Do you need more memory to store a Value function, or a Q-function?

\li Q2.4 What is the curse of dimensionality? Why is it a curse?

\li Q2.5 Why is env_print_values() in environment.h, and not implemented as for instance agent_print_values in agent.h (difficult question!)

Once you have answered these questions, you are ready for the next phase.

*/