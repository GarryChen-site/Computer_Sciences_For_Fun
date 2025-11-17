#include <iostream>
#include <ranges>
#include <string>
using namespace std;

// template <typename T>
template <ranges::forward_range T>
int countOccurrences(const T& text, const T& feature) {
  int count = 0;

  auto curr = text.begin();
  auto end = text.end();
  while (curr != end) {
    auto found = search(curr, end, feature.begin(), feature.end());
    if (found == end) {
      break;
    }
    ++count;
    curr = found + 1;
  }
  return count;
}

const int CORRECT_CHAL34 = 4;
const string HAYSTACK = "thank you next next thank you next next";
const string NEEDLE = "next";

int main() {
  //   int student_count = countOccurrences(21, 11);
  int student_count = countOccurrences(HAYSTACK, NEEDLE);
  if (student_count == CORRECT_CHAL34)
    cout << "Matched challenges 3 and 4!" << endl;
  else
    cout << "Your count was " << student_count << ", but the correct answer is "
         << CORRECT_CHAL34 << ". Try again!" << endl;

  return 0;
}
