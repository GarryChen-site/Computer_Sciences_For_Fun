#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

/*
 * CHALLENGE #5:
 * Modify fileToString above to turn every exclamation point in the file
 * into a question mark. In other words, if the file contains the line
 * "Also, test your might, Mortal Kombat!", you should turn that line into
 * "Also, test your might, Mortal Kombat?".
 */

string fileToString(ifstream& file) {
  string ret = "";
  string line;

  while (getline(file, line)) {
    auto excl2qst = [](char& c) { return (c == '!') ? '?' : c; };
    transform(line.begin(), line.end(), line.begin(), excl2qst);
    ret += line + " ";
  }
  return ret;
}

const string CORRECT_CHAL1 =
    "Thisisashortinputfilecomposedofspacesandofletters."
    "Itisalsoafilewithendoflinecharacterstohelpyoutotestyourcodeandhelpyougetst"
    "arted.Isn'tthisthebestassignmentforyoutosolve?Also,testyourmight,"
    "MortalKombat!I'mnotsosure.";
const string CORRECT_CHAL5 =
    "Thisisashortinputfilecomposedofspacesandofletters."
    "Itisalsoafilewithendoflinecharacterstohelpyoutotestyourcodeandhelpyougetst"
    "arted.Isn'tthisthebestassignmentforyoutosolve?Also,testyourmight,"
    "MortalKombat?I'mnotsosure.";

void removeSpaces(string& s) {
  s.erase(
      remove_if(s.begin(), s.end(), [](unsigned char c) { return isspace(c); }),
      s.end());
}

int main() {
  ifstream f("res/short.txt");
  string student_str = fileToString(f);
  removeSpaces(student_str);

  if (student_str == CORRECT_CHAL1)
    cout << "Matched Challenge 1!" << endl;
  else if (student_str == CORRECT_CHAL5)
    cout << "Matched Challenge 5!" << endl;
  else
    cout << "Try again!" << endl;

  return 0;
}
