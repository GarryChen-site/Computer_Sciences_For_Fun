#ifndef BOUNDED_VECTOR_H
#define BOUNDED_VECTOR_H

#include <cstddef>

namespace mycollection {
class vector {
 public:
  // Type aliases
  using value_type = int;
  using iterator = int*;

  // Special member functions
  vector(size_t capacity = 10);
  ~vector();

  // Element access
  value_type& at(size_t index);
  value_type& front();
  value_type& back();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_t size();
  size_t capacity();

  // Modifiers
  void clear();
  iterator insert(iterator pos, value_type value);
  iterator erase(iterator pos);
  void push_back(value_type value);
  void pop_back();

  // For debugging
  void debug();

  template <typename InputIt>
  void swap_elements(InputIt first, InputIt last);

  void reserve(size_t new_capacity);

 private:
  value_type* _elems;
  size_t _capacity;
  size_t _size;
};
}  // namespace mycollection

template <typename InputIt>
void mycollection::vector::swap_elements(InputIt first, InputIt last) {
  if (std::distance(first, last) != static_cast<int>(size())) {
    throw std::length_error("Can't swap: ranges have different sizes");
  }
  for (int i = 0; i < size(); ++i) {
    auto temp = _elems[i];
    _elems[i] = *first;
    *first++ = temp;
  }
}

#endif  // BOUNDED_VECTOR_H