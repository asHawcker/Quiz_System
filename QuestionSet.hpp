#ifndef QUE_SET
#define QUE_SET
#include "Question.hpp"

class QuestionSet{
private:
    int setID;
    Question* set;
    int count; // current no. of questions in set
    int size; // Total capacity of questions in set
public:
    QuestionSet(){
        set = nullptr;
        size = 0;
        setID = -1;
        count = 0;
    }
    QuestionSet(int id, int s){
        setID = id;
        size = s;
        set = new Question[size];
        count = 0;
    }
    QuestionSet(const char* id, int s, const char* filename){
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
    ~QuestionSet(){
        
    }
    int show(){
        for (int i=0;i<count;i++){
            set[i].show();
        }
        return 0;
    }

};


#endif