#ifndef MEDIAN_H
#define MEDIAN_H

#include <vector>

namespace mycollection {
template <typename T, typename Compare = std::less<T>>

class StreamingMedianTracker {
 public:
  using const_reference = const T&;

  StreamingMedianTracker(const Compare& comp = Compare());

  ~StreamingMedianTracker() = default;

  StreamingMedianTracker(const StreamingMedianTracker<T, Compare>& other) =
      delete;
  StreamingMedianTracker<T, Compare>& operator=(
      const StreamingMedianTracker<T, Compare>& rhs) = delete;
  StreamingMedianTracker(StreamingMedianTracker<T, Compare>&& other) = default;
  StreamingMedianTracker<T, Compare>& operator=(
      StreamingMedianTracker<T, Compare>&& rhs) = default;

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
void StreamingMedianTracker<T, Compare>::insert(const_reference element) {
  auto pos = std::lower_bound(_elems.begin(), _elems.end(), element, _comp);
  _elems.insert(pos, element);
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
                [this](const_reference value) { this->insert(value); });
}

}  // namespace mycollection

#endif  // MEDIAN_H