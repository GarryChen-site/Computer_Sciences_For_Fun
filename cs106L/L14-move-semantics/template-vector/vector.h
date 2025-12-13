#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>

namespace mycollection {
template <typename T>
class vector {
 public:
  using value_type = T;
  using iterator = T*;
  using const_iterator = const T*;

  // Special Member Functions
  vector(size_t capacity = 10);
  ~vector();
  vector(const vector<T>& other);
  vector<T>& operator=(const vector<T>& rhs);

  // fill constructor
  vector(size_t capacity, const T& init);

  // Element Access
  value_type& at(size_t index);
  value_type& front();
  value_type& back();

  const value_type& at(size_t index) const;
  const value_type& front() const;
  const value_type& back() const;

  // Iterators
  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  // Capacity
  bool empty() const;
  size_t size() const;
  size_t capacity() const;

  // Modifiers
  void clear();
  iterator insert(iterator pos, const value_type& value);
  iterator erase(iterator pos);
  void push_back(const value_type& value);
  void pop_back();

  // Operators (as member functions)
  vector<T>& operator+=(const T& element);
  vector<T>& operator+=(const vector<T>& other);

  // For Debugging Only
  void debug() const;

  template <typename InputIt>
  void swap_elements(InputIt first, InputIt last);

  void reserve(size_t n);

 private:
  value_type* _elems;
  size_t _capacity;
  size_t _size;
};
}  // namespace mycollection

using mycollection::vector;

template <typename T>
vector<T> operator+(const vector<T>& lhs, const T& rhs) {
  vector<T> copy = lhs;
  copy += rhs;
  return copy;
}

template <typename T>
vector<T> operator+(const T& lhs, const vector<T>& rhs) {
  vector<T> copy = rhs;
  copy += lhs;
  return copy;
}

template <typename T_>
std::ostream& operator<<(std::ostream& out, const vector<T_>& rhs) {
  std::copy(rhs.begin(), rhs.end(), std::ostream_iterator<T_>(out, " "));
  out << std::endl;
  return out;
}

#include "vector.cpp"

#endif