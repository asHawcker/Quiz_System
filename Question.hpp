#ifndef QUESTION
#define QUESTION
#include <iostream>
#include <fstream>
using namespace std;
class Question
{

protected:
    char *setID;
    char *text;
    char *author;
    char *answer;

public:
    Question()
    {
        text = author = answer = nullptr;
    }
    Question(const char id[], const char txt[], const char auth[], const char ans[])
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

    }
    Question(Question& q){
        Question(q.setID,q.text,q.author,q.answer);
    }
    ~Question(){
        delete [] setID;
        delete [] text;
        delete [] author;
        delete [] answer;
    }
    int show()
    {
        cout << setID << " | ";
        cout << "Question: ";
        for (int i = 0; text[i] != '\0'; i++)
            cout << text[i];
        cout << endl
             << "Author: ";
        for (int i = 0; author[i] != '\0'; i++)
            cout << author[i];
        cout << endl
             << "Answer: ";
        for (int i = 0; answer[i] != '\0'; i++)
            cout << answer[i];
        cout << endl;
    }

    
};
Question createQuestion(const char *l)
{
    char line[1000];
    int i=0;
    for (;*(l+i) != '\0';i++) line[i] = *(l+i);
    line[i] = '\0';
    char* id;
    char* text;
    char* auth;
    char* ans;

    i=0;
    id = &(line[0]);
    while (line[i] != ',') i++;
    line[i] = '\0';
    
    text = &(line[++i]);
    while (line[i] != ',') i++;
    line[i] = '\0';
    
    auth = &(line[++i]);
    while (line[i] != ',') i++;
    line[i] = '\0';

    ans = &(line[++i]);
    Question q(id,text,auth,ans);

    return q;
}

#endif