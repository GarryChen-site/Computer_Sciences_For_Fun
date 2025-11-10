#include <iostream>

using namespace std;

/*
  Substitution Failure Is Not An Error
  When the compiler tries to substitute an explicitly specified or deduced type
  into a template and fails, the specialization is discarded from the overload
  set, and does not cause a compiler error. The easiest way to achieve this is
  using SFINAE on the trailing return type.
*/

struct RubberDuck {
  int duck_radius;
  size_t size() const {
    cout << "Measuring the size of rubber duck: ";
    double volume = 4 * 3.14 * duck_radius * duck_radius * duck_radius / 3.0;
    return static_cast<size_t>(volume);
  }
};

struct NumberLikeDuck {
  operator int() const {
    cout << "Printing with conversion operator ";
    return 7;
  }
};

struct ConfuseDuck {
  int duck_radius;
  size_t size() const {
    cout << "Measuring the size of rubber duck: ";
    double volume = 4 * 3.14 * duck_radius * duck_radius * duck_radius / 3.0;
    return static_cast<size_t>(volume);
  }
  operator int() const {
    cout << "Printing with conversion operator ";
    return 7;
  }
};

// (void) [condition], size_t() means try substituting [condition] to ensure it
// semantically compiles but discard that result (hence the (void)). The comma
// operator ignores the left-hand side, and returns the default value of
// size_t(), which is how the return value is determined.

template <typename T>
auto print_size(const T& a) -> decltype((void)a.size(), size_t()) {
  cout << "printing with size member function: ";
  auto size = a.size();
  cout << size << endl;
  return size;
}

template <typename T>
auto print_size(const T& a) -> decltype((void)-a, size_t()) {
  cout << "printing with negative numeric function: ";
  auto size = a < 0 ? -a : a;
  cout << size << endl;
  return size;
}

template <typename T>
auto print_size(const T& a) -> decltype((void)a->size(), size_t()) {
  cout << "printing with pointer function: ";
  auto size = a->size();
  cout << size << endl;
  return size;
}

int main() {
  vector<int> vec{1, 2, 3};
  print_size(vec);
  print_size(vec[1]);
  print_size(&vec);

  RubberDuck duck{3};
  print_size(duck);

  NumberLikeDuck number_duck{};
  print_size(number_duck);

  //   ConfuseDuck confuse_duck{2};
  //   print_size(confuse_duck);  // ERROR: Ambiguous! both first and second
  //   match

  return 0;
}