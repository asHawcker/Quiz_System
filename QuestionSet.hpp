#ifndef QUE_SET
#define QUE_SET
#include "Question.hpp"

class QuestionSet{
private:
    int setID;
    Question* set;
    int size;
public:
    QuestionSet(){
        set = nullptr;
        size = 0;
        setID = -1;
    }
    QuestionSet(int id, int c){
        setID = id;
        size = c;
        set = new Question[size];
    }
    ~QuestionSet(){
        
    }
    

};


#endif