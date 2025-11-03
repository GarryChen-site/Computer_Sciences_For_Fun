#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

void demo_input_iterators() {
  cout << "=== INPUT ITERATORS DEMO ===" << endl;
  cout << "Input iterators can ONLY be dereferenced as r-values (read-only)\n"
       << endl;

  // istream_iterator is an INPUT iterator
  istringstream iss("10 20 30 40 50");
  istream_iterator<int> input_iter(iss);
  istream_iterator<int> end_iter;

  // ✅ VALID: Dereference as r-value (reading)
  cout << "Reading values (r-value access):" << endl;
  while (input_iter != end_iter) {
    int value = *input_iter;  // r-value: reading from iterator
    cout << "  Read: " << value << endl;
    ++input_iter;
  }

  // ❌ INVALID: Cannot dereference as l-value (writing)
  // Uncommenting the following would cause a compilation error:
  /*
  istringstream iss2("100 200");
  istream_iterator<int> input_iter2(iss2);
  *input_iter2 = 999;  // ERROR! Can't assign to input iterator
  */

  cout << "\n";
}

void demo_output_iterators() {
  cout << "=== OUTPUT ITERATORS DEMO ===" << endl;
  cout << "Output iterators can ONLY be dereferenced as l-values (write-only)\n"
       << endl;

  // ostream_iterator is an OUTPUT iterator
  ostringstream oss;
  ostream_iterator<int> output_iter(oss, " ");

  // ✅ VALID: Dereference as l-value (writing)
  cout << "Writing values (l-value access):" << endl;
  *output_iter = 100;  // l-value: writing to iterator
  ++output_iter;
  *output_iter = 200;
  ++output_iter;
  *output_iter = 300;
  ++output_iter;

  cout << "  Output stream contains: " << oss.str() << endl;

  // ❌ INVALID: Cannot dereference as r-value (reading)
  // Uncommenting the following would cause a compilation error:
  /*
  int value = *output_iter;  // ERROR! Can't read from output iterator
  */

  cout << "\n";
}

void demo_forward_iterators() {
  cout << "=== FORWARD ITERATORS (for comparison) ===" << endl;
  cout
      << "Forward iterators can be dereferenced as BOTH r-values AND l-values\n"
      << endl;

  vector<int> vec = {1, 2, 3, 4, 5};
  auto iter = vec.begin();

  // ✅ VALID: Dereference as r-value (reading)
  int value = *iter;
  cout << "  Read (r-value): " << value << endl;

  // ✅ VALID: Dereference as l-value (writing)
  *iter = 999;
  cout << "  Write (l-value): changed first element to " << *iter << endl;

  cout << "\n";
}

int main() {
  demo_input_iterators();
  demo_output_iterators();
  demo_forward_iterators();

  cout << "=== SUMMARY ===" << endl;
  cout << "Input Iterators:   *iter (r-value only) ✅  |  *iter = x (l-value) "
          "❌"
       << endl;
  cout << "Output Iterators:  *iter (r-value) ❌       |  *iter = x (l-value "
          "only) ✅"
       << endl;
  cout << "Forward Iterators: *iter (r-value) ✅       |  *iter = x (l-value) "
          "✅"
       << endl;

  return 0;
}