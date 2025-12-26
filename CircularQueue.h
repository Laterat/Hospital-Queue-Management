#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "Patient.h"
#include <iostream>
using namespace std;

class CircularQueue
{
private:
    int front, rear, size, capacity;
    Patient *queue;

public:
    CircularQueue(int cap);
    ~CircularQueue();

    bool isFull();
    bool isEmpty();
    int count();

    void enqueue(Patient p);          // Normal + emergency
    void dequeue();                   // Doctor consults patient
    void display();                   // Show queue
    Patient *searchPatient(int id);   // Search patient by ID
    int estimatedWaitingTime(int id); // Waiting time in minutes
};

#endif
