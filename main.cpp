#include "Question.hpp"
#include "QuestionSet.hpp"
#include "Admin.hpp"

int main(){

    QuestionSet q("1", 20, "qdata.csv");
    q.show();
    Question q1("1","newQ","ME","peacock",90);
    Question q2;
    q2=q1;
    q1.show();
    q2.show();
    AddQuestion(q,q1);
    AddQuestion(q,q1);
    AddQuestion(q,q1);
    AddQuestion(q,q1);
    AddQuestion(q,q1);
    AddQuestion(q,q1);
    cout<<"\n\n----------------------------"<<endl;
    q.show();

    return 0;
}