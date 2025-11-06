#include <iostream>

using namespace std;

template <typename T, typename... Ts>
auto my_min(T num, Ts... args) {
  if constexpr (sizeof...(args) == 0) {
    return num;
  } else {
    auto min = my_min(args...);
    return (num < min) ? num : min;
  }
}

int main() {
  int min = my_min(3, 5, 1, 8, 2);
  cout << "Minimum value: " << min << endl;  // Output: Minimum value: 1
  return 0;
}
