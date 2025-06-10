
#include "mymap.h"

#include "mymap.h"

using namespace std;

const int INITIAL_SIZE = 1000;

MyMap::MyMap() {
    nBuckets = INITIAL_SIZE;
    nElements = 0;
    buckets = createBucketArray(nBuckets);
}

MyMap::~MyMap() {
    for (int i = 0; i < nBuckets; i++) {
        key_val_pair* curr = buckets[i];
        while (curr != nullptr) {
            key_val_pair* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
    }
    delete[] buckets;
}


void MyMap::put(int key, int value) {
    int bucketIndex = hashFunction(key);
    key_val_pair* existing = nullptr;
    key_val_pair* curr = buckets[bucketIndex];
    while(curr != nullptr) {
        if(curr->key == key) {
            existing = curr; // Found the key, store the pointer to update later
            break;
        }
        curr = curr->next;
    }
    
    if(existing != nullptr) {
        existing->value = value; // Update the value if the key already exists
    } else {
        key_val_pair* incoming = new key_val_pair();
        incoming->key = key;
        incoming->value = value;
        incoming->next = buckets[bucketIndex];
        buckets[bucketIndex] = incoming;
        nElements++;
    }
}


int MyMap::get(int key) const {
    int bucketIndex = hashFunction(key);
    key_val_pair* curr = buckets[bucketIndex];
    while (curr != nullptr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    throw("Invalid operation: key not found");
}

bool MyMap::containsKey(int key) const {
    int bucketIndex = hashFunction(key);
    key_val_pair* curr = buckets[bucketIndex];
    while (curr != nullptr) {
        if (curr->key == key) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

Vector<int> MyMap::keys() const {
    Vector<int> keys;
    for (int i = 0; i < nBuckets; i++) {
        key_val_pair* current = buckets[i];
        while (current != nullptr) {
            keys.add(current->key);
            current = current->next;
        }
    }
    return keys;
}

int MyMap::size() const{
    return nElements;
}

MyMap::MyMap(const MyMap& other) {
    nBuckets = other.nBuckets;

    buckets = createBucketArray(nBuckets);

    Vector<int> keys = other.keys();
    for(int i = 0; i < keys.size(); i++) {
        int key = keys[i];
        int value = other.get(key);
        put(key, value);
    }
}

MyMap& MyMap::operator= (const MyMap& other) {

    if(this == &other) {
        return *this;
    }

    // Clean up existing buckets
    for (int i = 0; i < nBuckets; i++) {
        MyMap::key_val_pair* curr = buckets[i];
        while (curr != nullptr) {
            MyMap::key_val_pair* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        delete[] buckets[i];
    }

    nElements = 0;

    Vector<int> keys = other.keys();
    for(int i = 0; i < keys.size(); i++) {
        int key = keys[i];
        int value = other.get(key);
        put(key, value);
    }
    return *this;

}

ostream& operator<<(ostream &out, MyMap &myMap) {
    out << "{";
    Vector<int> keys = myMap.keys();
    for (int i=0; i < keys.size(); i++) {
        int key = keys[i];
        int value = myMap.get(key);
        out << key << ":" << value;
        if (i < keys.size() - 1) { // print the comma after each pair except the last
            out << ", ";
        }
    }
    out << "}";
    return out;
}

istream& operator>>(istream& in, MyMap& myMap) {
    string line;
    getline(in, line);

    // Remove { and }
    if(!line.empty() && line.front() == '{'){
        line = line.substr(1);
    }
    if(!line.empty() && line.back() == '}'){
        line.pop_back();
    }

    if(line.empty()) {
        return in;
    }

    vector<string> pairs = stringSplit(line, ",");
    for (const string& pair : pairs) {
        vector<string> kvp = stringSplit(trim(pair), ":");
        if (kvp.size() == 2) {
            myMap.put(stringToInteger(trim(kvp[0])), 
                     stringToInteger(trim(kvp[1])));
        }
    }
    return in;

}



MyMap::bucketArray MyMap::createBucketArray(int nBuckets) {
    bucketArray newBuckets = new key_val_pair*[nBuckets];
    for (int i = 0; i < nBuckets; i++) {
        newBuckets[i] = nullptr;
    }
    return newBuckets;
}

int MyMap::hashFunction(int input) const {
    // use unsigned integers for calculation
    // we are also using so-called "magic numbers"
    // see https://stackoverflow.com/a/12996028/561677 for details
    unsigned int temp = ((input >> 16) ^ input) * 0x45d9f3b;
    temp = ((temp >> 16) ^ temp) * 0x45d9f3b;
    temp = (temp >> 16) ^ temp;

    // convert back to positive signed int
    // (note: this ignores half the possible hashes!)
    int hash = (int) temp;
    if (hash < 0) {
        hash *= -1;
    }

    return hash;
}