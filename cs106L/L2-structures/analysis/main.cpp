#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

struct Report;
pair<bool, Report> get_date_report(string country);
vector<tuple<string, size_t, size_t, double>> read_data();

struct Report {
  size_t cases;
  size_t deaths;
  double increase_rate;
};

int main() {
  while (true) {
    string date;
    cout << "Enter a date (YYYY-MM-DD)";
    getline(cin, date);
    if (date == "") return 0;
    auto [success, report] = get_date_report(date);
    if (success) {
      cout << "On " << date << " there were " << report.cases << " cases and "
           << report.deaths << " deaths reported globally, an increase of "
           << setprecision(3) << report.increase_rate << "% from previous day."
           << endl;
    } else {
      cout << "The date " << date << " was not found in the database." << endl;
    }
  }
}

/*
 * Reads the data from file into a vector.
 *
 * Parameters: date, represented as a string
 * Return value: pair of bool (if date entry was found) and found Report
 *
 * Usage:
 *      auto [found, report] = get_date_report("2020-02-01");
 */

pair<bool, Report> get_date_report(string date) {
  vector<tuple<string, size_t, size_t, double>> data = read_data();

  for (const auto& [d, cases, deaths, rate] : data) {
    if (d == date) {
      return {true, Report{cases, deaths, rate}};
    }
  }
  return {false, Report{0, 0, 0.0}};
}

vector<tuple<string, size_t, size_t, double>> read_data() {
  vector<tuple<string, size_t, size_t, double>> results;
  ifstream infile("global.txt");
  string line;
  while (getline(infile, line)) {
    istringstream iss(line);
    string date;
    size_t cases, deaths;
    double rate;
    iss >> date >> cases >> deaths >> rate;
    results.emplace_back(date, cases, deaths, rate);
  }
  return results;
}