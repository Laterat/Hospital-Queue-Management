#include "CircularQueue.h"

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

bool CircularQueue::isFull()
{
    return size == capacity;
}

bool CircularQueue::isEmpty()
{
    return size == 0;
}

int CircularQueue::count()
{
    return size;
}

// Enqueue with emergency handling
void CircularQueue::enqueue(Patient p)
{
    if (isFull())
    {
        cout << "Queue is full! Cannot add patient.\n";
        return;
    }

    if (p.priority == 1)
    { // Emergency patient
        // Shift normal patients to insert at front
        int idx = rear;
        while (size > 0 && idx >= front && queue[idx % capacity].priority == 0)
        {
            queue[(idx + 1) % capacity] = queue[idx % capacity];
            idx--;
        }
        rear = (rear + 1) % capacity;
        queue[(idx + 1 + capacity) % capacity] = p;
    }
    else
    { // Normal patient
        rear = (rear + 1) % capacity;
        queue[rear] = p;
    }

    size++;
    cout << "Patient added successfully!\n";
}

// Dequeue for consultation
void CircularQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty! No patient to consult.\n";
        return;
    }
    Patient p = queue[front];
    cout << "\nConsulting Patient ID: " << p.id
         << ", Name: " << p.name
         << ", Symptoms: " << p.symptoms
         << ", Priority: " << (p.priority == 1 ? "Emergency" : "Normal") << "\n";

    front = (front + 1) % capacity;
    size--;
}

// Display all patients in queue
void CircularQueue::display()
{
    if (isEmpty())
    {
        cout << "Queue is empty!\n";
        return;
    }

    cout << "\n---- Waiting Patients ----\n";
    for (int i = 0; i < size; i++)
    {
        int idx = (front + i) % capacity;
        cout << "ID: " << queue[idx].id
             << ", Name: " << queue[idx].name
             << ", Age: " << queue[idx].age
             << ", Symptoms: " << queue[idx].symptoms
             << ", Priority: " << (queue[idx].priority == 1 ? "Emergency" : "Normal") << "\n";
    }
}

// Search patient by ID
Patient *CircularQueue::searchPatient(int id)
{
    if (isEmpty())
        return nullptr;
    for (int i = 0; i < size; i++)
    {
        int idx = (front + i) % capacity;
        if (queue[idx].id == id)
        {
            return &queue[idx];
        }
    }
    return nullptr;
}

// Estimated waiting time
int CircularQueue::estimatedWaitingTime(int id)
{
    int avgTime = 15; // Average consultation time in minutes
    int time = 0;
    if (isEmpty())
        return -1;

    for (int i = 0; i < size; i++)
    {
        int idx = (front + i) % capacity;
        if (queue[idx].id == id)
            return time;
        time += avgTime;
    }
    return -1; // Patient not found
}
