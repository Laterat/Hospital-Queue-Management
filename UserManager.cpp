#include "UserManager.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

// Initialize head
UserManager::UserNode* UserManager::head = nullptr;


// ----------------------
// --- Helper Functions ---

bool confirmAction(const std::string& msg)
{
    char confirm;
    while (true) // repeat until valid input
    {
        std::cout << msg << " (y/n): ";
        std::cin >> confirm;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (confirm == 'y' || confirm == 'Y')
            return true;
        else if (confirm == 'n' || confirm == 'N')
            return false;
        else
            std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
    }
}

string getUpdatedField(
    const string& fieldName,
    const string& currentValue,
    bool (*validator)(const string&) = nullptr
)
{
    while (true)
    {
        cout << fieldName << " [" << currentValue << "] (Press ENTER to skip): ";
        string input;
        getline(cin, input);

        // User pressed ENTER → keep old value
        if (input.empty())
            return currentValue;

        // No validator → accept input
        if (!validator)
            return input;

        // Validator exists → check
        if (validator(input))
            return input;

        // Invalid input → allow retry
        cout << "Invalid input. Try again or press ENTER to skip.\n";
    }
}


// ----------------------
// --- Linked List Helpers ---
// ----------------------
UserManager::UserNode* UserManager::findUserByUsername(const string& uname)
{
    UserNode* current = head;
    while (current)
    {
        if (current->data.username == uname)
            return current;
        current = current->next;
    }
    return nullptr;
}

void UserManager::appendUser(const User& u)
{
    UserNode* newNode = new UserNode(u);
    if (!head)
        head = newNode;
    else
    {
        UserNode* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

// ----------------------
// --- Core Functions ---
// ----------------------
void UserManager::init()
{
    User admin;
    admin.username = "admin";
    admin.password = "admin123";
    admin.role = ADMIN;
    admin.age = 0; // or a meaningful value
    admin.registrationDate = time(nullptr);

    head = new UserNode(admin);
    cout << "Initialized with default admin account.\n";
}

bool UserManager::authenticate(const string& username, const string& password, User& loggedUser)
{
    UserNode* current = head;
    while (current)
    {
        if (current->data.username == username && current->data.password == password)
        {
            loggedUser = current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}

void UserManager::addUser(const User& currentUser)
{
    if (currentUser.role != ADMIN)
    {
        cout << "Access denied. Only admin can add users.\n";
        return;
    }

    User u;
    cin.ignore();

    u.fullName = getValidatedInput("Enter full name: ", isValidName, "Letters and spaces only.");
    u.age = getValidatedInt("Enter age: ", 18, 120);
    u.location = getValidatedInput("Enter location: ", [](const string& s){ return !s.empty(); }, "Cannot be empty.");
    u.phoneNumber = getValidatedInput("Enter phone number (09XXXXXXXX): ", isValidEthiopianPhone, "Invalid phone format.");

    u.registrationDate = time(nullptr);
    u.username = generateUsername(u.fullName, u.phoneNumber);
    u.password = generatePassword();

    cout << "Select role (1-Receptionist, 2-Doctor): ";
    int roleChoice;
    cin >> roleChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    u.role = (roleChoice == 2 ? DOCTOR : RECEPTIONIST);

    appendUser(u);

    cout << "User '" << u.fullName << "' added successfully!\n";
    cout << "Username: " << u.username << "\n";
    cout << "Password: " << u.password << "\n";
}

void UserManager::removeUser(const User& currentUser)
{
    if (currentUser.role != ADMIN)
    {
        cout << "Access denied. Only admin can remove users.\n";
        return;
    }

    string uname;
    cout << "Enter username to remove: ";
    cin >> uname;
    cin.ignore();

    if (uname == currentUser.username)
    {
        cout << "Cannot delete your own admin account.\n";
        return;
    }

    UserNode* target = findUserByUsername(uname);
    if (!target)
    {
        cout << "User not found.\n";
        return;
    }

    cout << "\nUser found:\n";
    cout << "Full Name : " << target->data.fullName << "\n";
    cout << "Username  : " << target->data.username << "\n";
    cout << "Role      : " << roleToString(target->data.role) << "\n";

    if (!confirmAction("Are you sure you want to delete this user?"))
    {
        cout << "Deletion cancelled.\n";
        return;
    }

    // Remove node from linked list
    if (target == head)
        head = target->next;
    else
    {
        UserNode* prev = head;
        while (prev->next != target) prev = prev->next;
        prev->next = target->next;
    }

    delete target;
    cout << "User removed successfully.\n";
}

void UserManager::listUsers(const User& currentUser)
{
    if (currentUser.role != ADMIN)
    {
        cout << "Access denied. Only admin can list users.\n";
        return;
    }

    if (!head)
    {
        cout << "No users found.\n";
        return;
    }

    cout << "\n--- Staff Accounts ---\n";
    cout << left
         << setw(15) << "Username"
         << setw(25) << "Full Name"
         << setw(5)  << "Age"
         << setw(10) << "Role"
         << setw(15) << "Phone"
         << setw(20) << "Location"
         << setw(20) << "Registered"
         << "\n";

    cout << string(110, '-') << "\n";

    UserNode* current = head;
    while (current)
    {
        User &u = current->data;
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&u.registrationDate));

        cout << left
             << setw(15) << u.username
             << setw(25) << u.fullName
             << setw(5)  << u.age
             << setw(10) << roleToString(u.role)
             << setw(15) << u.phoneNumber
             << setw(20) << u.location
             << setw(20) << buffer
             << "\n";

        current = current->next;
    }
}

// Updates a field if the new value is different, sets updated flag
void updateField(string& field, const string& newValue, bool& updatedFlag) {
    if (newValue != field) {
        field = newValue;
        updatedFlag = true;
    }
}
void UserManager::updateOwnProfile(User &loggedUser)
{
    UserNode* current = head;
    bool updated = false; // Track if any field changed

    while (current)
    {
        if (current->data.username == loggedUser.username)
        {
            User &u = current->data;
            cin.ignore(); // clear leftover newline

            cout << "\n--- Update Your Profile ---\n";
            cout << "Press ENTER to skip a field.\n\n";

            // Full Name
            updateField(u.fullName, getUpdatedField("Full Name", u.fullName, isValidName), updated);

            // Age
            string ageInput = getUpdatedField("Age", to_string(u.age));
            if (!ageInput.empty()) {
                try {
                    int newAge = stoi(ageInput);
                    if (newAge > 0 && newAge < 120) {
                        if (newAge != u.age) {
                            u.age = newAge;
                            updated = true;
                        }
                    } else {
                        cout << "Invalid age. Skipped.\n";
                    }
                } catch (...) {
                    cout << "Invalid age input. Skipped.\n";
                }
            }

            // Location
            updateField(u.location, getUpdatedField("Location", u.location), updated);

            // Phone Number
            updateField(u.phoneNumber, getUpdatedField("Phone Number", u.phoneNumber, isValidEthiopianPhone), updated);

            // Password
            cout << "\nDo you want to change your password?\n";
            cout << "1. Regenerate automatically\n2. Create your own\n0. Skip\nChoice: ";
            int choice;
            cin >> choice;
            cin.ignore(); // clear newline

            if (choice == 1) {
                u.password = generatePassword();
                cout << "New password: " << u.password << "\n";
                updated = true;
            } else if (choice == 2) {
                string newPass = getValidatedInput(
                    "Enter new password: ",
                    [](const string& s){ return s.length() >= 6; },
                    "Password must be at least 6 characters."
                );
                if (newPass != u.password) {
                    u.password = newPass;
                    updated = true;
                }
            }

            loggedUser = u; // update the logged-in user

            if (updated)
                cout << "\nProfile updated successfully!\n";
            else
                cout << "\nNo changes were made to your profile.\n";

            return;
        }

        current = current->next;
    }

    cout << "Error: Your profile was not found.\n";
}

// void UserManager::updateOwnProfile(User &loggedUser)
// {
//     UserNode* current = head;
//     bool updated = false; // Track if any field is updated

//     while (current)
//     {
//         if (current->data.username == loggedUser.username)
//         {
//             User &u = current->data;
//             cin.ignore(); // clear leftover newline

//             cout << "\n--- Update Your Profile ---\n";
//             cout << "Press ENTER to skip a field.\n\n";

//             // Update Full Name
//             u.fullName = getUpdatedField("Full Name", u.fullName, isValidName);

//             // Update Agewh
//             string ageStr = getUpdatedField("Age", to_string(u.age));
//             if (!ageStr.empty())
//             {
//                 try {
//                     int age = stoi(ageStr);
//                     if (age > 18 && age < 120)
//                         u.age = age;
//                     else
//                         cout << "Invalid age. Skipped.\n";
//                 } catch (...) {
//                     cout << "Invalid age input. Skipped.\n";
//                 }
//             }

//             // Update Location
//             u.location = getUpdatedField("Location", u.location);

//             // Update Phone Number
//             u.phoneNumber = getUpdatedField("Phone Number", u.phoneNumber, isValidEthiopianPhone);

//             // Update Password
//             cout << "\nDo you want to change your password?\n";
//             cout << "1. Regenerate automatically\n2. Create your own\n0. Skip\nChoice: ";
//             int choice; 
//             cin >> choice;
//             cin.ignore(); // clear newline
//             if (choice == 1)
//             {
//                 u.password = generatePassword();
//                 cout << "New password: " << u.password << "\n";
//             }
//             else if (choice == 2)
//             {
//                 string newPass = getValidatedInput(
//                     "Enter new password: ",
//                     [](const string& s){ return s.length() >= 6; },
//                     "Password must be at least 6 characters."
//                 );
//                 u.password = newPass;
//             }

//             loggedUser = u;
//             cout << "\nProfile updated successfully!\n";
//             return;
//         }

//         current = current->next;
//     }

//     cout << "Error: Your profile was not found.\n";
// }

void UserManager::resetUserCredentials()
{
    string fullName = getValidatedInput("Enter full name of user to reset: ", [](const string& s){ return !s.empty(); }, "Cannot be empty.");
    string phone = getValidatedInput("Enter phone number of user: ", isValidEthiopianPhone, "Invalid phone format.");

    UserNode* uNode = head;
    while (uNode)
    {
        User &u = uNode->data;
        if (u.fullName == fullName && u.phoneNumber == phone)
        {
            if (u.role == ADMIN)
            {
                cout << "Cannot reset Admin account via this method.\n";
                return;
            }

            u.username = generateUsername(u.fullName, u.phoneNumber);
            u.password = generatePassword();

            cout << "Credentials reset successfully.\n";
            cout << "New Username: " << u.username << "\n";
            cout << "New Password: " << u.password << "\n";
            return;
        }
        uNode = uNode->next;
    }

    cout << "User not found or phone number mismatch.\n";
}



