#include "Question.hpp"


int Question::getID(){
    return stringToInt(setID);
}

Question& Question::operator=(const Question& other) {
    if (this == &other)
        return *this;

    setID=other.setID;
    text=other.text;
    author=other.author;
    points = other.points;

    return *this;
}

