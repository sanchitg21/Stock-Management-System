#ifndef Users_H
#define Users_H
#include <string>
class User
{
public:
    int id;
    std::string name;
    std::string mobilenum;
    User *left;
    User *right;
    User(int x, std::string a, std::string b);
    User();
};
#endif
