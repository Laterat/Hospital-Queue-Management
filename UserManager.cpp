#include "UserManager.h"
#include <iostream>
using namespace std;

vector<User> UserManager::users;

void UserManager::init()
{
    users.push_back({"admin", "admin123", ADMIN});
}

bool UserManager::authenticate(string u, string p, User &loggedUser)
{
    for (auto &user : users)
    {
        if (user.username == u && user.password == p)
        {
            loggedUser = user;
            return true;
        }
    }
    return false;
}

void UserManager::addUser()
{
    User u;
    int r;
    cout << "Username: ";
    cin >> u.username;
    cout << "Password: ";
    cin >> u.password;
    cout << "Role (1=Receptionist, 2=Doctor): ";
    cin >> r;

    u.role = (r == 1) ? RECEPTIONIST : DOCTOR;
    users.push_back(u);
    cout << "Staff user added.\n";
}

void UserManager::removeUser()
{
    string uname;
    cout << "Enter username to remove: ";
    cin >> uname;

    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if (it->username == uname)
        {
            users.erase(it);
            cout << "User removed.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

void UserManager::listUsers()
{
    cout << "\n--- Staff Accounts ---\n";
    for (auto &u : users)
    {
        cout << u.username << " - ";
        if (u.role == ADMIN)
            cout << "Admin\n";
        else if (u.role == DOCTOR)
            cout << "Doctor\n";
        else
            cout << "Receptionist\n";
    }
}
