// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"
#include "strlib.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    front = nullptr;  
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    while(front != nullptr) {
        PatientNode* temp = front;
        front = front->next;  // Move front to the next node
        delete temp;          // Delete the old front node
    }
}

void LinkedListPatientQueue::clear() {
    while(front != nullptr) {
        PatientNode* temp = front;
        front = front->next;  
        delete temp;          
    }
}

string LinkedListPatientQueue::frontName() {
    if(front == nullptr) {
        throw("Invalid Operation: The queue of patients is empty.");
    }
    return front->name;  
}

int LinkedListPatientQueue::frontPriority() {
    if(front == nullptr) {
        throw("Invalid Operation: The queue of patients is empty.");
    }
    return front->priority;  
}

bool LinkedListPatientQueue::isEmpty() {
    return front == nullptr;
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    PatientNode* newNode = new PatientNode(name, priority);
    if (front == nullptr) {
        front = newNode;
    } else if (front->priority > priority) {
        newNode->next = front;
        front = newNode;
    } else {
        PatientNode* current = front;
        while (current->next != nullptr && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

string LinkedListPatientQueue::processPatient() {
    if (front == nullptr) {
        throw("Invalid Operation: The queue of patients is empty.");
    }
    PatientNode* trash = front;
    string outgoing = trash->name;
    front = front->next;
    delete trash;
    return outgoing;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    if(front == nullptr) {
        throw("Invalid Operation: The queue of patients is empty.");
    }

    PatientNode* current = front;
    while(current->next != nullptr && current->name != name) {
        current = current->next;
    }
    if(current->next == nullptr) {
        throw("Invalid Operation: The patient " + name + " is not in the queue.");
    }
    PatientNode* patientToUpgrade = current;
    if(patientToUpgrade->priority < newPriority) {
        throw("Invalid Operation: The new priority must be lower than the current priority.");
    }
    current->next = patientToUpgrade->next;  
    newPatient(patientToUpgrade->name, newPriority); 
    delete patientToUpgrade; 
}

string LinkedListPatientQueue::toString() {
    if (front == nullptr) {
        return "{}";
    }
    string patientQueue;
    PatientNode* current = front;
    while (current->next != nullptr) {
        patientQueue += integerToString(current->priority) + ":" + current->name + ", ";
        current = current->next;
    }
    patientQueue += integerToString(current->priority) + ":" + current->name;
    return "{" + patientQueue + "}";    

}
