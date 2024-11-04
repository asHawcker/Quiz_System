#include"User.hpp"

class Admin : public User
{
private:
    int qnos;

public:
    Admin();
    void initUser();
    void setQns();

};