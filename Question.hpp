#ifndef QUESTION
#define QUESTION
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
// #include "miscFunc.hpp"
using namespace std;


class Question
{

protected:
    string setID;
    string text;
    string author;
    int points;

public:
    Question(const string &id, const string &questionText, const string &questionAuthor, int xp = 0):setID(id), text(questionText), author(questionAuthor), points(xp) {}
    Question(Question&);
    virtual ~Question() = default;
    virtual void display() const = 0;
    virtual bool checkAnswer() const{};
    virtual string serialize() const = 0;

    int getID();
    Question& operator=(const Question&);
    int getXP(){return points;}
    string getText(){
        return text;
    }
    string getAuthor(){
        return author;
    }
};
int stringToInt(const string& str);






#endif