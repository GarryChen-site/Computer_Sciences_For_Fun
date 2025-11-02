#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
    Write a function named friendList that takes in a file name and reads friend
   relationships from a file and writes them to a Map. friendList should return
   the populated Map. Friendships are bi-directional, so if Abby is friends with
   Barney, Barney is friends with Abby. The file contains one friend
   relationship per line, with names separated by a single space. You do not
   have to worry about malformed entries.

    Then the call of friendList("buddies.txt") should return a resulting map
   that looks like this:
    {"Abby":{"Barney", "Clyde"}, "Barney":{"Abby"}, "Clyde":{"Abby"}}

    Here is the function prototype you should implement:
    Map<string, Vector<string> > friendList(String filename)
*/
map<string, set<string>> friendList(const string& filename) {
  ifstream in;
  vector<string> lines;

  in.open(filename);
  string line;
  while (getline(in, line)) {
    lines.push_back(line);
  }

  map<string, set<string>> friends;
  for (const auto& line : lines) {
    istringstream iss(line);  // Vector<string> people = stringSplit(line, " ");
    string s1, s2;
    iss >> s1 >> s2;  // string s1 = people[0]; string s2 = people[1];

    friends[s1].insert(s2);
    friends[s2].insert(s1);
  }
  return friends;
}

int main() {
  auto answer = friendList("buddies.txt");

  for (const auto& [name, friends] : answer) {
    cout << name << ": {";
    auto last = --friends.end();
    for (auto iter = friends.begin(); iter != last; ++iter) {
      cout << *iter << ", ";
    }
    cout << *last << "}" << endl;
  }
}