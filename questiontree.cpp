#include "questiontree.h"
#include <sstream>
#include <fstream>
#include <climits>
#include <cstring>
#include <string>
#include "strlib.h"
#include <iostream>
#include "questionnode.h"
#include "ui.h"

/*
 * Hi, I am devansh sharma!
 * This project has the entire 20 questions game
 */

//Constructor
QuestionTree::QuestionTree()
{
    root = new QuestionNode ("A:computer");
    lost = 0;
    won = 0;
}

//destrcutor
QuestionTree::~QuestionTree()
{
    //calling a helper function that frees up memory for the tree
    destructorHelper(root);
    lost = 0;
    won = 0;
}

//a recursive helper function that deletes everything in the tree
void QuestionTree::destructorHelper (QuestionNode* curr)
{
   if(curr != nullptr)
   {
    destructorHelper (curr->yes);
    destructorHelper (curr->no);
    curr = nullptr;
    delete curr;
   }

}

//counting the number of answers in a tree
int QuestionTree::countAnswers() const
{
    QuestionNode* curr = root;
    int number = 0;

    //calling a helper function that counts the answers in a parameter recursively
    countAnswersHelper(curr, number);

    return number;
}

void QuestionTree::countAnswersHelper(QuestionNode* node, int& number) const
{
    if (node != nullptr)
    {
        string line = node->data;
        //if the node begins with A, then it is an answer
        if (line[0] == 'A')
        {
            number++;
        }
        countAnswersHelper(node->yes, number);
        countAnswersHelper(node->no, number);
    }
}

//counting the number of answers in a tree
int QuestionTree::countQuestions() const
{
    QuestionNode* curr = root;
    int number = 0;

    //using a recursive helper function to count the questions of a tree in the parameter
    countQuestionsHelper(curr, number);
    return number;
}

//helper function for counting questions
void QuestionTree::countQuestionsHelper(QuestionNode* node, int& number) const
{
    if (node != nullptr)
    {
        //if the node has children, then it is a question
        if (node->yes != nullptr && node->no != nullptr) number++;
        countQuestionsHelper(node->yes, number);
        countQuestionsHelper(node->no, number);
    }
}

//returning the number of games lost
int QuestionTree::gamesLost() const
{
    int x = lost;
    return x;
}

//returning the number of games won
int QuestionTree::gamesWon() const
{
    int x = won;
    return x;
}

//function to merge the data of a new file into the existing tree
void QuestionTree::mergeData(UI& ui, istream& input)
{
    //new tree that will have the new file's questions and answers
    QuestionNode* new_tree = new QuestionNode ();

    //helper function that reads the new file into using the provided input stream
    readDataHelper(input, new_tree);

    //helper function that merges the new tree and the existing one using a question
    mergeDataHelper(ui, root, new_tree);
}

void QuestionTree::mergeDataHelper (UI& ui, QuestionNode* original, QuestionNode* new_tree)
{
    string ques = ui.readLine("Type a Y/N question to distinguish my data from your file:");
    bool ans = ui.readBoolean("And what is the answer for the new data?");

    //new question node that will connect the two files
    QuestionNode* replacement = new QuestionNode ("Q:" + ques);

    replacement->yes = new QuestionNode();
    replacement->no = new QuestionNode();

    if (ans)
    {
        replacement->yes = new_tree;
        replacement->no = original;
    }

    else
    {
        replacement->yes = original;
        replacement->no = new_tree;
    }

    //making the new question node as the root
    root = replacement;
}

//main thing - playing the game
bool QuestionTree::playGame(UI& ui)
{
    QuestionNode* curr = root;

    //helper function that does the work
    return playGameHelper(ui, curr);
}

bool QuestionTree::playGameHelper(UI& ui, QuestionNode* node)
{
    bool r = false;
    string line = node->data;

    //asking the question if the node is a question, then going to the yes or no children depending on the response
    if (line[0] == 'Q')
    {
        bool b = ui.readBoolean(line.substr(2));
        if (b)
        {
            r = playGameHelper (ui, node->yes);
        }

        else
        {
            r = playGameHelper (ui, node->no);
        }
    }

    //checking the answer if the node is an answer
    else
    {
        bool b = ui.readBoolean("Are you thinking of: " + line.substr(2) + '?');
        if (b)
        {
            won++;
            r = true;
            ui.print("Hooray, I win!");
        }
        else
        {
            lost++;
            r = false;

            //helper function that adds the new item to a node, and updates the tree if the computer loses
            node_changer(node, line, ui);
        }
    }
    return r;
}

void QuestionTree::node_changer (QuestionNode* node, string line, UI& ui)
{
    string item = ui.readLine("Drat! I lost. What was your object? ");
    string ques = ui.readLine("Type a Y/N question to distinguish " + item + " from " + line.substr(2) + ":");
    bool ans = ui.readBoolean("And what is the answer for " + item + " ?");

    //adjusting the node as per the new object and the question
    node->data = "Q:" + ques;
    node->yes = new QuestionNode ();
    node->no = new QuestionNode ();

    if (ans)
    {
        node->yes->data = "A:" + item;
        node->no->data = line;
    }

    else
    {
        node->no->data = "A:" + item;
        node->yes->data = line;
    }
}

//finding the answer range
void QuestionTree::answerRange(int& minDepth, int& maxDepth) const
{
    QuestionNode* curr = root;
    maxDepth = 0; //temporary
    minDepth = INT_MAX; //temporary

    //using a recursive helper function that uses a variable to ascertain what is the level of the
    //node being explored
    answerRangeHelper(minDepth, maxDepth, 0, curr);
}

void QuestionTree::answerRangeHelper(int& minDepth, int& maxDepth, int l, QuestionNode* node) const
{
   if (node != nullptr)
   {
       l++;
       //finding the answer's level and comparing it to the existing min and max values
       if (node->data [0] == 'A')
       {
           if (l > maxDepth) maxDepth = l;
           if (l < minDepth) minDepth = l;
       }

       answerRangeHelper(minDepth, maxDepth, l, node->yes);
       answerRangeHelper(minDepth, maxDepth, l, node->no);
   }
}

//reading the data of a file
void QuestionTree::readData(istream& input)
{
    //clearing the exisiting tree
    destructorHelper(root);
    root = new QuestionNode ();
    readDataHelper(input, root);
}

void QuestionTree::readDataHelper(istream& input, QuestionNode* node)
{
    string line;
    if (getline(input, line))
    {
        //reading the line into the node's data
        node->data = line;

        //in case the node is a question
        if (line[0] == 'Q')
        {
            node->yes = new QuestionNode ();
            node->no = new QuestionNode ();
            readDataHelper(input, node->yes);
            readDataHelper(input, node->no);
        }
    }
}

//data that writes the present tree to a file
void QuestionTree::writeData(ostream& output)
{
    QuestionNode* curr = root;
    writeDataHelper(output, curr);
}

//helper function that recurisvely does the job
void QuestionTree::writeDataHelper(ostream& output, QuestionNode* node)
{
    if (node!=nullptr)
    {
        output << node->data << endl;
        writeDataHelper(output, node->yes);
        writeDataHelper(output, node->no);
    }
}
