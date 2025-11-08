#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <typename Iter, typename ElemType>
int count_occurrences(Iter begin, Iter end, const ElemType& val);

template <typename Iter, typename ElemType, typename UniPred>
int count_occurrences(Iter begin, Iter end, const ElemType& val, UniPred pred);

int main() {
  vector<int> vec{5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5};
  list<double> list{4.7, 3, 4, 3.7, 4.7, 2.9, 4.7};
  string s{"Hello world!"};

  cout << count_occurrences(vec.begin(), vec.end(), 3) << endl;  // returns 10
  cout << count_occurrences(list.begin(), list.end(), 4.7)
       << endl;                                                // returns 3
  cout << count_occurrences(s.begin(), s.end(), 'X') << endl;  // returns 0
  cout << count_occurrences(vec.begin() + vec.size() / 2, vec.end(), 5)
       << endl;  // returns 1

  cout << count_occurrences(vec.begin(), vec.end(), 3, [](int a, int b) {
    return abs(a - b) < 2;
  }) << endl;  // returns 10 (all 3s are within 2 of 3)
}

template <typename Iter, typename ElemType>
int count_occurrences(Iter begin, Iter end, const ElemType& val) {
  int count = 0;
  for (auto iter = begin; iter != end; ++iter) {
    if (*iter == val) {
      ++count;
    }
  }
  return count;
}

template <typename Iter, typename ElemType, typename UniPred>
int count_occurrences(Iter begin, Iter end, const ElemType& val, UniPred pred) {
  int count = 0;
  for (auto iter = begin; iter != end; ++iter) {
    if (pred(*iter, val)) {
      ++count;
    }
  }
  return count;
}