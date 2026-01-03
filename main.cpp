#include <iostream>
#include "CircularQueue.h"
#include "UserManager.h"
#include "Auth.h"
#include "Utils.h"
#include <limits>

using namespace std;

int getQueueCapacity(int maxLimit)
{
    int cap;
    cout << "Enter max queue capacity (1-" << maxLimit << "): ";
    while (!(cin >> cap) || cap <= 0 || cap > maxLimit)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number between 1 and " << maxLimit << ": ";
    }
    return cap;
}

int main()
{
    UserManager::init();

    const int MAX_HOSPITAL_CAPACITY = 500; // realistic max for demo
    int cap = getQueueCapacity(MAX_HOSPITAL_CAPACITY);

    cout << "Queue will be created with capacity: " << cap << endl;

    CircularQueue queue(cap);
    User currentUser;

    while (true)
    {
        cout << "\n--- Hospital System Login ---\n";
        if (!login(currentUser))
        {
            cout << "Invalid credentials.\n";
            continue;
        }

        if (currentUser.role == ADMIN)
        {
            int c;
            do
            {
                cout << "\n[ADMIN MENU]\n";
                cout << "1. Add Staff User\n";
                cout << "2. Remove Staff User\n";
                cout << "3. List Users\n";
                cout << "4. Reset User Credentials\n"; 
                cout << "5. Update My Profile\n";      
                cout << "6. Logout\n";
                cout << "Choice: ";
                cin >> c;
                cin.ignore(); // clear newline

                switch (c)
                {
                case 1:
                    UserManager::addUser( currentUser);
                    break;
                case 2:
                    UserManager::removeUser( currentUser);
                    break;
                case 3:
                    UserManager::listUsers( currentUser);
                    break;
                case 4:
                    UserManager::resetUserCredentials();
                    break;
                case 5:
                    UserManager::updateOwnProfile(currentUser);
                    break;
                case 6:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }

            } while (c != 6);
        }

        else if (currentUser.role == RECEPTIONIST)
        {
            int c;
            do
            {
                cout << "\n[RECEPTIONIST MENU]\n";
                cout << "1. Register Patient\n";
                cout << "2. Search Patient\n";
                cout << "3. Estimated Waiting Time\n";
                cout << "4. Display Queue\n";
                cout << "5. Update My Profile\n"; // new
                cout << "6. Logout\n";
                cin >> c;

                if (c == 1)
                {
                    Patient p;
                    p.id = generatePatientID();
                    cin.ignore();
                    cout << "Name: ";
                    getline(cin, p.name);

                    cout << "Age: ";
                    cin >> p.age;
                    cin.ignore();

                    cout << "Symptoms: ";
                    getline(cin, p.symptoms);

                    cout << "Emergency or Normal : ";
                    int pr;
                    cin >> pr;
                    p.priority = (pr == 1) ? EMERGENCY : NORMAL;

                    queue.enqueue(p);
                }
                else if (c == 2)
                {
                    int id;
                    cout << "Enter patient ID: ";
                    cin >> id;
                    Patient *p = queue.searchPatient(id);
                    if (p)
                        cout << "Found: " << p->name << "\n";
                    else
                        cout << "Patient not found.\n";
                }
                else if (c == 3)
                {
                    int id;
                    cout << "Patient ID: ";
                    cin >> id;
                    int t = queue.estimatedWaitingTime(id);
                    if (t >= 0)
                        cout << "Estimated wait: " << t << " minutes\n";
                    else
                        cout << "Patient not found.\n";
                }
                else if (c == 4)
                    queue.display();
                else if (c == 5)
                    UserManager::updateOwnProfile(currentUser);
                else if (c == 6)
                    cout << "Logging out...\n";
                else
                    cout << "Invalid option. Try again.\n";
            } while (c != 6);
        }

        else if (currentUser.role == DOCTOR)
        {
            int c;
            do
            {
                cout << "\n[DOCTOR MENU]\n";
                cout << "1. Peek Next Patient\n";
                cout << "2. Consult Next Patient\n";
                cout << "3. Display Queue\n";
                cout << "4. Update My Profile\n"; // new
                cout << "5. Logout\n";
                cin >> c;

                switch (c)
                {
                case 1:
                {
                    Patient *next = queue.peek();
                    if (next != nullptr)
                    {
                        cout << "\nNext Patient:\n";
                        cout << "ID: " << next->id
                             << ", Name: " << next->name
                             << ", Age: " << next->age
                             << ", Priority: " << (next->priority ? "Emergency" : "Normal") << "\n";
                    }
                    else
                    {
                        cout << "No patients in queue.\n";
                    }
                    break;
                }
                case 2:
                    queue.dequeue(); // actually consult the patient
                    break;
                case 3:
                    queue.display(); // show full queue
                    break;
                case 4:
                    UserManager::updateOwnProfile(currentUser); // new
                    break;
                case 5:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid option. Try again.\n";
                }
            } while (c != 5);
        }
    }
}
