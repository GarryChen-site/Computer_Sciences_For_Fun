#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  string line;
  while (getline(inputFile, line)) {
    // convert line into a stringstream to parse
    // the external device isn't a console or file, but a string
    stringstream ss(line);
    string name;
    int coolness;
    ss >> name >> coolness;

    cout << name << " is cool by a factor of " << coolness * 2 << endl;
  }

  return 0;
}