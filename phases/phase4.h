// Doxygen page for Phase 4
/*!
\page phase4 Phase 4: Adding external code (for plotting learning curves and a GUI)

\section sec_phase4 Phase 4: Adding external code

\b Aim: Learn how to incorporate external code into your own source code.

\subsection sec_rl4 Reinforcement Learning: Learning curves

Your agent is learning? Great! But how well is it at doing so? Does it learn fast? Or slow?
One way to analyze these questions is to inspect the "learning curve", which is a graphical representation in which the performance of the agent is plotted against the amount of experience it has had. 

\image html learning_curves.png "Examples of learning curves." 
\image latex learning_curves.pdf "Examples of learning curves." height=5cm

In episodic reinforcement learning, the amount of experience is often measured in terms of how many episodes the agent has observed, and the performance is measured as the total reward it receives during an episode. If your agent is learning, the total reward should increase as the number of observed episodes increases. If an agent learns well, the total reward should increase quickly as the experience grows; this is called a \em short learning curve. 


Learning curves may also be used to compare environments: with the same learning agent, more difficult tasks have \em longer learning curves. For some further insights, and a discussion of the editor VI in the context of learning curves, see <a href="http://en.wikipedia.org/wiki/Learning_curve#In_culture">http://en.wikipedia.org/wiki/Learning_curve#In_culture</a>.

\subsection sec_code4 Implementation in C: Including code from outside

\subsubsection sec_code4_lc External code for plotting learning curves

Download the C source code for storing and plotting learning curves from the project website. Unpack the tgz archive with: <tt>tar xzvf phase4_learning_curves.tgz</tt>.
The files are self-documenting, because the header file has doxygen comments. 

Include this code, such that it stores the total rewards acquired during an episode in a file. 
Where should you initialize the file? Where should you add the total reward to the file? Where should you close the file. At the end of your main() function, plot the results with the learning_curve_plot() function.

\subsubsection sec_code4_gui External code for visualizing the environment 

Download the C source code for visualizing the environment in a Graphical User Interface (GUI) from the project website. Unpack the tgz archive with: <tt>tar xzvf phase4_gui.tgz</tt>. The README_GUI.txt file in this archive explains how to compile this GUI with your code. 

\subsection sec_questions4 Questions Phase 4

Your answers, which you should include in the file answers.txt, will count for your grade.

\li Q4.1 What is a learning curve?

\li Q4.2 How many files did you have to modify to include the learning curve code? Without a modular approach, i.e. when every combination of agents and environments would need its own main.c file, how many files would you have had to modify?

Once you have answered these questions, you are ready for the next phase.

*/
