#ifndef BOUNDED_VECTOR_H
#include "vector.h"
#endif
using namespace mycollection;

template <typename T>
vector<T>::vector(size_t capacity) {
  _capacity = capacity;
  _size = 0;
  _elems = new T[_capacity];
}

template <typename T>
vector<T>::~vector() {
  delete[] _elems;
}

template <typename T>
typename vector<T>::value_type& vector<T>::at(size_t index) {
  if (index < 0 || index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return _elems[index];
}

template <typename T>
typename vector<T>::value_type& vector<T>::front() {
  return *begin();
}

template <typename T>
typename vector<T>::value_type& vector<T>::back() {
  return *(end() - 1);
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return _elems;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return _elems + _size;
}

template <typename T>
bool vector<T>::empty() {
  return _size == 0;
}

template <typename T>
size_t vector<T>::size() const {
  return _size;
}

template <typename T>
size_t vector<T>::capacity() const {
  return _capacity;
}

template <typename T>
void vector<T>::clear() {
  _size = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const value_type& value) {
  if (_size >= _capacity) {
    throw std::length_error("Vector capacity exceeded");
  }
  std::copy_backward(pos, end(), end() + 1);
  *pos = value;
  ++_size;
  return pos;
}

template <typename T>
void vector<T>::push_back(const value_type& value) {
  if (_size >= _capacity) {
    throw std::length_error("Vector capacity exceeded");
  }
  insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Vector is empty");
  }
  --_size;
}

template <typename T>
typename vector<T>::iterator vector<T>::erase(iterator pos) {
  if (pos < begin() || pos >= end()) {
    throw std::out_of_range("Iterator out of range");
  }
  std::copy(pos + 1, end(), pos);
  --_size;
  return pos;
}

template <typename T>
void vector<T>::debug() {
  std::cout << "Vector(size=" << _size << ", capacity=" << _capacity
            << ", elements=[";
  for (size_t i = 0; i < _size; ++i) {
    std::cout << _elems[i];
    if (i < _size - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "])" << std::endl;
}

template <typename T>
template <typename InputIt>
void vector<T>::swap_elements(InputIt first, InputIt last) {
  if (std::distance(first, last) != static_cast<int>(size())) {
    throw std::length_error("Iterator range size does not match vector size");
  }
  std::swap_ranges(first, last, begin());
}

template <typename T>
void vector<T>::reserve(size_t n) {}