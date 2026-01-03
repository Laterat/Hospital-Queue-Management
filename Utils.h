#ifndef UTILS_H
#define UTILS_H

#include <string>

int generatePatientID();
std::string generateUsername(const std::string& fullName, const std::string& phone);
std::string generatePassword(int length = 8);

// Validation functions
bool isValidName(const std::string& name);
bool isValidEthiopianPhone(const std::string& phone);

std::string getValidatedInput(
    const std::string& prompt,
    bool (*validator)(const std::string&) = nullptr,
    const std::string& errorMsg = ""
);
int getValidatedInt(const std::string& prompt, int min, int max);

#endif
