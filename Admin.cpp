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

void addQuestionToSet(QuestionSet &questionSet, string);

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
        std::cerr << "\033[1;31mFailed to open the file.\033[0m" << std::endl;
        return;
    }

    while (x == 0)
    {
        std::cout << "\033[1;33mEnter username: \033[0m";
        getline(cin, username);
        if (search(username))
            std::cout << "\033[1;31mUsername already in use. Please try another name.\033[0m\n";
        else
            break;
    }

    std::cout << "\033[1;33mEnter your age: \033[0m";
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    std::cout << "\033[1;33mEnter your email: \033[0m";
    getline(cin, email);

    std::cout << "\033[1;33mEnter your password: \033[0m";
    cin >> pass;

    file << username << "," << age << "," << email << "," << pass << "," << type << "\n";
    file.close();

    std::cout << "\033[1;32mInformation saved successfully.\033[0m\n" << std::endl;
}

void Admin::signin()
{
    string searchName;
    std::cout << "\033[1;33mEnter your UserName: \033[0m";
    cin >> searchName;

    if (!search(searchName))
    {
        std::cout << "\033[1;31mUser with the name '" << searchName << "' not found.\033[0m\n"
                  << std::endl;
    }
}

void Admin::AdminInterface()
{
    while (1)
    {
        int n;
        string setID;
        std::cout << "\033[1;34m\tAdmin\033[0m" << std::endl
                  << "Select option: " << std::endl
                  << "1. Show Questions" << std::endl
                  << "2. Add Question" << std::endl
                  << "3. Remove Question" << std::endl
                  << "4. Add new Admin" << std::endl
                  << "5. Create new Question Set" << std::endl
                  << "6. See account details" << std::endl
                  << "0. Back" << std::endl;
        cin >> n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid Input. Please Enter a valid integer input.\033[0m" << std::endl;
        }
        else if (n == 1)
        {
            std::cout << "\033[1;33mEnter set ID: \033[0m" << std::endl;
            cin >> setID;
            setID = "SET" + setID;
            QuestionSet q(setID, 100, setID + ".csv");
            q.show();
            cin.ignore();
        }
        else if (n == 2)
        {
            std::cout << "\033[1;33mEnter set ID: \033[0m" << std::endl;
            cin >> setID;
            setID = "SET" + setID;
            QuestionSet q(setID, 100, setID + ".csv");

            addQuestionToSet(q, username);
        }
        else if (n == 3)
        {
            while (1)
            {
                int choice;
                std::cout << "\033[1;34m\tRemove Question\033[0m" << std::endl;
                std::cout << "Select option: " << std::endl
                          << "1. Show questions" << std::endl
                          << "2. Remove Question" << std::endl
                          << "3. Back" << std::endl;
                cin >> choice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    std::cout << "\033[1;31mInvalid Input. Please Enter a valid integer input.\033[0m" << std::endl;
                    continue;
                }

                if (choice == 1)
                {
                    std::cout << "\033[1;33mEnter set ID: \033[0m" << std::endl;
                    cin >> setID;
                    setID = "SET" + setID;
                    QuestionSet q(setID, 100, setID + ".csv");
                    q.show();
                }
                else if (choice == 2)
                {
                    std::cout << "\033[1;33mEnter set ID: \033[0m" << std::endl;
                    cin >> setID;
                    setID = "SET" + setID;
                    QuestionSet q(setID, 100, setID + ".csv");
                    q.show();
                    int qno;
                    std::cout << "\033[1;33mEnter question number: \033[0m";
                    cin >> qno;
                    try
                    {
                        removeQuestion(q, qno);
                    }
                    catch (const char *e)
                    {
                        if (e == "IndexOutOfRange")
                        {
                            std::cout << "\033[1;31mIndex Out Of Range.\033[0m" << std::endl;
                        }
                        else if (e == "EmptySet")
                        {
                            std::cout << "\033[1;31mEmpty Set\033[0m" << std::endl;
                        }
                    }
                }
                else if (choice == 3)
                {
                    break; // Break out of the inner loop to return to main menu
                }
                else
                {
                    std::cout << "\033[1;31mInvalid choice\033[0m" << std::endl;
                }
            }
        }
        else if (n == 4)
        {
            Admin a1;
            cin.ignore();
            a1.signup();
        }
        else if (n == 5)
        {
            try
            {
                string setID;
                std::cout << "\033[1;33mEnter set ID: \033[0m" << std::endl;
                cin >> setID;
                setID = "SET" + setID;
                ifstream file(setID + ".csv");

                if (file.good())
                {
                    throw("FileExists");
                }
                else
                {
                    ofstream file1(setID + ".csv");
                    std::cout << "\033[1;32mCreated a new Question set csv file..\033[0m\n";
                    cin.ignore();
                }
            }
            catch (const char *e)
            {
                std::cout << "\033[1;31mError: \033[0m" << e;
            }
            catch (...)
            {
                std::cerr << "\033[1;31mAn error occurred while processing the file.\033[0m" << std::endl;
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
            std::cout << "\033[1;31mInvalid choice\033[0m" << std::endl;
        }
        std::cout << std::endl;
        cin.ignore();
    }
}

void Admin::Userlogin()
{
    int p;
    std::cout << "\033[1;33mEnter pin: \033[0m";
    cin >> p;
    if (pin != p)
    {
        std::cout << "\033[1;31mIncorrect pin\033[0m" << std::endl;
        return;
    }

    int n = 0, a = 0;
    while (1)
    {
        std::cout << "\033[1;34m\tWelcome to Quiz Game\033[0m" << std::endl
                  << "This is the admin interface" << std::endl
                  << "Choose option: " << std::endl
                  << "1. Sign in" << std::endl
                  << "2. Sign up" << std::endl
                  << "3. Back" << std::endl
                  << std::endl;
        std::cout << "\033[1;33mEnter choice: \033[0m";
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
            std::cout << "\033[1;31mInvalid choice.\033[0m" << std::endl;
        }
        if (a)
            AdminInterface();
        std::cout << std::endl;
    }
}

istream &operator>>(istream &in, User &u)
{
    std::cout << "\033[1;33mEnter username: \033[0m";
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

    out << "\033[1;34mUsername: \033[0m" << u.username << std::endl
        << "\033[1;34mAge: \033[0m" << u.age << std::endl
        << "\033[1;34mE-Mail: \033[0m" << u.email << std::endl
        << "\033[1;34mPassword: \033[0m*********" << std::endl
        << "\033[1;34mAccount type: \033[0m" << acctype << std::endl;
    return out;
}

void addQuestionToSet(QuestionSet &questionSet, string author)
{
    string questionType;
    std::cout << "\033[1;33mEnter question type (MCQ/INT/TEXT): \033[0m";
    cin >> questionType;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string id, text;
    int xp;
    std::cout << "\033[1;33mEnter question ID: \033[0m";
    getline(cin, id);
    std::cout << "\033[1;33mEnter question text: \033[0m";
    getline(cin, text);

    std::cout << "\033[1;33mEnter XP for the question: \033[0m";
    cin >> xp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Question *newQuestion = nullptr;

    if (questionType == "MCQ")
    {
        vector<string> options;
        int correctOption;

        std::cout << "\033[1;33mEnter MCQ options (separate by semicolon): \033[0m";
        string optionsInput;
        getline(cin, optionsInput);

        istringstream ss(optionsInput);
        string option;
        while (getline(ss, option, ';'))
        {
            options.push_back(option);
        }
        std::cout << "\033[1;33mEnter the correct option number (0-based index): \033[0m";
        cin >> correctOption;

        newQuestion = new MCQQuestion(id, text, author, options, correctOption, xp);
    }
    else if (questionType == "INT")
    {
        int answer;
        std::cout << "\033[1;33mEnter the correct integer answer: \033[0m";
        cin >> answer;

        newQuestion = new IntegerQuestion(id, text, author, answer, xp);
    }
    else if (questionType == "TEXT")
    {
        string answer;
        std::cout << "\033[1;33mEnter the correct text answer: \033[0m";
        getline(cin, answer);

        newQuestion = new TextQuestion(id, text, author, answer, xp);
    }
    else
    {
        std::cout << "\033[1;31mInvalid question type!\033[0m" << std::endl;
        return;
    }

    try
    {
        AddQuestion(questionSet, newQuestion);
        std::cout << "\033[1;32mQuestion added successfully!\033[0m" << std::endl;
    }
    catch (const char *errorMsg)
    {
        std::cout << "\033[1;31mError adding question: \033[0m" << errorMsg << std::endl;
        delete newQuestion;
    }
}
