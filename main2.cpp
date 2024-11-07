#include "Admin.hpp"
#include "Player.hpp"
#include <stdlib.h>

void player()
{
}

void admin()
{
    Admin a;
    a.Userlogin();
}

void player()
{
    Player p;
    p.initUser();
}

int main()
{
    int n;
    while (1)
    {
        cout << "\033[2J\033[H";

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
            cout << "\033[2J\033[H";
            exit(1);
        default:
            cout << "Invalid choice" << endl;
        }
        cout << endl;
    }

    return 0;
}