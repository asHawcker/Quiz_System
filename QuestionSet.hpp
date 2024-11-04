#ifndef QUE_SET
#define QUE_SET
#include "Question.hpp"

class QuestionSet{
private:
    int setID;
    Question* set;
    int count; // current no. of questions in set
    int size; // Total capacity of questions in set
public:
    QuestionSet();
    QuestionSet(int, int);
    QuestionSet(const char*, int, const char*);
    ~QuestionSet();
    int show();
    int getCount(){
        return count;
    }
    Question getQuestion(int x){
        return set[x%count];
    }
};
int AddQuestion();

#endif