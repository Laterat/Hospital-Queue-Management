#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

enum Role
{
    ADMIN,
    RECEPTIONIST,
    DOCTOR
};

struct User
{
    string username;
    string password;
    Role role;
};

#endif
