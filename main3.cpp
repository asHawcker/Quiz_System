#include"Player.hpp"
#include"QuestionSet.hpp"

int main(){

    QuestionSet q("1", 5, "qdata.csv");
    Player p;
    p.initUser();
    p.play(q);

    return 0;
}