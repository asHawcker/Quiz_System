#include "Admin.hpp"
#include "Player.hpp"
#include <stdlib.h>
#include <limits>

void admin()
{
    Admin a;
    a.Userlogin();
}

void player()
{
    int n = 0;
    Player p;
    int x =p.initUser();
    if(x==0)
    {
        return;
    }
    while (1)
    {
        cout << "Quiz Game Menu" << endl;
        cout << "1. Play quiz:" << endl;
        cout << "2. See player details" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
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
            {   string setID;
                cout << "Enter set ID: " << endl;
                cin >> setID;
                setID = "SET" + setID;
                cout << setID;
                QuestionSet q(setID, 100, setID + ".csv"); // add filename when different question sets are stored in different ids
                p.play(q);
                break;
            }
            case 2:
                p.display();
                cin.ignore();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice." << endl;
        }
        cin.ignore();
    }
}

int main()
{
    int n;
    while (1)
    {
       // cout << "\033[2J\033[H";

        cout << "Select choice:" << endl
             << "1. Player" << endl
             << "2. Admin" << endl
             << "3. Exit" << endl
             << endl
             << "Enter you choice" << endl;
        cin >> n;

        switch (n)
        {
        case 1:
            player();
            break;
        case 2:
            admin();
            break;
        case 3:
            //cout << "\033[2J\033[H";
            exit(1);
        default:
            cout << "Invalid choice" << endl;
        }
        cout << endl;
    }

    return 0;
}