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

static string filename="AdminData.csv";

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
        //cout << "\033[2J\033[H";

        cout << "\tAdmin" << endl
             << "Select option: " << endl
             << "1. Show Questions" << endl
             << "2. Add Question" << endl
             << "3. Remove Question" << endl
             << "4. Add new Admin" << endl
             << "5. See account details" << endl
             << "6. Back" << endl;
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
            QuestionSet q(setID, 100, "qdata.csv");
            q.show();
        }

        else if (n == 2)
        {
            cout << "Enter set ID: " << endl;
            cin >> setID;
            if (!(setID == "1" || setID == "2" || setID == "3" || setID == "4" || setID == "5")) throw("SetNotFound");
            setID = "SET"+setID;
            cout <<setID;
            QuestionSet q(setID, 100, setID+".csv");

            cout<<"Enter question type: \n";
            int temp_c;
            

            string qn, ans;
            int pts;
            cin.ignore();
            cout << "Enter question: ";
            cin>>qn;
            cout << "Enter answer: ";
            cin>>ans;
            cout << "Enter points: ";
            cin >> pts;
            Question q1(setID, (const char *)qn, username.c_str(), (const char *)ans, pts);
            q1.show();
            AddQuestion(q, new );
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
                        QuestionSet q(setID, 100, "qdata.csv");
                        q.show();
                    }
                    else if (choice == 2)
                    {
                        int qno;
                        cout << "Enter question number: ";
                        cin >> qno;
                        QuestionSet q(setID, 100, "qdata.csv");
                        removeQuestion(q, qno);
                    }
                    else if (choice == 3)
                    {
                        break;  // Break out of the inner loop to return to main menu
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
            a1.signup();
        }
        else if (n == 5)
        {

            printdetails();
        }
        else if (n == 6)
        {
            return;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
        cout << endl;
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
