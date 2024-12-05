#include "Question.hpp"


Question::Question(Question& q){
    setID = q.setID;
    text = q.text;
    author = q.author;
    points = q.points;
}

