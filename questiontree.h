// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#ifndef _questiontree_h
#define _questiontree_h

#include <sstream>
#include <fstream>
#include <climits>
#include <cstring>
#include <string>
#include "strlib.h"
#include <iostream>
#include "questionnode.h"
#include "ui.h"
using namespace std;

class QuestionTree {
public:
    QuestionTree();
    ~QuestionTree();
    void answerRange(int& minDepth, int& maxDepth) const;
    int countAnswers() const;
    int countQuestions() const;
    int gamesLost() const;
    int gamesWon() const;
    void mergeData(UI& ui, istream& input);
    bool playGame(UI& ui);
    void readData(istream& input);
    void writeData(ostream& output);

private:
    QuestionNode* root;
    void readDataHelper(istream& input, QuestionNode* node);
    void countAnswersHelper(QuestionNode* node, int& number) const;
    void countQuestionsHelper(QuestionNode* node, int& number) const;
    bool playGameHelper(UI& ui, QuestionNode* node);
    void node_changer (QuestionNode* node, string line, UI& ui);
    void writeDataHelper (ostream& output, QuestionNode* node);
    void mergeDataHelper (UI& ui, QuestionNode* original, QuestionNode* new_tree);
    void destructorHelper (QuestionNode* curr);
    void answerRangeHelper(int& minDepth, int& maxDepth, int l, QuestionNode* node) const;
    int lost;
    int won;

};

#endif // _questiontree_h
