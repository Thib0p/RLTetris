// Doxygen page for Phase 1
/*!

\page phase1 Phase 1: Reinforcement Learning foundations and understanding the code

\section sec_phase1 Phase 1: Reinforcement Learning foundations and understanding the code

\b Aims: Understand the basic principles of reinforcement learning. Understand how the provided code implements the general structure of a reinforcement learning problem, so that you can extend it with new agents and environments.

This phase has by far the most text: it forms the foundation for the C code you will write in Phase 2 and beyond.

\subsection phase1_rl Reinforcement Learning: Foundations

Many problems, from games such as backgammon and chess to autonomous robot manipulation, are so complex that it is difficult to specify by hand what the best action is for every possible state. However, even non-roboticists and novice backgammon players know whether a particular state is good (The robot grasped the cup! I won the game!) or bad (The robot dropped the cup... I lost...). 

The field of artificial intelligence concerned with learning the best actions from only feedback about the quality of actions and states is know as ``reinforcement learning'' (RL). This in contrast to ``supervised learning'', in which the output (e.g. an action) for each input (e.g. a state) is known, or ``unsupervised learning'', in which there are only inputs.


The basic reinforcement learning agent-environment interface are depicted in the figure below. The agent makes an state of the environment and executes an action. The environment gets the action, updates the state of the environment, and returns a reward to the agent.

\image html  code_overview_01_RL_small.png "Agent-environment interface for reinforcement learning problems."
\image latex code_overview_01_RL.png "Agent-environment interface for reinforcement learning problems." height=5cm

We explain the basic concepts in reinforcement learning using a very simple environment, which is also provided to you as C code. The world is a 1D grid, i.e. an array, in which the agent can move left or right. For every movement, the agent receives a penalty of -1. The left cell in the grid is the \em terminal \em state; if the agent arrives here it has completed the task, and receives a 'reward' of 100. Below is an example of how the state changes, depending on the actions of the agent.

\verbatim
 Before       Action   Reward        After
 01234567                            01234567

|T....A..| == RIGHT == (R=  -1) ==> |T.....A.|   (agent moves right, receives -1 penalty)

|T....A..| ==  LEFT == (R=  -1) ==> |T...A...|   (agent moves left, receives -1 penalty)

|TA......| ==  LEFT == (R= 100) ==> |A.......|   (agent moves to terminal state, receives 100 reward)
\endverbatim

\subsubsection sec_mdp Markov Decision Processes

RL problems are often modelled as a "Markov Decision Process" (MDP). An MDP consists of the following components:

\li A \b state \b space \f$S\f$, e.g. the 8 discrete positions of the agent in the 1D grid.
\li An \b action \b space \f$A\f$, e.g. the actions [LEFT,RIGHT] of the agent in the 1D grid.
\li A \b transition \b function \f$T: S\times A \rightarrow S\f$, which specifies the subsequent state that results from applying an action in a state. For instance, doing `LEFT' in state `3' will take the agent to state `2'.
\li A \b reward \b function \f$R: S\times A \rightarrow R\f$: the reward of performing a certain action in a certain state. For the grid, this is always -1, unless the agent moves into the terminal state, for which it receives 100.

\subsubsection sec_rl_concepts Policy, Episodes, Model-free

Apart from the basic "Markov Decision Process" formulation of reinforcement learning, the following RL concepts will be important for this project

\li An agent's \b policy maps states to actions \f$\pi: S \rightarrow A\f$. It determines which action the agent performs in which state. 
\li In this project, we consider \b episodic reinforcement learning. This means that there is at least one terminal state. If the agent ends up in the terminal state, the current episode ends, and a new episode starts. 
\li Finally, we will consider only \b model-free reinforcement learning methods, where the agent does not know anything about the environment in which it acts (i.e. does not know about the transition function and reward function); the agent must determine what to do \em only from interactions with the environment

The main question that RL addresses is: Which actions should the agent take, such that the agent optimizes the expected reward it will get? The policy that determines these best actions is the "optimal policy", and written as \f$\pi^*\f$
For our 1D grid example, it is very easy to specify \f$\pi^*\f$: always go left towards the terminal state. However, for more complex problems, the optimal policy \f$\pi^*\f$ can be extremely difficult to find. RL algorithms aim at determining \f$\pi^*\f$ from trial-and-error interaction with the world.

\subsection sec_code_overview Implementation in C: Overview of the provided code

Before continuing with this phase, please download the initial C source code for Phase 1 of this project from the project website. Unpack the tgz archive with: <tt>tar xzvf phase1_initial_code.tgz</tt>.
The README.txt explains how to compile the first program, and how to generate the doxygen documentation.

So how is the basic reinforcement learning problem structure implemented in the source code we provide?

\subsubsection Agent-Environment Interface

The main loop for the agent-environment interface is implemented as follows (for the full version, see run_episode()):

\code
while (!terminal) // Continue till episode is done (a terminal state is reached)
{
  // Update environment state, and get the reward and next state
  state  = env_step(p_env, action, &reward, &terminal);    
  
  // Get the next action for this state 
  action = agent_step(p_agent, env, reward,state);
}
\endcode

To make it obvious in the code what is being communicated between the environment and the agent, the  following typedefs are introduced in rl.h:\n
<tt>typedef unsigned int ::action_t;</tt>\n
<tt>typedef unsigned long long int ::state_t;</tt>\n
<tt>typedef double ::reward_t;</tt>

The p_env and p_agent are pointers to structures that contain all the relevant information about the environment and the agents. The env_step() and agent_step() functions modify the content of these structures.

\subsubsection sec_agent_declaration Agent Declaration

The agent's job is to provide an action for a given state, which is declared in the function agent_step()  in the header file agent.h. Note that the agent also receives a reward in this function. This is the reward of performing the \em previous action in the \em previous state of the environment.\n
<tt>::action_t agent_step(agent_t *p_agent, reward_t reward, state_t state);</tt>

\subsubsection sec_environment_declaration Environment Declaration

Similarly, the environment takes the action of the agent, and updates the state of the environment, which is declared in the function env_step() in the header file environment.h. This function returns the state of the updated state (as a return parameter), as well as the reward for executing the action in the state (through a pass by pointer) and whether the resulting state is a terminal state (through a pass by pointer).\n
<tt>::state_t env_step(env_t* p_env, action_t action, reward_t reward, int* terminal);</tt>

Including our header files in the RL overview yields the following:

\image html  code_overview_02_RL_headers_small.png
\image latex code_overview_02_RL_headers.png "" height=5cm

Including the main RL loop in the overview yields the image below. The main loop specificies how states, actions and rewards are passed between the agent and the environment, and thus implements the agent-environment interface.
Note how main.c encapsulates the two (blue) header files in the image, because it \#includes them. 

\image html  code_overview_03_main_small.png
\image latex code_overview_03_main.png "" height=6cm


\subsubsection sec_declaration_vs_definition Declarations vs. Definitions

Although the agent.h header file \b declares \em what an agent should do, it do not \b define \em how the agent actually does it. This what/how is a very important distinction in the C and C++ languages!
Whereas declarations (what) are usually put in the .h header files, the .c source files contain the definitions (how). Thus, the declaration of the function

\code
// Declaration: says what to do, but doesn't actually implement (define) how
action_t agent_policy(agent_t* p_agent, state_t state);
// No code here! We don't know how this function is implemented here.
\endcode

is done in the agent.h header file, whereas one of the definitions of this function can be found in the agent_random.c source file

\code
// Definition: says how to do what the declaration above says it should do
action_t agent_step(agent_t* p_agent, state_t state)  
{
  // Here is the code that actually does something
  return rand()%p_agent->n_actions; // Return a random action  
}
\endcode

Note that a pointer to a structure (p_agent) is passed as an argument; this contains all relevant information about the agent, in this case the number of actions the agent can perform p_agent->n_actions.


The same goes for the environment. The declarations (\em what does an environment do?) are in environment.h, whereas environment_grid1D.c actually defines \em how a 1-dimensional grid environment does \em what a 1D grid environment should do. This is shown to the left in the image below.

\image html  code_overview_sourcesall_small.png
\image latex code_overview_sourcesall.png "" height=6cm

The `trick' in this project will be that you will implement several agents by defining different implementations of for instance agent_step() in different agent_<name>.c source files, and different implementations of for instance environment_step in different environment_<name>.c source files, see the image above (right).

When exchanging these source files, the declarations in agent.h and environment.h always stays the same! This means that we can easily run all our environments with all our agents. For instance, if we want to run the random agent on the 1-dimensional grid world (code for both is provided), you compile as follows (please try this compilation, and run the program):

\code
gcc -Wall -g environments/environment_grid1D.c    agents/agent_random.c main.c -o rl_grid1D_random 
\endcode

Later, if you wrote a new very smart agent and a beautiful environment, you could try the different agents with the different environments by compiling as follows.

\code
gcc -Wall -g environments/environment_grid1D.c    agents/agent_random.c main.c -o rl_grid1D_random 
gcc -Wall -g environments/environment_grid1D.c    agents/agent_smart.c  main.c -o rl_grid1D_smart 
gcc -Wall -g environments/environment_beautiful.c agents/agent_random.c main.c -o rl_beautiful_random 
gcc -Wall -g environments/environment_beautiful.c agents/agent_smart.c  main.c -o rl_beautiful_smart 
\endcode

Thus, we have executables that use different agents and different environments, just by compiling different source files that have different definitions for the \em same declarations in the header files.

For convenience, all functions declarations in agent.h start with the prefix "agent_". That way, it is easy to recognize whether the definitions in a .c file, e.g. agent_random.c, are implementations of declarations in agent.h, or somewhere else. The same goes for environment.c and the "env_" prefix. 

If this is not 100% clear, please ask your supervisor for further explanation, because understanding  the different between declarations and definitions is fundamental to achieving the aims of this project. <a href="http://www.gamedev.net/page/resources/_/technical/general-programming/organizing-code-files-in-c-and-c-r1798">This article</a> also describes the difference nicely, and also motivates why the separation of header and source files is helpful.

\subsubsection sec_opaque_pointers Opaque Pointers

We use one more "design pattern" in the code: opaque pointers. In agent.h you will find the typedef:\n
<tt>typedef struct agent_impl_t agent_t;</tt>

The agent_t structure should contain all those things relevant to the agent's state. This may be, for instance, its values or the number of actions it can perform. Then, the function declarations operate on a pointer to agent_t, for instance\n
<tt>action_t agent_step(agent_t* p_agent, reward_t reward, state_t state);</tt>\n
These functions access the information \em inside the agent strucure. For instance, it may update the values stored in the agent structure.

The trick now is that we do \em not specify in the header file what is actually in the agent_impl_t structure (just like we didn't specify what was going on inside the functions in the header file). This is done in the .c file. For instance, in agent_random.c you will find.

\code
struct agent_impl_t {
  unsigned int n_actions; // How many possible actions can this agent perform?
};
\endcode

Thus, for the random agent, the agent_impl_t structure only contains information about the number of actions an agent can perform. For the agents you will write, it will contain more information.
Because of <tt>typedef struct agent_impl_t agent_t;</tt> the same information is stored in agent_t, but... this information is not known in the header file, or any file that includes the header file. In summary, only agent_random.c knows about what is actually implemented in the agent structure, and no file that should not have access to this information can access it. For instance, we can ensure that the environment does not have access to the agent, or vice versa. This is know as \em encapsulation.

\subsection sec_questions1 Questions Phase 1

Your answers, which you should include in the file answers.txt, will count for your grade.

\li Q1.1: What is a policy? What is the optimal policy?

\li Q1.2: What is an episode? When does an episode end?

\li Q1.3: Describe chess as a Markov Decision Process, i.e. what is the state space, action space, transition function and reward function (there are many ways to model chess as an MDP; just provide one). Do you know the optimal policy for chess?

\li Q1.4: Run the program "rl_grid1D_random", and describe what you see in terms of states, actions, terminal states and episodes. If the output of the program does not make it clear, inspect the relevant .c files. 

\li Q1.5: Make a new agent that, instead of performing random actions, always goes left. Suggestion:
\code
cp agents/agent_random.c agents/agent_left.c

# Edit agents/agent_left.c so that it always returns the LEFT (=0) action.

gcc -Wall -g environments/environment_grid1D.c agents/agent_left.c main.c -o rl_grid1D_left
\endcode
When running agent_random and agent_left, what differences do you see in the total rewards the agents receive for an episode? Who is doing better? What total reward would you expect to get for each of the states for agent_random and agent_left? (Understanding these questions and thinking about the answers will be fundamental to Phase 2)

\li Q1.6 What is the difference between a function declaration and an function definition?

\li Q1.7 Does a header file contain declarations or definitions?

Once you have answered these questions, you are ready for the next phase.

*/
