#ifndef QUE_SET
#define QUE_SET
#include "Question.hpp"
#include "Q_types.hpp"
#include <sstream>
#include <string>

class QuestionSet{

friend int AddQuestion(QuestionSet& qSet, Question* q) {
    if (qSet.set.size() >= qSet.size) throw("MaxLimitReached");    
    qSet.set.push_back(q);
    return 1;
}

friend int removeQuestion(QuestionSet& qSet, int qNumber) {
    if (qSet.set.empty()) throw("EmptySet");
    if (qNumber <= 0 || qNumber > static_cast<int>(qSet.set.size())){
        throw("IndexOutOfRange");
        return -1;
    }   
    delete qSet.set[qNumber - 1];
    qSet.set.erase(qSet.set.begin() + qNumber - 1);
    return 1;
}
private:
    string setID;
    string filename;
    vector<Question*> set;
    int size; // Total capacity of questions in set
public:
    QuestionSet(int, int);
    QuestionSet(const string& id, size_t capacity, const string& csvFilename) 
        : setID(id), size(capacity), filename(csvFilename) {
        loadFromCSV();
    }
    ~QuestionSet() {
        saveToCSV();
        for (Question* q : set) {
            delete q;
        }
    }
    int show();
    int getCount() const{
        return set.size();
    }
    Question* getQuestion(int x) const{
        if (x<set.size()) return set[x];
        else return set[x%set.size()];
    }

    void loadFromCSV() {
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

    // Save questions to CSV
    void saveToCSV() const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file for writing: " + filename);
        }
        for (const auto& q : set) {
            string serialized = q->serialize();
            file << serialized << endl;
            
        }
    }

};


#endif