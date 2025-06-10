
#pragma once

#include <iostream>
#include "vector.h"
using namespace std;


class MyMap
{
public:
    MyMap();
    ~MyMap();

    int get(int key) const;
    void put(int key, int value);
    bool containsKey(int key) const;
    Vector<int> keys() const;
    int size() const;

    MyMap(const MyMap& other);
    MyMap& operator=(const MyMap& other);
    friend ostream& operator<<(ostream& out, MyMap& myMap);
    friend istream& operator>>(istream& in, MyMap& myMap);

private:

    struct key_val_pair {
        int key;
        int value;
        key_val_pair* next;
    };

    typedef key_val_pair** bucketArray;

    bucketArray createBucketArray(int nBuckets);
    int hashFunction(int key) const;

    bucketArray buckets;

    int nBuckets;
    int nElements;
};