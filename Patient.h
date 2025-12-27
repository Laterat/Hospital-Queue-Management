#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

struct Patient
{
    int id;
    string name;
    int age;
    string symptoms;
    int priority; // 1 = Emergency, 0 = Normal
};

#endif
