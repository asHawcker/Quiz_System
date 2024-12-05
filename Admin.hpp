#include "User.hpp"

class Admin : public User
{
private:
    int qnos;

public:
    Admin();
    void signup(int x=0);
    void signin();
    void AdminInterface();
    void Userlogin();

    friend istream &operator>>(istream &in, User &u);
    friend ostream &operator<<(ostream &out, const User &u);
};