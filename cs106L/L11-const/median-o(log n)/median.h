#ifndef MEDIAN_H
#define MEDIAN_H

#include <functional>
#include <queue>
#include <vector>

namespace mycollection {

template <typename Compare>
struct InvertedCompare {
  Compare comp;
  InvertedCompare(const Compare& c) : comp(c) {}
  template <typename T>
  bool operator()(const T& a, const T& b) const {
    return comp(b, a);
  }
};

template <typename T, typename Compare = std::less<T>>
class StreamingMedianTracker {
 public:
  using const_reference = const T&;

  StreamingMedianTracker(const Compare& comp = Compare());

  void insert(const_reference value);

  const_reference getMedian() const;

  template <typename InputIt>
  void insert(InputIt first, InputIt last);

 private:
  Compare _comp;

  // Max-heap for the lower half, largest of lower half on top
  // Use Compare (std::less)
  std::priority_queue<T, std::vector<T>, Compare> _lower;

  // Min-heap for the upper half, smallest of upper half on top
  // Use InvertedCompare to invert the ordering
  std::priority_queue<T, std::vector<T>, InvertedCompare<Compare>> _upper;

  void balance();
};

template <typename T, typename Compare>
StreamingMedianTracker<T, Compare>::StreamingMedianTracker(const Compare& comp)
    : _comp(comp), _lower(comp), _upper(InvertedCompare<Compare>(comp)) {}

template <typename T, typename Compare>
void StreamingMedianTracker<T, Compare>::balance() {
  if (_lower.size() > _upper.size() + 1) {
    _upper.push(_lower.top());
    _lower.pop();
  } else if (_upper.size() > _lower.size()) {
    _lower.push(_upper.top());
    _upper.pop();
  }
}

template <typename T, typename Compare>
void StreamingMedianTracker<T, Compare>::insert(const_reference value) {
  if (_lower.empty()) {
    _lower.push(value);
  } else if (!_comp(_lower.top(), value)) {
    _lower.push(value);
  } else {
    _upper.push(value);
  }
  balance();
}

template <typename T, typename Compare>
typename StreamingMedianTracker<T, Compare>::const_reference
StreamingMedianTracker<T, Compare>::getMedian() const {
  if (_lower.empty()) {
    throw std::runtime_error("No elements in the tracker");
  }
  if (_lower.size() > _upper.size()) {
    return _lower.top();
  } else {
    return _upper.top();
  }
}

template <typename T, typename Compare>
template <typename InputIt>
void StreamingMedianTracker<T, Compare>::insert(InputIt first, InputIt last) {
  std::for_each(first, last, [this](const auto& elem) { this->insert(elem); });
}
}  // namespace mycollection

#endif  // MEDIAN_H