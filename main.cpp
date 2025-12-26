#include <iostream>
#include "Patient.h"
#include "CircularQueue.h"
#include "Utils.h"
using namespace std;

int main()
{
    int capacity;
    cout << "Enter maximum number of patients in queue: ";
    cin >> capacity;

    CircularQueue hospitalQueue(capacity);

    int choice;
    do
    {
        cout << "\n===== Hospital Queue Management (Staff) =====\n";
        cout << "1. Register Patient (Receptionist)\n";
        cout << "2. Consult Next Patient (Doctor)\n";
        cout << "3. Display Waiting Patients (Staff)\n";
        cout << "4. Search Patient by ID (Receptionist/Doctor)\n";
        cout << "5. Check Queue Status (Admin)\n";
        cout << "6. Estimated Waiting Time (Receptionist)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Patient p;
            p.id = generatePatientID();
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, p.name);
            cout << "Enter Age: ";
            cin >> p.age;
            cin.ignore();
            cout << "Enter Symptoms: ";
            getline(cin, p.symptoms);
            int pri;
            cout << "Emergency? 1 = Yes, 0 = No: ";
            cin >> pri;
            p.priority = pri;
            hospitalQueue.enqueue(p);
            break;
        }
        case 2:
            hospitalQueue.dequeue();
            break;
        case 3:
            hospitalQueue.display();
            break;
        case 4:
        {
            int id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            Patient *p = hospitalQueue.searchPatient(id);
            if (p)
            {
                cout << "Found Patient - ID: " << p->id << ", Name: " << p->name
                     << ", Age: " << p->age
                     << ", Symptoms: " << p->symptoms
                     << ", Priority: " << (p->priority == 1 ? "Emergency" : "Normal") << "\n";
            }
            else
                cout << "Patient not found.\n";
            break;
        }
        case 5:
            cout << "Patients in queue: " << hospitalQueue.count() << "\n";
            cout << (hospitalQueue.isEmpty() ? "Queue is empty\n" : "Queue has patients\n");
            cout << (hospitalQueue.isFull() ? "Queue is full\n" : "Queue is not full\n");
            break;
        case 6:
        {
            int id;
            cout << "Enter Patient ID for estimated waiting time: ";
            cin >> id;
            int time = hospitalQueue.estimatedWaitingTime(id);
            if (time >= 0)
                cout << "Estimated waiting time: " << time << " minutes.\n";
            else
                cout << "Patient not found.\n";
            break;
        }
        case 7:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
