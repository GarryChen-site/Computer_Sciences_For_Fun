#include "vector.h"

#include <iostream>

using namespace mycollection;

vector::vector(size_t capacity) {
  _capacity = capacity;
  _size = 0;
  _elems = new value_type[_capacity];
}

vector::~vector() { delete[] _elems; }

vector::value_type& vector::at(size_t index) {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return _elems[index];
}

vector::value_type& vector::front() { return *begin(); }

vector::value_type& vector::back() { return *(end() - 1); }

vector::iterator vector::begin() { return _elems; }

vector::iterator vector::end() { return _elems + size(); }

bool vector::empty() { return size() == 0; }

size_t vector::capacity() { return _capacity; }

void vector::clear() { _size = 0; }

vector::iterator vector::insert(iterator pos, value_type value) {
  int index = pos - begin();
  if (size() == capacity()) {
    reserve(2 * size());
  }
  pos = begin() + index;
  std::copy(pos, end(), pos + 1);
  *pos = value;
  ++_size;
  return pos;
}

vector::iterator vector::erase(iterator pos) {
  std::copy(pos + 1, end(), pos);
  --_size;
  return pos;
}

void vector::push_back(value_type value) { insert(end(), value); }

void vector::pop_back() { --_size; }

void vector::debug() {
  for (iterator it = begin(); it != end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void vector::reserve(size_t new_capacity) {
  if (new_capacity <= capacity()) {
    return;
  }
  value_type* new_elems = new value_type[new_capacity];
  std::copy(begin(), end(), new_elems);
  delete[] _elems;
  _elems = new_elems;
  _capacity = new_capacity;
}