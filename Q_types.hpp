#include "Question.hpp"

class MCQQuestion : public Question
{
private:
    vector<string> options;
    int correctOptionIndex;

public:
    MCQQuestion(const string &id, const string &questionText,const string &author,const vector<string> &mcqOptions, int correctIndex, int xp = 10): Question(id, questionText, author, xp), options(mcqOptions), correctOptionIndex(correctIndex) {}

    void display() const
    {
        cout << "Question: " << text << endl;
        for (size_t i = 0; i < options.size(); ++i)
        {
            cout<<i+1<<". "<<options[i] << endl;
        }
    }

    bool checkAnswer() const
    {
        int userAnswer;
        cout << "Enter your answer (1-" << options.size() << "): ";
        cin >> userAnswer;
        return userAnswer - 1 == correctOptionIndex;
    }

    string serialize() const
    {
        string optionsStr;
        for (size_t i = 0; i < options.size(); ++i)
        {
            optionsStr += options[i];
            if (i < options.size() - 1)
                optionsStr += ";";
        }
        return "MCQ," + setID + "," + text + "," + author + "," +optionsStr + "," + to_string(points)+","+to_string(correctOptionIndex);
    }
};



class IntegerQuestion : public Question{
private:
    int correctAnswer;
public:
    IntegerQuestion(const string& id, const string& questionText,const string& author, int correct, int xp = 10): Question(id, questionText, author, xp), correctAnswer(correct) {}

    void display() const{
        cout << "Question: " << text << endl;
    }
    bool checkAnswer() const{
        int userAnswer;
        cin >> userAnswer;
        return userAnswer == correctAnswer;
    }
    string serialize() const{
        return "INT," + setID + "," + text + "," + author + "," + to_string(correctAnswer) + "," + to_string(points)+",0";
    }
};


class TextQuestion : public Question {
private:
    string correctAnswer;

public:
    TextQuestion(const string& id, const string& questionText,const string& author, const string& correct, int xp = 10): Question(id, questionText, author, xp), correctAnswer(correct) {}

    void display() const{
        cout << "Question: " << text << endl;
    }

    bool checkAnswer() const{
        string userAnswer;
        getline(cin, userAnswer);
        return userAnswer == correctAnswer;
    }
    string serialize() const{
        return "TEXT," + setID + "," + text + "," + author +"," +correctAnswer + "," +to_string(points);
    }
};