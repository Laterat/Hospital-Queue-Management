#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

enum Priority { NORMAL = 0, EMERGENCY = 1 };


   struct Patient
{
    int id;
    string name;
    int age;
    string symptoms;
    Priority priority;

    time_t arrivalTime;
    string phone;
    string address;

    bool isEmergency;
    bool isConsulted;
    int estimatedConsultationTime;
};
     




#endif
