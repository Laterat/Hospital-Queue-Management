#ifndef UTILS_H
#define UTILS_H


int generatePatientID();
string generateUsername(const std::string& fullName);
string generatePassword(int length = 8);

// Validation functions
bool isValidName(const std::string& name);
bool isValidEthiopianPhone(const std::string& phone);

string getValidatedInput(const std::string& prompt,
                              bool (*validator)(const std::string&) = nullptr,
                              const std::string& errorMsg = "");

int getValidatedInt(const std::string& prompt, int min, int max);

#endif
