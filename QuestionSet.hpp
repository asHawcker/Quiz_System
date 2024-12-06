#ifndef QUE_SET
#define QUE_SET
#include "Question.hpp"
#include "Q_types.hpp"
#include <sstream>
#include <string>

class QuestionSet{

friend int AddQuestion(QuestionSet& qSet, Question* q);
friend int removeQuestion(QuestionSet& qSet, int qNumber);

private:
    string setID;
    string filename;
    vector<Question*> set;
    int size; // Total capacity of questions in set
public:
    QuestionSet(int, int);
    QuestionSet(const string& id, size_t capacity, const string& csvFilename);
    ~QuestionSet();
    int show();
    int getCount() const;
    Question* getQuestion(int x) const;

    void loadFromCSV();

    // Save questions to CSV
    void saveToCSV() const;
};

#endif