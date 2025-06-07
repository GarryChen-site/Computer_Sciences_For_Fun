// heappatientqueue.h
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"
using namespace std;

const int INITIAL_CAPACITY = 10;

struct HeapPatient {
    string name;
    int priority;
};

class HeapPatientQueue : public PatientQueue  {
public:
    HeapPatientQueue();
    ~HeapPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    HeapPatient* patients;
    int capacity;
    int count;
    void expand();
    void shrink();
    void bubbleUp(int index);
    void bubbleDown(int index);
    void swap(int index1, int index2);
};
