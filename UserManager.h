#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"

class UserManager
{
private:
    struct UserNode
    {
        User data;
        UserNode *next;
        UserNode(const User &u) : data(u), next(nullptr) {}
    };

    static UserNode *head; // start of linked list

public:
   

    static UserManager::UserNode* findUserByUsername(const string& uname);
    static void appendUser(const User& u);

    static void init();
    static bool authenticate(const std::string &u, const std::string &p, User &loggedUser);
    static void addUser(const User& currentUser);
    static void removeUser(const User& currentUser);
    static void listUsers(const User& currentUser);
    static void updateOwnProfile(User &loggedUser);
    static void resetUserCredentials();
};

#endif
