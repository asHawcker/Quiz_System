#include "player.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
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
            signUp();
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

void Player :: signIn()
{
    const string filename = "PlayerData.csv";
    ifstream fileIn(filename);

    if (!fileIn.is_open())
    {
        cout << "Failed to open the file" << endl;
        return;
    }

    string line;
    bool userFound = false;

    while (getline(fileIn,line))
    {
        stringstream ss
    }
}