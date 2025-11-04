#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

template <typename T>
void print_non_map(const T& collection) {
  cout << "{";
  for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
    cout << *iter << " ";
  }
  cout << "}" << endl;
}

template <typename T>
void print_map(const T& collection) {
  cout << "{";
  for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
    cout << iter->first << ": " << iter->second << " ";
  }
  cout << "}" << endl;
}

int main() {
  deque<int> d{1, 2, 3, 5, 6};
  d.insert(d.end(), 7);
  print_non_map(d);  // d = {1 2 3 5 6 7 }

  // erase 2
  d.erase(++d.begin());
  print_non_map(d);  // d = {1 3 5 6 7 }

  // insert 4 at index 2
  d.insert(d.begin() + 2, 4);
  print_non_map(d);  // d = {1 3 4 5 6 7 }

  // erase from index 2 to end
  d.erase(d.begin() + 2, d.end());
  print_non_map(d);  // d = {1 3}

  // Map

  map<int, int> map{{3, 4}, {1, 2}, {5, 6}};

  map.insert({7, 8});
  print_map(map);  // map = {1: 2 3: 4 5: 6 7: 8 }

  // insert {3, 0}, should fail as key 3 exists
  auto [map_iter, success] = map.insert({3, 0});
  cout << "Insertion success: " << success << endl;
  print_map(map);  // map = {1: 2 3: 4 5: 6 7: 8 }

  // modify value for key 3
  map_iter->second = 0;
  print_map(map);  // map = {1: 2 3: 0 5: 6 7: 8 }

  // vector
  vector<int> vec{40, 60, 30, 70, 10, 20};
  set<int> set1{15, 35, 55, 75};
  set<int> set2{25, 35, 45, 65, 80, 100};

  // convert vec to set
  set<int> set3{vec.begin(), vec.end()};
  print_non_map(set3);  // set3 = {10, 20, 30, 40, 60, 70}

  // insert contents of set1 into vec at the beginning
  vec.insert(vec.begin(), set1.begin(), set1.end());
  print_non_map(vec);  // vec = {15, 35, 55, 75, 40, 60, 30, 70, 10, 20}
}