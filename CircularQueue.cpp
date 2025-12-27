#include "CircularQueue.h"
#include <iostream>
using namespace std;

CircularQueue::CircularQueue(int cap)
{
    capacity = cap;
    queue = new Patient[capacity];
    front = 0;
    rear = -1;
    size = 0;
}

CircularQueue::~CircularQueue()
{
    delete[] queue;
}

bool CircularQueue::isEmpty()
{
    return size == 0;
}

bool CircularQueue::isFull()
{
    return size == capacity;
}

int CircularQueue::count()
{
    return size;
}

void CircularQueue::enqueue(Patient p)
{
    if (isFull())
    {
        cout << "Queue full! Cannot register patient.\n";
        return;
    }

    if (p.priority == 1)
    { // Emergency
        int i = size;
        while (i > 0)
        {
            int idx = (front + i) % capacity;
            int prev = (front + i - 1) % capacity;
            if (queue[prev].priority == 1)
                break;
            queue[idx] = queue[prev];
            i--;
        }
        queue[(front + i) % capacity] = p;
        rear = (rear + 1) % capacity;
    }
    else
    {
        rear = (rear + 1) % capacity;
        queue[rear] = p;
    }

    size++;
    cout << "Patient registered successfully.\n";
}

void CircularQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "No patients to consult.\n";
        return;
    }

    Patient p = queue[front];
    cout << "\nConsulting Patient:\n";
    cout << "ID: " << p.id << ", Name: " << p.name
         << ", Priority: " << (p.priority ? "Emergency" : "Normal") << "\n";

    front = (front + 1) % capacity;
    size--;
}

void CircularQueue::display()
{
    if (isEmpty())
    {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "\n--- Waiting Patients ---\n";
    for (int i = 0; i < size; i++)
    {
        int idx = (front + i) % capacity;
        cout << "ID: " << queue[idx].id
             << ", Name: " << queue[idx].name
             << ", Age: " << queue[idx].age
             << ", Priority: " << (queue[idx].priority ? "Emergency" : "Normal")
             << "\n";
    }
}

Patient *CircularQueue::searchPatient(int id)
{
    for (int i = 0; i < size; i++)
    {
        int idx = (front + i) % capacity;
        if (queue[idx].id == id)
            return &queue[idx];
    }
    return nullptr;
}

int CircularQueue::estimatedWaitingTime(int id)
{
    int avgTime = 15; // minutes
    int time = 0;

    for (int i = 0; i < size; i++)
    {
        int idx = (front + i) % capacity;
        if (queue[idx].id == id)
            return time;
        time += avgTime;
    }
    return -1;
}
