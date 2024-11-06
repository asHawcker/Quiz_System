#ifndef QUE_SET
#define QUE_SET
#include "Question.hpp"

class QuestionSet{
friend int AddQuestion(QuestionSet& qSet,Question& q){
    if (qSet.count >= qSet.size) return 0; //returns 0 if addition is not possible
    if (q.getID() != qSet.setID) return -1; // returns -1 if there is a mismatch in qSet.setID and q.setID
    qSet.set[qSet.count++] = q;
}
friend int removeQuestion(QuestionSet& qSet, int qNumber){
    if (qSet.count == 0) return 0; // Empty question set
    if (qNumber>qSet.count) return -1; // qNumber out of range
    qSet.count--;
    for (int i=qNumber-1; i<qSet.count;i++){
        qSet.set[i] = qSet.set[i+1];
    }

}
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
    int getCount() const{
        return count;
    }
    Question getQuestion(int x) const{
        if (x<count) return set[x];
        else return set[x%count];
    }
};


#endif