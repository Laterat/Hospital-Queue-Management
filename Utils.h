#ifndef UTILS_H
#define UTILS_H

#include "Patient.h"
#include <iostream>
using namespace std;

int generatePatientID()
{
    static int id = 1000;
    return id++;
}

#endif
