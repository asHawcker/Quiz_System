#include "QuestionSet.hpp"

QuestionSet::QuestionSet(){
    set = nullptr;
    size = 0;
    setID = -1;
    count = 0;
}
QuestionSet::QuestionSet(int id, int s){
    setID = id;
    size = s;
    set = new Question[size];
    count = 0;
}
QuestionSet::QuestionSet(const char* id, int s, const char* filename){
    setID = stringToInt(id);
    size = s;
    set = new Question[size];
    count = 0;
    ifstream file("qdata.csv");

    char line[1000];

    while (file.getline(line, sizeof(line)))
    {   
        
        if (createQuestion(line).getID() == setID){
            set[count++] = createQuestion(line);
        }
    }

    file.close();
}
QuestionSet::~QuestionSet(){
    
}