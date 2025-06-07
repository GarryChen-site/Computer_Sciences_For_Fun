// heappatientqueue.cpp
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "HeapPatientQueue.h"
#include "strlib.h"

HeapPatientQueue::HeapPatientQueue() {
    capacity = INITIAL_CAPACITY;
    patients = new HeapPatient[capacity];
    count = 0;
}

HeapPatientQueue::~HeapPatientQueue() {
    delete [] patients;
}

void HeapPatientQueue::clear() {
    delete [] patients;
    capacity = INITIAL_CAPACITY;
    patients = new HeapPatient[capacity];
    count = 0;
}

string HeapPatientQueue::frontName() {
    if(count == 0) {
        throw("Invalid Operation: The queue of patients is empty.");
    }
    return patients[1].name;  
}

int HeapPatientQueue::frontPriority() {
    if(count == 0) {
        throw("Invalid Operation: The queue of patients is empty.");
    }
    return patients[1].priority; 
}

bool HeapPatientQueue::isEmpty() {
    return count == 0;
}

void HeapPatientQueue::newPatient(string name, int priority) {
    if(count == capacity - 1) {
        expand();
    }
    count++;
    patients[count].name = name;
    patients[count].priority = priority;
    bubbleUp(count);
}


string HeapPatientQueue::processPatient() {
    if (count == 0) {
        throw("Invalid Operation: The queue of patients is empty.");
    }
    string outgoing = patients[1].name;
    patients[1] = patients[count];
    count--;
    if(count < capacity / 2) {
        shrink();
    }
    bubbleDown(1);
    return outgoing;
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    if (count == 0) { //error case
        throw("Invalid Operation: The queue of patients is empty.");
    }
    int index = 0;
    for (int i = 1; i <= count; i++) {
        if (patients[i].name == name) {
            if (patients[i].priority >= newPriority) {
                patients[i].priority = newPriority;
            } else { //error case
                throw("Invalid Operation: The priority of the patient is already greater than the"
                " new priority.");
            }
            index = i;
            break;
        }
    }
    if (index == 0) { //error case
        throw("Invalid Operation: There is no patient with the given name.");
    } else {
        bubbleUp(index);
    }
}

string HeapPatientQueue::toString() {
    string patientQueue = "{";
    for (int i = 1; i <= count; i++) {
        if (i == count) {
            patientQueue += integerToString(patients[i].priority) + ":" + patients[i].name;
        } else {
            patientQueue += integerToString(patients[i].priority) + ":" + patients[i].name + ", ";
        }
    }
    return patientQueue + "}";
}

void HeapPatientQueue::expand() {
    HeapPatient* newPatients = new HeapPatient[capacity * 2];
    for (int i = 1; i <= count; i++) {
        newPatients[i] = patients[i];
    }
    delete [] patients;
    patients = newPatients;
    capacity *= 2;
}

void HeapPatientQueue::shrink() {
    if (capacity <= INITIAL_CAPACITY) {
        return; // Do not shrink below initial capacity
    }
    if (capacity / 2 < count + 1) {
        return; // Do not shrink if it would be too small
    }
    HeapPatient* newPatients = new HeapPatient[capacity / 2];
    for (int i = 1; i <= count; i++) {
        newPatients[i] = patients[i];
    }
    delete [] patients;
    patients = newPatients;
    capacity /= 2;
}

void HeapPatientQueue::bubbleUp(int index) {
    while (index > 1 && patients[index].priority <= patients[index / 2].priority) {
        if (patients[index].priority == patients[index / 2].priority) {
            if (patients[index].name < patients[index / 2].name) {
                swap(index, index / 2);
            }
        } else {
            swap(index, index / 2);
        }
        index /= 2;
    }
}

void HeapPatientQueue::bubbleDown(int index) {
    int left = index * 2;
    while(left <= count) {
        int moreUrgent = left;
        int right = left + 1;
        if (right <= count) {
            if (patients[right].priority <= patients[left].priority) {
                if (patients[right].priority == patients[left].priority) {
                    if (patients[right].name <= patients[left].name) {
                        moreUrgent++; 
                    }
                } else {
                    moreUrgent++;
                }
            }            
        }
        if (patients[moreUrgent].priority <= patients[index].priority) {
            if (patients[moreUrgent].priority == patients[index].priority) {
                if (patients[moreUrgent].name <= patients[index].name) {
                    swap(index, moreUrgent); 
                }
            } else {
                swap(index, moreUrgent);
            }
            index = moreUrgent;
            left = index * 2;
        } else {
            break;
        }
    }
}


void HeapPatientQueue::swap(int index1, int index2) {
    HeapPatient temp = patients[index1];
    patients[index1] = patients[index2];
    patients[index2] = temp;
}