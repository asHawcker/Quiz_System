#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include "User.hpp"

using namespace std;

static string filename = "UserData.csv";

User::User(int a) : username(""), age(0), email(""), pass(""), type(a) {}

void User::signup(int x)
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

void User::signin()
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

bool User::search(const string &searchName)
{
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
