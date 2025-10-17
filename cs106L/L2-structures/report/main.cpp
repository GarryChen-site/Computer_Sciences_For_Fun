#include <iostream>
#include <string>

using namespace std;

pair<int, string> report_lines() {
  string line;
  int number_of_lines = 0;
  string longest;

  while (getline(cin, line)) {
    number_of_lines++;
    if (line.length() > longest.length()) {
      longest = line;
    }
  }
  return make_pair(number_of_lines, longest);
}

int main() {
  string prompt = "Enter a bunch of words (press ctrl+d when you done):";

  auto [num_lines, longest_line] = report_lines();
  cout << "You entered " << num_lines << " lines." << endl;
  cout << "The longest line was: " << longest_line << endl;
}