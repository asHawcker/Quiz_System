#include "Question.hpp"

int main(){

    
    ifstream file("qdata.csv");

        char line[1000];

        while (file.getline(line, sizeof(line)))
        {
            createQuestion(line).show();
        }

        file.close();

    return 0;
}