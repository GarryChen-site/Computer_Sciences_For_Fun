#include <iostream>
#include <string>
using namespace std;

void waitForEnter(const string& msg) {
  cout << msg;
  string l;
  getline(cin, l);
  cout << endl;
}

/*
 * Tests the buffer without flushing
 *
 * try output a string to the stream, then does some slow operation
 * and then output another string to the stream. We will see nothing
 * printed until the very end because the output is buffered.
 */
void testBuffer(ostream& os) {
  os << "Before loop - ";
  for (int i = 0; i < 2000000000; i++) {
    // waste time
  }
  os << "After loop" << endl;
}

/*
 * the first string is printed to the console,
 * and then there is a delay before the second string is printed.
 */
void testBufferWithFlush(ostream& os) {
  os << "Before loop - " << flush;
  for (int i = 0; i < 2000000000; i++) {
    // waste time
  }
  os << "After loop" << endl;
}

int main() {
  waitForEnter("Press ENTER to test buffered output...");
  cout << "Testing cout..." << endl;
  testBuffer(cout);
  cout << "Done testing cout." << endl << endl;

  cout << string(20, '=') << endl;

  waitForEnter("Press ENTER to test flushed output...");
  cout << "Testing cout with flush..." << endl;
  testBufferWithFlush(cout);
  cout << "Done testing cout with flush." << endl;
}