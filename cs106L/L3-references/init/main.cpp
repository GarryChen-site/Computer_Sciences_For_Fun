#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void print_vector(const vector<T>& vec);

int main() {
  cout << "Testing out the cool constructors using uniform initialization"
       << endl;
  vector<string> default_init;

  vector<string> vec(10, "Ito-En");

  vector<string> value_init{};

  vector<string> direct_init{3, "init"};
  vector<string> copy_init = {3, "init"};
  vector<string> list_init{"C++", "Java", "Python"};
  vector<string> aggr_init = {"C++", "Java", "Python"};

  print_vector(default_init);
  print_vector(value_init);
  print_vector(direct_init);
  print_vector(copy_init);
  print_vector(list_init);
  print_vector(aggr_init);

  cout << "Careful about ambiguous uniform initialization vs. initializer_list"
       << endl;
  vector<int> int_list_init{3, 2};
  vector<int> int_fill_ctor(3, 2);
  //   auto list_init{3, 2};
  print_vector(int_list_init);
  print_vector(int_fill_ctor);

  return 0;
}

template <typename T>
void print_vector(const vector<T>& vec) {
  cout << "{";
  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    cout << *iter;
    if (next(iter) != vec.end()) {
      cout << ", ";
    }
  }
  cout << "}" << endl;
}