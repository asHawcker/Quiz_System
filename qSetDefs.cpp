#include "QuestionSet.hpp"

int QuestionSet::show(){
    for (size_t i = 0; i < set.size(); ++i) {
            cout << "Question " << i + 1 << ": ";
            set[i]->display();
            cout << endl;
        }
    return 0;
}

int AddQuestion(QuestionSet& qSet, Question* q) {
    if (qSet.set.size() >= qSet.size) throw("MaxLimitReached");    
    qSet.set.push_back(q);
    return 1;
}

int removeQuestion(QuestionSet& qSet, int qNumber) {
    if (qSet.set.empty()) throw("EmptySet");
    if (qNumber <= 0 || qNumber > static_cast<int>(qSet.set.size())){
        throw("IndexOutOfRange");
        return -1;
    }   
    delete qSet.set[qNumber - 1];
    qSet.set.erase(qSet.set.begin() + qNumber - 1);
    return 1;
}
Question* QuestionSet :: getQuestion(int x) const{
        if (x<set.size()) return set[x];
        else return set[x%set.size()];
    }

void QuestionSet :: saveToCSV() const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file for writing: " + filename);
        }
        for (const auto& q : set) {
            string serialized = q->serialize();
            file << serialized << endl;
            
        }
    }