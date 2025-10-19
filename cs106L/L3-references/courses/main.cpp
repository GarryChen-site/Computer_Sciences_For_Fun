#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Time;
struct Course;
void print_time(const Time& time);
void print_course(const Course& course);
void print_all_courses(const vector<Course>& courses);

struct Time {
  int hours;
  int minutes;
};

struct Course {
  string name;
  pair<Time, Time> time;
  vector<string> instructors;
};

pair<Course, bool> find(vector<Course>& courses, string& target) {
  for (const auto& [code, time, instructors] : courses) {
    if (code == target) {
      return {Course{code, time, instructors}, true};
    }
  }
  return {Course{}, false};
}

void shift(vector<Course>& courses) {
  for (auto& [code, time, instructors] : courses) {
    time.first.hours += 1;
    time.second.hours += 1;
  }
}

int main() {
  Course now{"CS106L", {{16, 30}, {17, 50}}, {"Wang", "Zeng"}};
  Course before{"CS106B", {{14, 30}, {15, 20}}, {"Gregg", "Zelenski"}};
  Course future{"CS107", {{12, 30}, {13, 50}}, {"Troccoli"}};
  vector<Course> courses{now, before, future};

  cout << "Testing find function" << endl;
  string target = "CS106B";
  auto [result, found] = find(courses, target);
  if (found) {
    print_course(result);
    cout << endl;
  } else {
    cout << "Course " << target << " not found." << endl;
  }

  cout << "Testing shift function" << endl;
  cout << "Original list of courses:" << endl;
  print_all_courses(courses);
  shift(courses);
  cout << "After shifting course" << endl;
  print_all_courses(courses);
}

void print_time(const Time& time) { cout << time.hours << ":" << time.minutes; }

void print_course(const Course& course) {
  cout << course.name << " ";
  print_time(course.time.first);
  cout << " - ";
  print_time(course.time.second);
  cout << " ";
  for (const auto& in : course.instructors) {
    cout << in << " ";
  }
}

void print_all_courses(const vector<Course>& courses) {
  for (const auto& course : courses) {
    print_course(course);
    cout << endl;
  }
}