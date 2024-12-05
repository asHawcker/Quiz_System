#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include "Admin.hpp"
#include "QuestionSet.hpp"
#include "Question.hpp"
#include <limits>
#define pin 123456

void addQuestionToSet(QuestionSet &questionSet,string);

static string filename = "AdminData.csv";

Admin::Admin() : User(0)
{
    qnos = 0;
}

void Admin::signup(int x)
{
    ofstream file;
    file.open(filename, ios::app);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return;
    }

    while (x == 0)
    {
        cout << "Enter username: ";
        getline(cin, username);
        if (search(username))
            cout << "Username already in use. Please try another name.\n";
        else
            break;
    }

    cout << "Enter your age: ";
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your password: ";
    cin >> pass;

    file << username << "," << age << "," << email << "," << pass << "," << type << "\n";
    file.close();

    cout << "Information saved successfully.\n"
         << endl;
}

void Admin::signin()
{
    string searchName;
    cout << "Enter your UserName: ";
    cin >> searchName;

    if (!search(searchName))
    {
        cout << "User with the name '" << searchName << "' not found.\n"
             << endl;
    }
}

void Admin::AdminInterface()
{
    while (1)
    {
        int n;
        string setID;
        // cout << "\033[2J\033[H";

        cout << "\tAdmin" << endl
             << "Select option: " << endl
             << "1. Show Questions" << endl
             << "2. Add Question" << endl
             << "3. Remove Question" << endl
             << "4. Add new Admin" << endl
             << "5. Create new Question Set"<<endl
             << "6. See account details" << endl
             << "0. Back" << endl;
        cin >> n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Please Enter a valid integer input." << endl;
        }

        else if (n == 1)
        {
            cout << "Enter set ID: " << endl;
            cin >> setID;
            setID = "SET" + setID;
            cout << setID;
            QuestionSet q(setID, 100, setID + ".csv");
            q.show();
            cin.ignore();
        }

        else if (n == 2)
        {
            cout << "Enter set ID: " << endl;
            cin >> setID;
            setID = "SET" + setID;
            cout << setID;
            QuestionSet q(setID, 100, setID + ".csv");

            addQuestionToSet(q,username);
        }
        else if (n == 3)
        {
            while (1)
            {
                int choice;
                cout << "\tRemove Question" << endl;
                cout << "Select option: " << endl
                     << "1. Show questions" << endl
                     << "2. Remove Question" << endl
                     << "3. Back" << endl;
                cin >> choice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Input. Please Enter a valid integer input." << endl;
                    continue;
                }

                if (choice == 1)
                {   
                    cout << "Enter set ID: " << endl;
                    cin >> setID;
                    setID = "SET" + setID;
                    cout << setID;
                    QuestionSet q(setID, 100, setID+".csv");
                    q.show();
                }
                else if (choice == 2)
                {   
                    cout << "Enter set ID: " << endl;
                    cin >> setID;
                    setID = "SET" + setID;
                    cout << setID;
                    QuestionSet q(setID, 100, setID+".csv");
                    q.show();
                    int qno;
                    cout << "Enter question number: ";
                    cin >> qno;
                    try{
                        removeQuestion(q,qno);
                    }
                    catch(const char* e){
                        if (e=="IndexOutOfRange"){
                            cout<<"Index Out Of Range."<<endl;
                        }
                        else if (e=="EmptySet"){
                            cout<<"Empty Set"<<endl;
                        }
                    }
                }
                else if (choice == 3)
                {
                    break; // Break out of the inner loop to return to main menu
                }
                else
                {
                    cout << "Invalid choice" << endl;
                }
            }
        }
        else if (n == 4)
        {
            Admin a1;
            cin.ignore();
            a1.signup();
        }
        else if (n==5){
            try{
            string setID;
            cout << "Enter set ID: " << endl;
            cin >> setID;
            setID = "SET" + setID;
            ifstream file(setID+".csv");
            
                if (file.good()){
                    throw("FileExists");
                }else{  
                    ofstream file1(setID+".csv");
                    cout << "\033[32mCreated a new Question set csv file..\033[0m\n";
                    cin.ignore();
                }
            } catch(const char* e){
                std::cout<<"Error : "<<e;
            } catch(...){
                cerr << "\033[1;31mAn error occurred while processing the file.\033[0m" << endl;
            }
        }
        else if (n == 6)
        {

            printdetails();
            cin.ignore();
        }
        else if (n == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
        cout << endl;
        cin.ignore();
    }
}

void Admin::Userlogin()
{
    int p;
    cout << "Enter pin: ";
    cin >> p;
    if (pin != p)
    {
        cout << "Incorrect pin";
        return;
    }

    int n = 0, a = 0;
    while (1)
    {
        // cout << "\033[2J\033[H";

        cout << "\tWelcome to Quiz Game" << endl
             << "This is the admin interface" << endl
             << "Choose option: " << endl
             << "1. Sign in" << endl
             << "2. Sign up" << endl
             << "3. Back" << endl
             << endl;
        cout << "Enter choice: ";
        cin >> n;
        switch (n)
        {
        case 1:
            a = User::signin();
            break;
        case 2:
            User::signup();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice." << endl;
        }
        if (a)
            AdminInterface();
        cout << endl;
    }
}

istream &operator>>(istream &in, User &u)
{
    cout << "Enter username: ";
    getline(in, u.username);
    if (u.search(u.username))
    {
        u.signin();
    }
    else
    {
        u.signup(1);
    }
    return in;
}

ostream &operator<<(ostream &out, const User &u)
{
    string acctype;

    if (u.type == 0)
        acctype = "Admin";
    else if (u.type == 1)
        acctype = "Player";
    else
        acctype = "Unknown";

    out << "Username: " << u.username << endl
        << "Age: " << u.age << endl
        << "E-Mail: " << u.email << endl
        << "Password: *********" << endl
        << "Account type: " << acctype << endl;
    return out;
}

void addQuestionToSet(QuestionSet &questionSet,string author)
{
    string questionType;
    cout << "Enter question type (MCQ/INT/TEXT): ";
    cin >> questionType;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string id, text;
    int xp;
    cout << "Enter question ID: ";
    getline(cin, id);
    cout << "Enter question text: ";
    getline(cin, text);

    cout << "Enter XP for the question: ";
    cin >> xp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Question *newQuestion = nullptr;
    if (questionType == "MCQ")
    {
        vector<string> options;
        int correctOption;

        cout << "Enter MCQ options (separate by semicolon): ";
        string optionsInput;
        getline(cin, optionsInput);

        istringstream ss(optionsInput);
        string option;
        while (getline(ss, option, ';'))
        {
            options.push_back(option);
        }
        cout << "Enter the correct option number (0-based index): ";
        cin >> correctOption;

        newQuestion = new MCQQuestion(id, text, author, options, correctOption, xp);
    }
    else if (questionType == "INT")
    {
        int answer;
        cout << "Enter the correct integer answer: ";
        cin >> answer;

        newQuestion = new IntegerQuestion(id, text, author, answer, xp);
    }
    else if (questionType == "TEXT")
    {
        string answer;
        cout << "Enter the correct text answer: ";
        getline(cin, answer);

        newQuestion = new TextQuestion(id, text, author, answer, xp);
    }
    else
    {
        cout << "Invalid question type!" << endl;
        return;
    }

    try
    {
        AddQuestion(questionSet, newQuestion);
        cout << "Question added successfully!" << endl;
    }
    catch (const char *errorMsg)
    {
        cout << "Error adding question: " << errorMsg << endl;
        delete newQuestion;
    }
}