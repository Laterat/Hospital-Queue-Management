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
    string fullName;
    int age;
    string location;
    string phoneNumber;
    time_t registrationDate;
    Role role;
};

// Convert Role enum to readable string
inline string roleToString(Role r)
{
    switch (r)
    {
        case ADMIN: return "ADMIN";
        case RECEPTIONIST: return "RECEPTIONIST";
        case DOCTOR: return "DOCTOR";
        default: return "UNKNOWN";
    }
}

#endif
