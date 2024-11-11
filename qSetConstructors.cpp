#include "QuestionSet.hpp"
#include <sstream>
#include <string>
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
QuestionSet::QuestionSet(const char setID[], int s, const char filename[]) {
    this->setID = stringToInt(setID);
    this->size = s;
    this->count = 0;
    set = new Question[size];  // Allocate memory for Question array

    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;  // Skip empty lines

        // Check if array capacity is reached
        if (count >= size) {
            std::cerr << "Reached maximum capacity of question set." << std::endl;
            break;
        }

        // Create a Question object from the line and add to the set
        this->set[count++] = createQuestion(line.c_str());
    }

    file.close();
}
QuestionSet::~QuestionSet() {
    std::ofstream file("qdata.csv", std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: qdata.csv" << std::endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        Question temp = set[i];
        file << temp.getID() << ","
             << temp.getText() << ","
             << temp.getAuthor() << ","
             << temp.getAnswer() << ","
             << temp.getXP() << "\n";
    }

    file.close();
    delete[] set; 
}
