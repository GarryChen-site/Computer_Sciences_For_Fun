#ifndef BOUNDED_VECTOR_H
#define BOUNDED_VECTOR_H

#include <cstddef>

namespace mycollection {
template <typename T>
class vector {
 public:
  using value_type = T;
  using iterator = T*;

  vector(size_t capacity = 10);
  ~vector();

  value_type& at(size_t index);
  value_type& front();
  value_type& back();

  iterator begin();
  iterator end();

  bool empty();
  size_t size();
  size_t capacity();

  void clear();
  iterator insert(iterator pos, const value_type& value);
  void push_back(const value_type& value);
  void pop_back();
  iterator erase(iterator pos);

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

#endif  // BOUNDED_VECTOR_H