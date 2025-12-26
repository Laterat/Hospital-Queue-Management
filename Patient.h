#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

struct Patient
{
    int id;          // Unique patient ID
    string name;     // Patient name
    int age;         // Age
    string symptoms; // Reason for visit
    int priority;    // 1 = Emergency, 0 = Normal
};

#endif
