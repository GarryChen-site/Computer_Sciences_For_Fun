#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int dotProduct(const vector<int>& v1, const vector<int>& v2) {
  /*
   * Return the dot product of the two given vectors! We can
   * assume that v1 and v2 are the same length.
   */

  return inner_product(v1.begin(), v1.end(), v2.begin(), 0);
}

const int CORRECT_CHAL6 = 0;

int main() {
  int student_res = dotProduct({1, 0, -1}, {1, 0, 1});
  if (student_res == CORRECT_CHAL6) {
    cout << "Matched challenge 6!" << endl;
  } else {
    cout << "Try again!" << endl;
  }
  return 0;
}