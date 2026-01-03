#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <ctime>
#include <random>
#include <algorithm>

inline int generatePatientID()
{
    static int id = 1000;
    return id++;
}

inline string generateUsername(const string& fullName)
{
    string username;
    size_t spacePos = fullName.find(' ');
    if(spacePos != string::npos)
        username = string(1, tolower(fullName[0])) + fullName.substr(spacePos + 1);
    else
        username = fullName;

    // Remove spaces
    username.erase(remove(username.begin(), username.end(), ' '), username.end());

    // Add 3 random digits
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100, 999);
    username += to_string(dis(gen));

    return username;
}


inline string generatePassword(int length = 8)
{
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                         "abcdefghijklmnopqrstuvwxyz"
                         "0123456789";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, chars.size() - 1);

    string password;
    for(int i = 0; i < length; ++i)
        password += chars[dis(gen)];

    return password;
}

#endif
