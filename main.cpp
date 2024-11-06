#include "Question.hpp"
#include "QuestionSet.hpp"
#include "Admin.hpp"

int main(){

    QuestionSet q("1", 5, "qdata.csv");
    q.show();
    Question q1("1","newQ","ME","peacock",90);
    AddQuestion(q,q1);
    cout<<"\n\n----------------------------"<<endl;
    q.show();

    return 0;
}