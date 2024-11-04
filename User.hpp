#include <iostream>
using namespace std;

class User
{
protected:

    string username;
    int age;
    string email;
    string pass;
    int type;   //1 for player  0 for admin

public:
    User(int a=1);
    void signup(int x=0);
    void signin();
    bool extractUserInfo(const string& line);
    bool search(const string& searchName);
    bool checkPass(const string &p) const;
    
    friend istream &operator>>(istream &in,User &u);
    friend ostream &operator<<(ostream &out,const User &u);

};