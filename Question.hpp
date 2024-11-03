#ifndef QUESTION
#define QUESTION
#include <iostream>
#include <fstream>
#include <cstring>
// #include "miscFunc.hpp"
using namespace std;


class Question
{

protected:
    char *setID;
    char *text;
    char *author;
    char *answer;
    int points;

public:
    Question();
    Question(const char [], const char [], const char [], const char [], int);
    Question(Question&);
    ~Question();
    int show();
    int getID();
    Question& operator=(const Question&);

};
Question createQuestion(const char *);
int stringToInt(const char* str);

#endif