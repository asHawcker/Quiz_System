#include "User.hpp"

class Admin : public User
{
private:
    int qnos;

public:
    Admin();
    void AdminInterface();
    void Userlogin();
};