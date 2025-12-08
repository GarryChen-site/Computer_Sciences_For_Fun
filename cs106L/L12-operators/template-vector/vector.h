#ifndef BOUNDED_VECTOR_H
#define BOUNDED_VECTOR_H

#include <cstddef>
#include <iostream>
#include <iterator>

namespace mycollection {

template <typename T>
class vector {
 public:
  using value_type = T;
  using iterator = T*;
  using const_iterator = const T*;

  vector(size_t capacity = 10);
  ~vector();

  value_type& at(size_t index);
  value_type& front();
  value_type& back();

  const value_type& at(size_t index) const;
  const value_type& front() const;
  const value_type& back() const;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  bool empty();
  size_t size() const;
  size_t capacity() const;

  void clear();
  iterator insert(iterator pos, const value_type& value);
  iterator erase(iterator pos);
  void push_back(const value_type& value);
  void pop_back();

  // Operators
  vector<T>& operator+=(const T& element);
  vector<T>& operator+=(const vector<T>& other);

  void debug();

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

// Operators (non-member)
template <typename T>
vector<T> operator+(const vector<T>& lhs, const vector<T>& rhs) {
  vector<T> copy = lhs;
  copy += rhs;
  return copy;
}

template <typename T>
vector<T> operator+(const vector<T>& lhs, const T& rhs) {
  vector<T> copy = lhs;
  copy += rhs;
  return copy;
}

template <typename T_>
std::ostream& operator<<(std::ostream& out, const vector<T_>& rhs) {
  std::copy(rhs.begin(), rhs.end(), std::ostream_iterator<T_>(out, " "));
  out << std::endl;
  return out;
}

#include "vector.cpp"

#endif  // BOUNDED_VECTOR_H