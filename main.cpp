#include "Question.hpp"
#include "QuestionSet.hpp"
#include "Admin.hpp"

int main(){

    QuestionSet qSet("SET1", 20, "qdata.csv");
    
    cout<<"\n\n----------------------------"<<endl;
    qSet.show();
    try{
        cout<<removeQuestion(qSet,4)<<endl;
    }
    catch(const char* e){
        if (e=="IndexOutOfRange"){
            cout<<"Index Out Of Range."<<endl;
        }
        else if (e=="EmptySet"){
            cout<<"Empty Set"<<endl;
        }
    }
    qSet.show();
    // qSet.getQuestion(2)->display();
    // cout<<qSet.getQuestion(2)->checkAnswer();
    return 0;
}