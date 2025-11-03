#include <iostream>
#include <map>
#include <utility>
using namespace std;

void print_pair(const pair<int, int>& p) {
  cout << p.first << ":" << p.second << endl;
}

int main() {
  map<int, int> map{{1, 2}, {3, 4}};
  auto iter = map.begin();

  ++iter;
  cout << "First line is a pair" << endl;
  print_pair(*iter);

  cout << "Second line is an int " << endl;
  cout << (*iter).second << endl;
  auto iter2 = iter;
  ++iter;
  cout << "Third line is undefined behavior " << endl;

  cout << "Fourth line is a pair" << endl;
  print_pair(*iter2);
}