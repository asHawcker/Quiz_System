#include "player.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>
using namespace std;

int Player :: initUser()
{
    int n=0;
    int loggedin = 0;

    while (1)
    {
        cout << "Welcome to Quiz Game"<<endl
        << "Choose option: " << endl
        << "1. Sign in" << endl
        << "2. Sign up" << endl
        << "3. Back to Main Menu" << endl;

        cout << "Enter choice: ";
        cin >> n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Please Enter a valid integer input." << endl;
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
                cout << "Invalid choice." << endl;
        }
    }
}

void Player :: display()
{
    cout << "Name: " << username << endl;
    cout << "Age: " << age << endl;
    cout << "Email: " << email << endl;
    cout << "Level: " << level << endl;
    cout << "XP: " << xp << endl;
}

void Player:: play(const QuestionSet &qset)
{
    int currentscore = 0; // score of the current quiz
    for (int i=0;i<qset.getCount();i++)
    {
        cout<<"\nQuestion"<< "(" << i+1 <<"/" <<qset.getCount() << ")" << endl
            << qset.getQuestion(i).getText()<<endl;

        cout<<"Enter Answer :";
        string answer;
        if (i==0)
        {
            cin.ignore();
        }
        getline(cin,answer);
        if (answer == qset.getQuestion(i).getAnswer())
        {
            cout<<"Correct Answer"<<endl;
            xp += qset.getQuestion(i).getXP();
            currentscore += qset.getQuestion(i).getXP();
        }

        else
        {
            cout << "Your answer is wrong" << endl 
                 << "Correct answer is : " << qset.getQuestion(i).getAnswer();
        }

    }
    level = xp/100;
    cout << "\n\nQuiz Completed." << endl << "Your Score is : " <<currentscore <<endl;
    saveToCSV();
}

void Player :: saveToCSV()
{
    try
    {
        const string filename = "PlayerData.csv";
        ifstream fileIn(filename);
        ofstream fileOut("temp.csv");

        if (!fileIn.is_open() || !fileOut.is_open())
        {
            throw runtime_error("Faled to open PlayerData.csv");
        }

        string line;
        bool userFound = false;

        // Check each line to see if the current player's data already exists
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

        // If the player was not found, add their info as a new entry
        if (!userFound) {
            fileOut << username << "," << age << "," << email << "," << pass << "," 
                    << type << "," << level << "," << xp << "\n";
        }

        // Close files
        fileIn.close();
        fileOut.close();

        // Replace the original file with the updated temp file
        if(remove(filename.c_str())!=0 || rename("temp.csv", filename.c_str())!=0)
        {
            throw runtime_error("Failed to update CSV file");
        }

        // cout << "Player information saved successfully." << endl;
        
    }

    catch (const runtime_error &e)
    {
        cerr << "A runtime error occured while handling PlayerData.csv" << endl << e.what() << endl;
        exit(0);
    }


    catch(const exception& e)
    {
        std::cerr <<"An exception occured while handling PlayerData.csv" << endl << e.what() << endl;
        exit(0);
    }

    catch (...)
    {
        cerr << "An unknown error has occured while saving the player information"<< endl;
        exit(0);
    }
}

void Player :: signUp(int x)
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
            cout << "Enter username: ";
            cin>> username;
            if (search(username))
                cout << "Username already in use. Please try another name.\n";
            else
                break;
        }

        cout << "Enter your age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter your email: ";
        cin>>email;

        cout << "Enter your password: ";
        cin >> pass;

        type = 1;
        level = xp = 0;
        file << username << "," << age << "," << email << "," << pass << "," << type << "," << level << "," << xp << "\n";
        file.close();

        cout << "Information saved successfully.\n"
            << endl;
    }

    catch (const runtime_error &e)
    {
        cerr << "A Runtime error has occured while handling PlayerData.csv" << e.what() << endl;
        exit(0);
    }
    
    catch (...)
    {
        cerr << "An unknown error has occured while handling PlayerData.csv"<<endl;
        exit(0);
    }
}

int Player :: signIn()
{
    string InputUsername, InputPassword;
    cout << "Enter username : ";
    cin >> InputUsername;
    cout << "Enter password : ";
    cin >> InputPassword;

    bool userFound = false;

    ifstream file("PlayerData.csv");

    if (!file.is_open())
    {
        cerr << "Failed to open the file PlayerData.csv." << endl;
        return -1;//file Not Found
    }

    try
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string fileUsername, filePassword, fileAge, fileEmail, fileType, fileLevel, fileXP;
            
            getline(ss,fileUsername,',');
            getline(ss,fileAge,',');
            getline(ss,fileEmail,',');
            getline(ss,filePassword, ',');
            getline(ss,fileType,',');
            getline(ss,fileLevel,',');
            getline(ss,fileXP,',');

            if (InputUsername == fileUsername)
            {
                userFound = true;

                if(InputPassword == filePassword)
                {
                    username = fileUsername;
                    age = stoi(fileAge);
                    email = fileEmail;
                    pass = filePassword;
                    type = stoi(fileType);
                    level = stoi(fileLevel);
                    xp = stoi(fileXP);
                    cout << "Logged in successfully." << endl;
                    return 1;
                }

                else{
                    cout << "Wrong password. Please try again." << endl;
                }
                file.close();
                return 0;
                break;
            } 
            
        }
        file.close();
        if(!userFound)
        {
            cout << "Username not found"<<endl;
            return 0;
        }
    }
    catch(const exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(0);
    }

    return 0;
}