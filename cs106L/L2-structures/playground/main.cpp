#include <iostream>
#include <utility>

using namespace std;

struct S {
  int a, b;
  string c;
};

struct Time {
  int hour, minute, second;
};

int main() {
  S my_struct;
  my_struct.a = 1;
  my_struct.b = 2;
  my_struct.c = "Hello, World!";

  pair<int, double> p;
  p.first = 42;
  p.second = 3.14;

  tuple<int, double, int> t;
  get<0>(t) = 7;
  get<1>(t) = 2.71;
  get<2>(t) = 42;

  Time time;
  time.hour = 10;
  time.minute = 30;
  time.second = 45;

  auto i = 1L;
  auto pi = 3.14;

  auto copy = time;

  auto pair_copy = p;

  auto num = 3.2;

  auto str = string("Hello");

  auto func = [](int x) { return x * x; };
}
