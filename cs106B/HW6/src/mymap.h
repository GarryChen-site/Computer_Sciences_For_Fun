
#pragma once

#include <iostream>

using namespace std;


class MyMap
{
public:
    MyMap();
    ~MyMap();

    int get(int key) const;
    void put(int key, int value);
    bool containsKey(int key) const;

    friend ostream& operator<<(ostream& out, MyMap& myMap);
    friend istream& operator>>(istream& in, MyMap& myMap);
};