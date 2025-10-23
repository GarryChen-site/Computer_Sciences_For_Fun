#include <string>
#include <vector>
using namespace std;

auto calculateSum(const vector<string>& v) {
  auto multiplier = 2.4;                       // double
  auto name = "Ito-En";                        // char* (c-string)
  auto betterName1 = string{"Ito-En"};         // std::string
  const auto& betterName2 = string{"Ito-En"};  // const std::string&
  auto copy = v;                               // vector<string>
  auto& refMult = multiplier;                  // double&
  auto func = [](auto i) { return i * 2; };

  return betterName1;
}

struct Discount {
  double discountFactor;
  int expirationDate;
  string nameOfDiscount;
};  // this semicolon is required

void structures() {
  auto prices = make_pair(3.4, 5);       // pair<double, int>
  auto values = make_tuple(3, 4, "hi");  // tuple<int, int, const char*>

  // access via get/set
  prices.first = prices.second;     // prices = {5.0, 5}
  get<0>(values) = get<1>(values);  // values = {4, 4, "hi"}

  // structured bindings (C++17) - extract each element
  auto [a, b] = prices;            // a, b are copies of 5.0 and 5
  const auto& [x, y, z] = values;  // x, y, z are const references to 4, 4, "hi"

  // Call to Discount's constructor or initializer list
  auto coupon1 = Discount{0.2, 20240101, "New Year Sale"};
  Discount coupon2{0.3, 20240214, "Valentine's Day Sale"};

  coupon1.discountFactor = 0.8;
  coupon2.expirationDate = coupon1.expirationDate;

  // extract each component
  auto [factor, date, name] = coupon1;
}