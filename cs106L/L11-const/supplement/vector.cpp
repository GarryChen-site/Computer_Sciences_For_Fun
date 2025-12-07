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
  // this is called the static_cast/const_cast trick
  // here is the logic:
  // (1) cast 'this' to a const vector<T>*
  // (2) call its at() function. since *this is a const vector<T>,
  //      it will invoke the const version that you want to call
  // (3) the return value of the const version is a const vector<T>::value_type&
  // (4) cast away the const of that return value to get a
  // vector<T>::value_type&
  // (5) finally, return that non-const
  // vector<T>::value_type& as the return value
  return const_cast<typename vector<T>::value_type&>(
      static_cast<const vector<T>*>(this)->at(index));
}

template <typename T>
typename vector<T>::value_type& vector<T>::front() {
  return const_cast<typename vector<T>::value_type&>(
      static_cast<const vector<T>*>(this)->front());
}

template <typename T>
typename vector<T>::value_type& vector<T>::back() {
  return const_cast<typename vector<T>::value_type&>(
      static_cast<const vector<T>*>(this)->back());
}

template <typename T>
const typename vector<T>::value_type& vector<T>::at(size_t index) const {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return _elems[index];
}

template <typename T>
const typename vector<T>::value_type& vector<T>::front() const {
  return *begin();
}

template <typename T>
const typename vector<T>::value_type& vector<T>::back() const {
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
typename vector<T>::const_iterator vector<T>::begin() const {
  return _elems;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return _elems + size();
}

template <typename T>
bool vector<T>::empty() const {
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
void vector<T>::debug() const {
  std::copy(begin(), end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';
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
void vector<T>::reserve(size_t n) {
  (void)n;  // To avoid unused parameter warning
}