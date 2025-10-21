#include <iostream>
#include <string>
using namespace std;

string chopBothEnds(const string& str);

int main() {
  cout << "First example: printing each letter on a new line" << endl;
  cout << "You should get a warning about comparing signed and unsigned "
          "integers."
       << endl;
  string str = "Hello, World!";
  for (int i = 0; i < str.size(); ++i) {
    cout << str[i] << endl;
  }

  cout << "testing a very common bug with size_t. How would you fix?" << endl;
  cout << "Test case 1:" << chopBothEnds("rubber duck") << endl;
  cout << "Test case 2:" << chopBothEnds("Ito-En Green Tea") << endl;
  cout << "Test case 3:" << chopBothEnds("AB") << endl;
  cout << "Test case 4:" << chopBothEnds("A") << endl;
  cout << "Test case 5:" << chopBothEnds("") << endl;

  cout << "End of main()" << endl;
  return 0;
}

string chopBothEnds(const string& str) {
  string result = "";
  for (size_t i = 1; i < str.size() - 1; ++i) {
    result += str[i];
  }
  return result;
}
