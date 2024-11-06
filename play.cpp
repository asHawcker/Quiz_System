#include "player.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>
using namespace std;
void Player :: initUser()
{
    cout << "Player Interface"<<endl
         << "Choose option: " << endl
         << "1. Sign in" << endl
         << "2. Sign up" << endl
         << endl;

    int n=0;
    while (n <= 0 && n >= 3)
    {
        cout << "Enter choice: ";
        cin >> n;
        switch (n)
        {
        case 1:
            signIn();
            break;
        case 2:
            cout << "Enter usernname : ";
            cin >> username;
            cout << "Enter password : ";
            cin >> pass;
            cout << "Enter email : ";
            cin >> email;
            cout << "Enter age : ";
            cin >> age;
            type = 1;
            level = 0;
            xp = 0;
            signUp(0);
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
}

void Player:: play(const QuestionSet &qset)
{
    int currentscore = 0; // score of the current quiz
    for (int i=0;i<qset.getCount();i++)
    {
        cout<<"Question"<< "(" << i<<"/" <<qset.getCount() << ")" << endl
            << qset.getQuestion(i).getText()<<endl;

        cout<<"Enter Answer : ";
        string answer;
        cin>>answer;

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
    level = xp%100;
    cout << "Quiz Completed" << endl << "Your Score is : " <<currentscore <<endl;
    saveToCSV();
}

void Player :: saveToCSV()
{
    const string filename = "PlayerData.csv";
    ifstream fileIn(filename);
    ofstream fileOut("temp.csv");

    if (!fileIn.is_open() || !fileOut.is_open()) 
    {
        cout << "Failed to open the file" << endl;
        return;
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
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());

    cout << "Player information saved successfully." << endl;
}

void Player :: signUp(int x)
{
    string filename;

    if (type == 0)
        filename = "AdminData.csv";
    else if (type == 1)
        filename = "PlayerData.csv";

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

    type = 1;
    level = xp = 0;
    file << username << "," << age << "," << email << "," << pass << "," << type << "," << level << "," << xp << "\n";
    file.close();

    cout << "Information saved successfully.\n"
         << endl;
}

void Player :: signIn()
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
        cout << "Failed to open the file." << endl;
        return;
    }

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
                break;
            }

            else{
                cout << "Wrong password. Please try again." << endl;
            }

            break;
        } 

        if(!userFound)
        {
            cout << "USername not found"<<endl;
        }

        file.close();
    }

}