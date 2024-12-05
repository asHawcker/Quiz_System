#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include "User.hpp"

using namespace std;

User::User(int a) : username(""), age(0), email(""), pass(""), type(a) {}

void User::signup(int x)
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
        cin >> username;
        if (search(username))
        {
            cout << "Username already in use.\n";
            return;
        }
        else
            break;
    }

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your email: ";
    cin >> email;

    cout << "Enter your password: ";
    cin >> pass;

    file << username << "," << age << "," << email << "," << pass << "," << type << "\n";
    file.close();

    cout << "Information saved successfully.\n"
         << endl;
}

int User::signin()
{
    string searchName, pw;
    cout << "Enter your UserName: ";
    cin >> searchName;

    if (!search(searchName))
    {
        cout << "User with the name '" << searchName << "' not found.\n"
             << endl;
        return 0;
    }
    cout << "Enter password: ";
    cin >> pw;

    if (pw != pass)
    {
        cout << "Incorrect password" << endl;
        return 0;
    }
    cout << "Signed in to your account" << endl;
    return 1;
}

bool User::search(const string &searchName)
{
    string filename;

    if (type == 0)
        filename = "AdminData.csv";
    else if (type == 1)
        filename = "PlayerData.csv";

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        size_t pos = line.find(',');
        if (pos != string::npos)
        {
            string name = line.substr(0, pos);
            if (name == searchName)
            {
                file.close();
                return extractUserInfo(line);
            }
        }
    }

    file.close();
    return false;
}

bool User::extractUserInfo(const string &line)
{
    string ageStr, typeStr;

    stringstream ss(line);
    if (!getline(ss, username, ','))
        return false;
    if (!getline(ss, ageStr, ','))
        return false;
    if (!getline(ss, email, ','))
        return false;
    if (!getline(ss, pass, ','))
        return false;
    if (!getline(ss, typeStr, ','))
        return false;

    try
    {
        age = stoi(ageStr);
        type = stoi(typeStr);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: Required data: age/type is not a valid integer." << endl;
        return false;
    }

    return true;
}

bool User::checkPass(const string &p) const
{
    return pass == p;
}

void User::printdetails()
{
    cout << "Username: " << username << endl
         << "Age: " << age << endl
         << "E-Mail: " << email << endl
         << "Password: *********" << endl;
}

