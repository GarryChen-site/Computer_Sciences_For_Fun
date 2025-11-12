#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

struct Course {
  string name;
  double rating;
};

ostream& operator<<(ostream& os, const Course& c) {
  os << setw(15) << setfill(' ') << c.name << "   " << c.rating;
  return os;
}

// how many times does [type] [val] appear in [range of elements]
template <typename InputIt, typename DataType>
int count_occurrences(InputIt begin, InputIt end, const DataType& val) {
  int count = 0;
  for (auto iter = begin; iter != end; ++iter) {
    if (*iter == val) {
      ++count;
    }
  }
  return count;
}

bool isLessThan5(int val) { return val < 5; }

bool isLessThanLimit(int val, int limit) { return val < limit; }

vector<Course> readCourses() {
  vector<Course> v = {
      {"CS 106A", 4.4337},  {"CS 106B", 4.4025},  {"CS 107", 4.6912},
      {"CS 103", 4.0532},   {"CS 109", 4.6062},   {"CS 110", 4.343},
      {"Math 51", 3.6119},  {"Math 52", 4.325},   {"Math 53", 4.3111},
      {"Econ 1", 4.2552},   {"Anthro 3", 3.71},   {"Educ 342", 4.55},
      {"Chem 33", 3.50},    {"German 132", 4.83}, {"Econ 137", 4.84},
      {"CS 251", 4.24},     {"TAPS 103", 4.79},   {"Music 21", 4.37},
      {"English 10A", 4.41}};
  shuffle(v.begin(), v.end(), default_random_engine{});
  return v;
}

vector<double> readNumbers() {
  vector<double> numbers;
  generate_n(back_inserter(numbers), 500, rand);
  return numbers;
}

int main() {
  auto courses = readCourses();
  auto numbers = readNumbers();

  sort(numbers.begin(), numbers.end());

  auto course_less_than = [](const auto& c1, const auto& c2) {
    return c1.name < c2.name;
  };

  sort(courses.begin(), courses.end(), course_less_than);

  copy(courses.begin(), courses.end(), ostream_iterator<Course>(cout, "\n"));
}