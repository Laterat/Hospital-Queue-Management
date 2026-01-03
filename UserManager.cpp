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
UserManager::UserNode *UserManager::head = nullptr;

void UserManager::init()
{
    User admin;
    admin.username = "admin";
    admin.password = "admin123";
    admin.role = ADMIN;
    head = new UserNode(admin);
    cout << "Initialized with default admin account.\n";
}

bool UserManager::authenticate(const string &username, const string &password, User &loggedUser)
{
    UserNode *current = head;
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



// ---- Helper functions ----
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
    if (phone[0] != '0' || phone[1] != '9') return false;
    for (char c : phone)
        if (!isdigit(c)) return false;
    return true;
}

void UserManager::addUser(const User &currentUser)
{

    if (currentUser.role != ADMIN)
    {
        cout << "Access denied. Only admin can add users.\n";
        return;
    }

    User u;

    // -------- Full Name --------
    do
    {
        cout << "Enter full name: ";
        getline(cin, u.fullName);

        if (!isValidName(u.fullName))
            cout << "Invalid name. Letters and spaces only.\n";

    } while (!isValidName(u.fullName));

    // -------- Age --------
    while (true)
    {
        cout << "Enter age: ";
        cin >> u.age;

        if (!cin.fail() && u.age >= 18 && u.age <= 120)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        cout << "Invalid age. Enter a number between 18 and 120.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // -------- Location --------
    do
    {
        cout << "Enter location: ";
        getline(cin, u.location);

        if (u.location.empty())
            cout << "Location cannot be empty.\n";

    } while (u.location.empty());

    // -------- Phone Number --------
    do
    {
        cout << "Enter phone number (09XXXXXXXX): ";
        getline(cin, u.phoneNumber);

        if (!isValidEthiopianPhone(u.phoneNumber))
            cout << "Invalid phone number. Use 09XXXXXXXX format.\n";

    } while (!isValidEthiopianPhone(u.phoneNumber));

    // Set registration date
    u.registrationDate = time(nullptr);

    u.username = generateUsername(u.fullName);
    u.password = generatePassword();

    // Choose role
    cout << "Select role (1-Receptionist, 2-Doctor): ";
    int roleChoice;
    cin >> roleChoice;

    switch (roleChoice)
    {
    case 1:
        u.role = RECEPTIONIST;
        break;
    case 2:
        u.role = DOCTOR;
        break;
    default:
        cout << "Invalid choice. Defaulting to RECEPTIONIST.\n";
        u.role = RECEPTIONIST;
    }

    // Create new node
    UserNode *newNode = new UserNode(u);

    // Append to linked list
    if (!head)
    {
        head = newNode; // first user
    }
    else
    {
        UserNode *temp = head;
        while (temp->next)
            temp = temp->next; // move to last node
        temp->next = newNode;
    }

    cout << "User '" << u.fullName << "' added successfully!\n";
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

    UserNode *current = head;
    UserNode *prev = nullptr;

    while (current)
    {
        // Prevent deleting self
        if (current->data.username == currentUser.username)
        {
            cout << "Error: You cannot delete your own admin account.\n";
            return;
        }

          // Check if this is the user to delete
        if (current->data.username == uname)
        {
            // Show user details for confirmation
            cout << "\nUser found:\n";
            cout << "Full Name : " << current->data.fullName << '\n';
            cout << "Username  : " << current->data.username << '\n';
            cout << "Role      : "
                 << (current->data.role == DOCTOR ? "DOCTOR" : "RECEPTIONIST") << "\n";

                  // Confirm deletion
            string confirm;
            cout << "Are you sure you want to delete this user? (y/n): ";
            cin >> confirm;

            if (confirm != "y" && confirm != "Y")
            {
                cout << "Deletion cancelled.\n";
                return;
            }


          // Delete node safely
            if (prev)
                prev->next = current->next;
            else
                head = current->next;

            delete current;
            cout << "User removed successfully.\n";
            return;
        }

        prev = current;
        current = current->next;
    }

    cout << "User not found.\n";
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

    // Table header
    cout << left
         << setw(15) << "Username"
         << setw(25) << "Full Name"
         << setw(5)  << "Age"
         << setw(10) << "Role"
         << setw(15) << "Phone"
         << setw(20) << "Location"
         << setw(20) << "Registered"
         << "\n";

     cout << string(110, '-') << "\n"; // separator line

    // Traverse the linked list
    UserNode *current = head;
    while (current)
    {
        User &u = current->data;

        // Format registration date
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

void UserManager::updateOwnProfile(User &loggedUser)
{
    UserNode *current = head;
    while (current)
    {
        if (current->data.username == loggedUser.username)
        {
            User &u = current->data;
            cout << "Updating your profile: " << u.username << "\n";

            cout << "Full Name (" << u.fullName << "): ";
            cin.ignore();
            string fullName;
            getline(cin, fullName);
            if (!fullName.empty())
            {
                u.fullName = fullName;
                u.username = generateUsername(u.fullName); // auto-update username
            }

            cout << "Age (" << u.age << "): ";
            string ageStr;
            getline(cin, ageStr);
            if (!ageStr.empty())
                u.age = stoi(ageStr);

            cout << "Location (" << u.location << "): ";
            string loc;
            getline(cin, loc);
            if (!loc.empty())
                u.location = loc;

            cout << "Phone Number (" << u.phoneNumber << "): ";
            string phone;
            getline(cin, phone);
            if (!phone.empty())
                u.phoneNumber = phone;

            cout << "Do you want to regenerate password? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                u.password = generatePassword();
                cout << "New password: " << u.password << "\n";
            }

            loggedUser = u; // update session info
            cout << "Profile updated successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Error: Your profile was not found.\n";
}

void UserManager::resetUserCredentials()
{
    string fullName, phone;
    cout << "Enter full name of the user to reset: ";
    cin.ignore();
    getline(cin, fullName);
    cout << "Enter phone number of the user: ";
    getline(cin, phone);

    UserNode *current = head;
    while (current)
    {
        User &u = current->data;
        if (u.fullName == fullName && u.phoneNumber == phone)
        {
            if (u.role == ADMIN)
            {
                cout << "Cannot reset Admin account via this method.\n";
                return;
            }

            u.username = generateUsername(u.fullName);
            u.password = generatePassword();

            cout << "Credentials reset successfully.\n";
            cout << "New Username: " << u.username << "\n";
            cout << "New Password: " << u.password << "\n";
            return;
        }
        current = current->next;
    }

    cout << "User not found or phone number mismatch.\n";
}
