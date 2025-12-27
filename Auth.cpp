#include "Auth.h"
#include "UserManager.h"
#include <iostream>
using namespace std;

bool login(User &user)
{
    string u, p;
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    return UserManager::authenticate(u, p, user);
}
