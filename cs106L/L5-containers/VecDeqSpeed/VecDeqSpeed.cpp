#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void printVector(const vector<double>& vec) {
  cout << "{";
  for (auto i : vec) {
    cout << i << " ";
  }
  cout << "}" << endl;
}

using duration_type = chrono::microseconds::rep;
using time_type = chrono::high_resolution_clock::time_point;

double timeVecAccess(int numValues) {
  vector<int> v(numValues);

  time_type t1 = chrono::high_resolution_clock::now();

  for (int i = 0; i < numValues; ++i) {
    v[i] = i;
  }

  time_type t2 = chrono::high_resolution_clock::now();

  return chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
}

double timeDeqAccess(int numValues) {
  deque<int> d(numValues);

  time_type t1 = chrono::high_resolution_clock::now();

  for (int i = 0; i < numValues; ++i) {
    d[i] = i;
  }

  time_type t2 = chrono::high_resolution_clock::now();

  return chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
}

int main() {
  cout << "Vector vs Deque Access Performance Test" << endl;
  cout << "=======================================" << endl;

  vector<int> containerSizes;
  vector<double> vectorTimes;
  vector<double> dequeTimes;

  const int numIterations = 20;
  const int startVal = 500;

  int numToInsert = startVal;
  for (int i = 0; i < numIterations; ++i) {
    cout << "Process: " << fixed << setprecision(2)
         << (100.0 * i / numIterations) << "% complete" << endl;

    containerSizes.push_back(numToInsert);
    double timeToVecAccess = timeVecAccess(numToInsert);
    double timeToDeqAccess = timeDeqAccess(numToInsert);
    vectorTimes.push_back(timeToVecAccess);
    dequeTimes.push_back(timeToDeqAccess);
    numToInsert *= 2;
  }

  cout << "\n100.0% complete\n\n";

  // Display results in a table format
  cout << "Results:\n";
  cout << "========\n";
  cout << left << setw(15) << "Container Size" << setw(15) << "Vector (ms)"
       << setw(15) << "Deque (ms)" << setw(15) << "Difference" << endl;
  cout << string(60, '-') << endl;

  for (size_t i = 0; i < containerSizes.size(); ++i) {
    double diff = dequeTimes[i] - vectorTimes[i];
    cout << left << setw(15) << containerSizes[i] << setw(15) << fixed
         << setprecision(2) << vectorTimes[i] << setw(15) << fixed
         << setprecision(2) << dequeTimes[i] << setw(15) << fixed
         << setprecision(2) << diff << endl;
  }

  // Calculate and display averages
  double avgVectorTime = 0, avgDequeTime = 0;
  for (size_t i = 0; i < vectorTimes.size(); ++i) {
    avgVectorTime += vectorTimes[i];
    avgDequeTime += dequeTimes[i];
  }
  avgVectorTime /= vectorTimes.size();
  avgDequeTime /= dequeTimes.size();

  cout << "\nSummary:\n";
  cout << "========\n";
  cout << "Average vector access time: " << fixed << setprecision(2)
       << avgVectorTime << " ms\n";
  cout << "Average deque access time:  " << fixed << setprecision(2)
       << avgDequeTime << " ms\n";
  cout << "Performance difference:     " << fixed << setprecision(2)
       << avgDequeTime - avgVectorTime << " ms\n";

  if (avgVectorTime < avgDequeTime) {
    cout << "Vector is faster on average!\n";
  } else if (avgDequeTime < avgVectorTime) {
    cout << "Deque is faster on average!\n";
  } else {
    cout << "Both containers have similar performance!\n";
  }

  return 0;
}