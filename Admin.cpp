#include "Admin.hpp"

#define pin 123456

void Admin::initUser()
{
    int p;
    cout << "Enter pin: ";
    cin >> p;
    if (pin != p)
    {
        cout << "Incorrect pin";
        return;
    }
    cout << "Welcome to Quiz Game" << endl
         << "This is the admin interface" << "Choose option: " << endl
         << "1. Sign in" << endl
         << "2. Sign up" << endl
         << endl;
    int n = 0;
    while (n <= 0 && n >= 3)
    {
        cout << "Enter choice: ";
        cin >> n;
        switch (n)
        {
        case 1:
            User::signin();
            break;
        case 2:
            User::signup(0);
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
}
void Admin::setQns()
{
    
}