#ifndef UTILS_H
#define UTILS_H

inline int generatePatientID()
{
    static int id = 1000;
    return id++;
}

#endif
