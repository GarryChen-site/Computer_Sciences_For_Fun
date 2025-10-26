#include <fstream>
#include <iostream>
using namespace std;

int main() {
  int number = 42;
  cout << "The answer is: " << number << endl;

  ofstream outputFile("output.txt");
  outputFile << "The answer is: " << number << endl;
  return 0;
}