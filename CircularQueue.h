#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "Patient.h"

class CircularQueue
{
private:
    int front, rear, size, capacity;
    Patient *queue;

public:
    CircularQueue(int cap);
    ~CircularQueue();

    bool isEmpty();
    bool isFull();
    int getSize() const;

    void enqueue(Patient p);
    void dequeue();
    void display();

    Patient *searchPatient(int id);
    int estimatedWaitingTime(int id);

    Patient* peek();

};

#endif
