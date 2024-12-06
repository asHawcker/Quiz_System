#include "QuestionSet.hpp"
#include <sstream>
#include <string>

QuestionSet :: QuestionSet(const string& id, size_t capacity, const string& csvFilename) 
: setID(id), size(capacity), filename(csvFilename) {
        loadFromCSV();
    }

QuestionSet :: ~QuestionSet() {
        saveToCSV();
        for (Question* q : set) {
            delete q;
        }
    }

int QuestionSet ::  getCount() const{
        return set.size();
    }

void QuestionSet :: loadFromCSV() {
        ifstream file(filename);
        if (!file.is_open()) {
            return;
        }
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            istringstream ss(line);
            string type, id, text, author, extra, xp;
            int extra2;
            getline(ss, type, ',');
            getline(ss, id, ',');
            getline(ss, text, ',');
            getline(ss, author, ',');
            getline(ss, extra, ',');
            getline(ss, xp, ',');
            ss >> extra2;
    

            Question* newQuestion = nullptr;
            if (type == "MCQ") {
                vector<string> options;
                istringstream optionStream(extra);
                string option;
                while (getline(optionStream, option, ';')) {
                    options.push_back(option);
                }
                newQuestion = new MCQQuestion(id, text, author, options, extra2, stringToInt(xp));
            }
            else if (type == "INT") {
                newQuestion = new IntegerQuestion(id, text, author, stoi(extra), stringToInt(xp));
            }
            else if (type == "TEXT") {
                newQuestion = new TextQuestion(id, text, author, extra, stringToInt(xp));
            }

            AddQuestion(*this, newQuestion);
            
        }
    }

