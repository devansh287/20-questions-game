# 20 Questions game
This problem focuses on implementing a yes/no guessing game using a binary tree. Please do not hesitate to contact me for any 
information regarding this on my email devansh@stanford.edu.

## Disclaimer
Stanford University's standard C++ libraries have been used to develop the project. I wrote the main implementation files i.e. questiontree.cpp and questiontree.h in the 20Questions/src folder.

## Detailed description (Taken from assignment instructions)
### Basics
In this problem you will implement a yes/no guessing game called "20 Questions." Each round of the game begins by you (the human player) thinking of an object. The computer will try to guess your object by asking you a series of yes-or-no questions. Eventually the computer will have asked enough questions that it thinks it knows what object you are thinking of, so it will make a final guess about what your object is. If this guess is correct, the computer wins; if not, you win. (Though the game is called "20 Questions," our game will not limit the game to a max of 20.)
### Data Structure
The computer stores its knowledge of questions and answers in a binary tree whose nodes represent the game's questions and answers. Every node's data is a string representing the text of the question or answer. A "question" node contains a left "yes" subtree and a right "no" subtree. An "answer" node is a leaf in the tree. The idea is that this tree can be traversed to ask the human player a series of questions.
### Expansion
The computer expands its question tree by one question each time it loses a game, and therefore it gets better at the game over time. Specifically, if the computer's answer guess is incorrect, you the human player must tell it a new question it can ask to help it do better in future games. The computer takes the new information from the lost game and uses it to grow its tree of questions and answers. You must replace the old incorrect answer node with a new question node that has the old incorrect answer and new correct answer as its children.
### Question Lists
The computer can save and load its tree of questions and answers from the disk so that it will retain its improvements over time, even after the program exits and reloads later. The trees are stored in the 20Questions/res folder as .txt files. The lines occur in a specific order representing a tree-like structure of questions and answers. Each question has two follow-up options that we'll call its children, which are either answer guesses or other questions to be asked. The first child of a question is its "yes" child, which comes immediately after it. The second child of a question is its "no" child, which comes immediately after the "yes" child and any of its children. The order in which the lines are stored represents a preorder traversal of the question binary tree.
