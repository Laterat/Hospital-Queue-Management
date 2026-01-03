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
    string phone;
    string address;
    time_t arrivalTime;

    string symptoms;
    Priority priority;
   
    

    bool isEmergency;
    bool isConsulted;
    int estimatedConsultationTime;
};
     




#endif
