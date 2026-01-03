#include "Utils.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;
 int generatePatientID()
{
    static int id = 1000;
    return id++;
}

string generateUsername(const string& fullName)
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


string generatePassword(int length)
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


bool isValidName(const string& name)
{
    if (name.empty()) return false;
    for (char c : name)
        if (!isalpha(c) && c != ' ')
            return false;
    return true;
}

bool isValidEthiopianPhone(const string& phone)
{
    if (phone.length() != 10) return false;
    if (phone.substr(0, 2) != "09") return false;
    for (char c : phone)
        if (!isdigit(c)) return false;
    return true;
}

string getValidatedInput(
    const string& prompt,
    bool (*validator)(const string&),
    const string& errorMsg
){
    string input;
    do {
        cout << prompt;
        getline(cin, input);

        if (!validator || validator(input))
            break;

        cout << errorMsg << endl;
    } while (true);
    return input;
}

int getValidatedInt(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value >= min && value <= max)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid Age input. Enter a number between " << min << " and " << max << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


