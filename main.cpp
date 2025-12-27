#include <iostream>
#include "CircularQueue.h"
#include "UserManager.h"
#include "Auth.h"
#include "Utils.h"
#include <limits>

using namespace std;

int getQueueCapacity(int maxLimit) {
    int cap;
    cout << "Enter max queue capacity (1-" << maxLimit << "): ";
    while (!(cin >> cap) || cap <= 0 || cap > maxLimit) {
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
                cout << "4. Logout\n";
                cin >> c;

                if (c == 1)
                    UserManager::addUser();
                else if (c == 2)
                    UserManager::removeUser();
                else if (c == 3)
                    UserManager::listUsers();
            } while (c != 4);
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
                cout << "5. Logout\n";
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
                    cout << "Emergency (1=Yes,0=No): ";
                    cin >> p.priority;
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
            } while (c != 5);
        }

        else if (currentUser.role == DOCTOR)
        {
            int c;
            do
            {
                cout << "\n[DOCTOR MENU]\n";
                cout << "1. Consult Next Patient\n";
                cout << "2. Display Queue\n";
                cout << "3. Logout\n";
                cin >> c;

                if (c == 1)
                    queue.dequeue();
                else if (c == 2)
                    queue.display();
            } while (c != 3);
        }
    }
}
