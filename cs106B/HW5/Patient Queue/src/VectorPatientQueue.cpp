// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "VectorPatientQueue.h"

VectorPatientQueue::VectorPatientQueue() {
}

VectorPatientQueue::~VectorPatientQueue() {
}

void VectorPatientQueue::clear() {
    patients.clear();
}

string VectorPatientQueue::frontName() {
    if(patients.isEmpty()) {
        throw("Invalid operation: The queue of patients is empty.");
    }

    int outgoing = 0;
    for(int i = 1; i < patients.size(); i++) {
        if(patients[i].priority < patients[outgoing].priority) {
            outgoing = i;
        } else if (patients[i].priority == patients[outgoing].priority) {
            if (patients[i].timestamp < patients[outgoing].timestamp) {
                outgoing = i;
            }
        }
        return patients[outgoing].name;
    }
}

int VectorPatientQueue::frontPriority() {
    if (patients.isEmpty()) {
        throw("Invalid operation: The queue of patients is empty.");
    }
    int outgoing = 0;
    for (int i = 1; i < patients.size(); i++) {
        if (patients[i].priority < patients[outgoing].priority) {
            outgoing = i;
        }
    }
    return patients[outgoing].priority;
}

bool VectorPatientQueue::isEmpty() {
    return patients.isEmpty();
}

void VectorPatientQueue::newPatient(string name, int priority) {
    Patient newPatient = {name, priority, patients.size() + 1};
    patients.add(newPatient);
}

string VectorPatientQueue::processPatient() {
    if (patients.isEmpty()) {
        throw("Invalid operation: The queue of patients is empty.");
    }

    int outgoing = 0;
    for (int i = 1; i < patients.size(); i++) {
        if (patients[i].priority < patients[outgoing].priority) {
            outgoing = i;
        } else if (patients[i].priority == patients[outgoing].priority) {
            if (patients[i].timestamp < patients[outgoing].timestamp) {
                outgoing = i;
            }
        }
    }

    string name = patients[outgoing].name;
    patients.remove(outgoing);
    return name;

}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    if (patients.isEmpty()) {
        throw("Invalid operation: The queue of patients is empty.");
    }

    int toModify = 0;
    for (int i = 1; i < patients.size(); i++) {
        if (patients[i].name == name) {
            if (patients[toModify].name == name) {
                if (patients[toModify].priority > patients[i].priority) {
                    toModify = i;
                } else if (patients[toModify].priority == patients[i].priority &&
                        patients[toModify].timestamp > patients[i].timestamp) {
                    toModify = i;
                }
            } else {
                toModify = i;
            }
        }
    }

    if (patients[toModify].name != name) {
        throw("Invalid operation: The patient " + name + " is not in the queue.");
    }
    if (patients[toModify].priority < newPriority) {
        throw("Invalid operation: The new priority must be lower than the current priority.");
    }
    patients[toModify].priority = newPriority;
}

string VectorPatientQueue::toString() {
    string patientQueue = "";
    int end = patients.size();
    for (int i = 0; i < end; i++) {
        if (i == end - 1){
            patientQueue += integerToString(patients[i].priority) + ":" + patients[i].name;
        } else {
            patientQueue += integerToString(patients[i].priority) + ":" + patients[i].name + ", ";
        }
    }
    return "{" + patientQueue + "}";
}
