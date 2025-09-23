#include <math.h>

#include <iostream>
#include <utility>
using namespace std;

int read_int(string prompt) {
  int val;
  cout << prompt;
  cin >> val;
  return val;
}

struct Solution {
  double one;
  double two;
  bool has_solutions;
};

pair<pair<double, double>, bool> solve_quadratic(int a, int b, int c) {
  double D = b * b - 4 * a * c;
  pair<double, double> blank;
  if (D < 0) {
    return make_pair(blank, false);
  }
  pair<double, double> answers =
      make_pair((-b + sqrt(D)) / 2, (-b - sqrt(D)) / 2);
  return make_pair(answers, true);
}

int main() {
  int a = read_int("Type in a: ");
  int b = read_int("Type in b: ");
  int c = read_int("Type in c: ");
  auto [roots, found] = solve_quadratic(a, b, c);
  auto [root1, root2] = roots;
  if (found) {
    cout << "Roots are: " << root1 << " and " << root2 << endl;
  } else {
    cout << "No real roots" << endl;
  }
}