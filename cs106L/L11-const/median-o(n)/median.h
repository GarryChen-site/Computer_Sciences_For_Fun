#ifndef MEDIAN_H
#define MEDIAN_H

#include <vector>

namespace mycollection {

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
  std::vector<T> _elems;
  Compare _comp;
};

template <typename T, typename Compare>
StreamingMedianTracker<T, Compare>::StreamingMedianTracker(const Compare& comp)
    : _elems(), _comp(comp) {}

template <typename T, typename Compare>
void StreamingMedianTracker<T, Compare>::insert(const_reference value) {
  auto pos = std::lower_bound(_elems.begin(), _elems.end(), value, _comp);
  _elems.insert(pos, value);
}

template <typename T, typename Compare>
typename StreamingMedianTracker<T, Compare>::const_reference
StreamingMedianTracker<T, Compare>::getMedian() const {
  return _elems[_elems.size() / 2];
}

template <typename T, typename Compare>
template <typename InputIt>
void StreamingMedianTracker<T, Compare>::insert(InputIt first, InputIt last) {
  std::for_each(first, last,
                [this](const auto& elem) { return this->insert(elem); });
}
}  // namespace mycollection

#endif  // MEDIAN_H