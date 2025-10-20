#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void print_vector(const vector<T>& vec);

int main() {
  vector<int> original{1, 2};
  vector<int> copy = original;
  vector<int>& lref = original;

  original.push_back(3);
  copy.push_back(4);
  lref.push_back(5);

  cout << "Example in class:" << endl;
  cout << "original (lref) = ";
  print_vector(original);
  cout << "copy = ";
  print_vector(copy);
  cout << endl;

  lref = copy;
  copy.push_back(6);
  original.push_back(7);

  // Q1: what are contents of original?
  // Q2: what are contents of copy?

  cout << "Poll question in class:" << endl;
  cout << "original (lref) = ";

  print_vector(original);
  cout << "copy = ";
  print_vector(copy);
}

template <typename T>
void print_vector(const vector<T>& vec) {
  cout << "{ ";
  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    cout << *iter << " ";
    if (next(iter) != vec.end()) {
      cout << ", ";
    }
  }
  cout << "}" << endl;
}