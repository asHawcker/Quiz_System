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

    void initUser();

    void play(const QuestionSet &qset);

    void saveToCSV();

    void signIn();
    void signUp(int x);
};

#endif