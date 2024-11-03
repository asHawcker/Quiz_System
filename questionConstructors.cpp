#include "Question.hpp"

Question::Question()
{
    text = author = answer = nullptr;
}

Question::Question(const char id[], const char txt[], const char auth[], const char ans[], int pts)
{
    
    int temp = 0;
    for (int i = 0; txt[i] != '\0'; i++)
        temp++;
    text = new char[temp + 1];
    for (int i = 0; i < temp + 1; i++)
        text[i] = txt[i];

    temp = 0;
    for (int i = 0; auth[i] != '\0'; i++)
        temp++;
    author = new char[temp + 1];
    for (int i = 0; i < temp + 1; i++)
        author[i] = auth[i];

    temp = 0;
    for (int i = 0; ans[i] != '\0'; i++)
        temp++;
    answer = new char[temp + 1];
    for (int i = 0; i < temp + 1; i++)
        answer[i] = ans[i];
    
    temp = 0;
    for (int i = 0; id[i] != '\0'; i++)
        temp++;
    setID = new char[temp + 1];
    for (int i = 0; i < temp + 1; i++)
        setID[i] = id[i];
    
    points = pts;

}

Question::Question(Question& q){
    Question(q.setID,q.text,q.author,q.answer,q.points);
}

Question::~Question(){
    delete [] setID;
    delete [] text;
    delete [] author;
    delete [] answer;
}
