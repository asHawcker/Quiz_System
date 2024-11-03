#include "Question.hpp"


int Question::show()
{
    cout << setID << " | ";
    cout << "Question: ";
    for (int i = 0; text[i] != '\0'; i++)
        cout << text[i];
    cout << endl
            << "Author: ";
    for (int i = 0; author[i] != '\0'; i++)
        cout << author[i];
    cout << endl
            << "Answer: ";
    for (int i = 0; answer[i] != '\0'; i++)
        cout << answer[i];
    cout << endl;
    cout<<"Points : "<< points;
    cout << endl;
}

int Question::getID(){
    return stringToInt(setID);
}

Question& Question::operator=(const Question& other) {
    if (this == &other)
        return *this;

    delete[] setID;
    delete[] text;
    delete[] author;
    delete[] answer;

    setID = new char[std::strlen(other.setID) + 1];
    std::strcpy(setID, other.setID);

    text = new char[std::strlen(other.text) + 1];
    std::strcpy(text, other.text);

    author = new char[std::strlen(other.author) + 1];
    std::strcpy(author, other.author);

    answer = new char[std::strlen(other.answer) + 1];
    std::strcpy(answer, other.answer);

    points = other.points;

    return *this;
}

Question createQuestion(const char *l){

    char line[1000];
    int i=0;
    for (;*(l+i) != '\0';i++) line[i] = *(l+i);
    line[i] = '\0';
    char* id;
    char* text;
    char* auth;
    char* ans;
    int pts;

    i=0;
    id = &(line[0]);
    while (line[i] != ',') i++;
    line[i] = '\0';
    
    text = &(line[++i]);
    while (line[i] != ',') i++;
    line[i] = '\0';
    
    auth = &(line[++i]);
    while (line[i] != ',') i++;
    line[i] = '\0';

    ans = &(line[++i]);
    while (line[i] != ',') i++;
    line[i] = '\0';

    pts = stringToInt(&(line[++i]));
    Question q(id,text,auth,ans,pts);

    return q;
}
