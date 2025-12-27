#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <vector>

class UserManager
{
private:
    static vector<User> users;

public:
    static void init();
    static bool authenticate(string u, string p, User &loggedUser);

    static void addUser();
    static void removeUser();
    static void listUsers();
};

#endif
