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
    queue = nullptr;
}

bool CircularQueue::isEmpty()
{
    return size == 0;
}

bool CircularQueue::isFull()
{
    return size == capacity;
}

int CircularQueue::getSize() const
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

    int insertPos = size;  // logical position

    if (p.priority == EMERGENCY)
    {
        for (int i = 0; i < size; i++)
        {
            int idx = (front + i) % capacity;
            if (queue[idx].priority == NORMAL)
            {
                insertPos = i;
                break;
            }
        }
    }

    // shift logically (SAFE)
    for (int i = size; i > insertPos; i--)
    {
        int curr = (front + i) % capacity;
        int prev = (front + i - 1) % capacity;
        queue[curr] = queue[prev];
    }

    queue[(front + insertPos) % capacity] = p;
    rear = (rear + 1) % capacity;
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
 
    int time = 0;

    for (int i = 0; i < size; i++)
    {
        int idx = (front + i) % capacity;
        if (queue[idx].id == id)
            return time;
             int avgTime = (queue[idx].priority == EMERGENCY) ? 20 : 10; // minutes
        time += avgTime;
    }
    return -1;
}

Patient* CircularQueue::peek()
{
    if (isEmpty())
        return nullptr;
    return &queue[front];
}
