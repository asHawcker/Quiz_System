#include "Admin.hpp"
#include "QuestionSet.hpp"
#include "Question.hpp"
#define pin 123456

Admin::Admin() : User(0)
{
    qnos = 0;
}

void Admin::AdminInterface()
{
    while (1)
    {
        int n;
        char setID[10];
        cout << "\033[2J\033[H";

        cout << "\tAdmin" << endl
             << "Select option: " << endl
             << "1. Add Question" << endl
             << "2. Remove Question" << endl
             << "3. Add new Admin" << endl
             << "4. See account details" << endl
             << "5. Back" << endl;
        cin >> n;
        if (n == 1)
        {
            cout << "Enter set ID: " << endl;
            cin >> setID;
            QuestionSet q(setID, 10, "qdata.csv");
            char qn[50], ans[50];
            int pts;
            cin.ignore();
            cout << "Enter question: ";
            cin.getline(qn, 50);
            cout << "Enter answer: ";
            cin.getline(ans, 50);
            cout << "Enter points: ";
            cin >> pts;
            Question q1((const char *)setID, (const char *)qn, username.c_str(), (const char *)ans, pts);
            q1.show();
            cout << AddQuestion(q, q1);
        }
        else if (n == 2)
        {
        }
        else if (n == 3)
        {
            Admin a1;
            a1.signup();
        }
        else if (n == 4)
        {

            printdetails();
        }
        else if (n == 5)
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