#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "User.hpp"      
#include "QuestionSet.hpp" 
#include <string>

class Player : public User 
{
private:
    int level; 
    int xp;    

public:
    Player() : User(1), level(0), xp(0) {}

    int initUser();

    void play(const QuestionSet &qset);

    void saveToCSV();

    int signIn();
    void signUp(int x);
    void display();
};

#endif