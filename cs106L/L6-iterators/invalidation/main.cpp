#include <deque>
#include <iostream>

using namespace std;

void print_deque(const deque<int>& collection) {
  cout << "{";
  for (auto iter = collection.begin(); iter != collection.end(); ++iter) {
    cout << *iter << " ";
  }
  cout << "}" << endl;
}

void erase_elem_bad(deque<int>& d, int val) {
  for (auto iter = d.begin(); iter != d.end();
       ++iter) {  // ++iter may be invalid
    if (*iter == val) {
      d.erase(iter);  // once you call erase, iter is invalidated
    }
  }
}

void erase_elem(deque<int>& d, int val) {
  for (auto iter = d.begin(); iter != d.end(); /* empty */) {
    if (*iter == val) {
      iter = d.erase(iter);  // erase returns a valid iterator
    } else {
      ++iter;  // only increment if not erased
    }
  }
}

int main() {
  deque<int> d{3, 1, 4, 1, 5, 3, 3, 3, 3, 4, 1, 1, 3};
  //   erase_elem_bad(d, 3);
  print_deque(d);  // may crash or print garbage

  erase_elem(d, 3);
  print_deque(d);
}
