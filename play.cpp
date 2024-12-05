#include "player.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>
using namespace std;

int Player :: initUser()
{
    int n = 0;
    int loggedin = 0;

    while (1)
    {
        cout << "\033[1;34mWelcome to Quiz Game\033[0m" << endl
             << "\033[1;33mChoose option: \033[0m" << endl
             << "\033[1;32m1. Sign in\033[0m" << endl
             << "\033[1;36m2. Sign up\033[0m" << endl
             << "\033[1;31m3. Back to Main Menu\033[0m" << endl;

        cout << "\033[1;37mEnter choice: \033[0m";
        cin >> n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31mInvalid Input. Please Enter a valid integer input.\033[0m" << endl;
        }

        switch (n)
        {
        case 1:
        {
            loggedin = signIn();
            if (loggedin == 1)
            {
                return 1;
            }
            break;
        }
        case 2:
        {
            signUp(0);
            break;
        }
        case 3:
        {
            return 0;
            break;
        }
        default:
            cout << "\033[1;31mInvalid choice.\033[0m" << endl;
        }
    }
}

void Player ::display()
{
    cout << "\033[1;34mName: \033[0m" << username << endl;
    cout << "\033[1;34mAge: \033[0m" << age << endl;
    cout << "\033[1;34mEmail: \033[0m" << email << endl;
    cout << "\033[1;34mLevel: \033[0m" << level << endl;
    cout << "\033[1;34mXP: \033[0m" << xp << endl;
}

void Player::play(const QuestionSet &qset)
{
    int currentscore = 0; // score of the current quiz
    for (int i = 0; i < qset.getCount(); i++)
    {
        cout << "\033[1;36m\nQuestion"
             << "(" << i + 1 << "/" << qset.getCount() << ")\033[0m" << endl;

        qset.getQuestion(i)->display();
        
        if (qset.getQuestion(i)->checkAnswer())
        {
            cout << "\033[1;32mCorrect Answer\033[0m" << endl;
            xp += qset.getQuestion(i)->getXP();
            currentscore += qset.getQuestion(i)->getXP();
        }

        else
        {
            cout << "\033[1;31mYour answer is wrong\033[0m" << endl;
        }
        cin.ignore();
    }
    level = xp / 100;
    cout << "\n\n\033[1;32mQuiz Completed.\033[0m" << endl
         << "\033[1;33mYour Score is : " << currentscore << "\033[0m" << endl;
    saveToCSV();
}

void Player ::saveToCSV()
{
    try
    {
        const string filename = "PlayerData.csv";
        ifstream fileIn(filename);
        ofstream fileOut("temp.csv");

        if (!fileIn.is_open() || !fileOut.is_open())
        {
            throw runtime_error("Failed to open PlayerData.csv");
        }

        string line;
        bool userFound = false;

        while (getline(fileIn, line))
        {
            stringstream ss(line);
            string existingUsername;
            getline(ss, existingUsername, ',');

            if (existingUsername == username)
            {
                fileOut << username << "," << age << "," << email << "," << pass << ","
                        << type << "," << level << "," << xp << "\n";
                userFound = true;
            }

            else
            {
                fileOut << line << "\n";
            }
        }

        if (!userFound)
        {
            fileOut << username << "," << age << "," << email << "," << pass << ","
                    << type << "," << level << "," << xp << "\n";
        }

        fileIn.close();
        fileOut.close();

        if (remove(filename.c_str()) != 0 || rename("temp.csv", filename.c_str()) != 0)
        {
            throw runtime_error("Failed to update CSV file");
        }
    }

    catch (const runtime_error &e)
    {
        cerr << "\033[1;31mA runtime error occurred while handling PlayerData.csv\033[0m" << endl
             << e.what() << endl;
        exit(0);
    }

    catch (const exception &e)
    {
        std::cerr << "\033[1;31mAn exception occurred while handling PlayerData.csv\033[0m" << endl
                  << e.what() << endl;
        exit(0);
    }

    catch (...)
    {
        cerr << "\033[1;31mAn unknown error has occurred while saving the player information\033[0m" << endl;
        exit(0);
    }
}

void Player ::signUp(int x)
{
    string filename;
    filename = "PlayerData.csv";

    try
    {
        ofstream file;
        file.open(filename, ios::app);
        if (!file.is_open())
        {
            throw runtime_error("Failed to open PlayerData.csv");
        }

        while (x == 0)
        {
            cout << "\033[1;37mEnter username: \033[0m";
            cin >> username;
            if (search(username))
                cout << "\033[1;31mUsername already in use. Please try another name.\033[0m\n";
            else
                break;
        }

        cout << "\033[1;37mEnter your age: \033[0m";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\033[1;37mEnter your email: \033[0m";
        cin >> email;

        cout << "\033[1;37mEnter your password: \033[0m";
        cin >> pass;

        type = 1;
        level = xp = 0;
        file << username << "," << age << "," << email << "," << pass << "," << type << "," << level << "," << xp << "\n";
        file.close();

        cout << "\033[1;32mInformation saved successfully.\033[0m\n"
             << endl;
    }

    catch (const runtime_error &e)
    {
        cerr << "\033[1;31mA Runtime error has occurred while handling PlayerData.csv\033[0m" << e.what() << endl;
        exit(0);
    }

    catch (...)
    {
        cerr << "\033[1;31mAn unknown error has occurred while handling PlayerData.csv\033[0m" << endl;
        exit(0);
    }
}

int Player ::signIn()
{
    string InputUsername, InputPassword;
    cout << "\033[1;37mEnter username : \033[0m";
    cin >> InputUsername;
    cout << "\033[1;37mEnter password : \033[0m";
    cin >> InputPassword;

    bool userFound = false;

    ifstream file("PlayerData.csv");

    if (!file.is_open())
    {
        cerr << "\033[1;31mFailed to open the file PlayerData.csv.\033[0m" << endl;
        return -1;
    }

    try
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string fileUsername, filePassword, fileAge, fileEmail, fileType, fileLevel, fileXP;

            getline(ss, fileUsername, ',');
            getline(ss, fileAge, ',');
            getline(ss, fileEmail, ',');
            getline(ss, filePassword, ',');
            getline(ss, fileType, ',');
            getline(ss, fileLevel, ',');
            getline(ss, fileXP, ',');

            if (InputUsername == fileUsername)
            {
                userFound = true;

                if (InputPassword == filePassword)
                {
                    username = fileUsername;
                    age = stoi(fileAge);
                    email = fileEmail;
                    pass = filePassword;
                    type = stoi(fileType);
                    level = stoi(fileLevel);
                    xp = stoi(fileXP);
                    cout << "\033[1;32mLogged in successfully.\033[0m" << endl;
                    return 1;
                }

                else
                {
                    cout << "\033[1;31mIncorrect Password.\033[0m" << endl;
                    return 0;
                }
            }
        }

        if (!userFound)
        {
            cout << "\033[1;31mIncorrect Username.\033[0m" << endl;
            return 0;
        }
    }
    catch (...)
    {
        cerr << "\033[1;31mAn error occurred while processing the file.\033[0m" << endl;
        return -1;
    }

    return 0;
}
