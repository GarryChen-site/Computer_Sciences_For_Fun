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

double timePushBack(int numValues) {
  deque<int> d;

  time_type t1 = chrono::high_resolution_clock::now();

  for (int i = 0; i < numValues; ++i) {
    d.push_back(i);
  }

  time_type t2 = chrono::high_resolution_clock::now();

  return chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
}

double timePushFront(int numValues) {
  deque<int> d;

  time_type t1 = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < numValues; ++i) {
    d.push_front(i);
  }

  time_type t2 = std::chrono::high_resolution_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

int main() {
  cout << "Warming up..." << endl;
  timePushBack(1000);
  timePushFront(1000);

  cout << "PushBack vs PushFront Performance Test" << endl;
  cout << "=======================================" << endl;

  vector<int> containerSizes;
  vector<double> pushBackTimes;
  vector<double> pushFrontTimes;

  const int numIterations = 20;
  const int startVal = 500;

  int numToInsert = startVal;
  for (int i = 0; i < numIterations; ++i) {
    cout << "Process: " << fixed << setprecision(2)
         << (100.0 * i / numIterations) << "% complete" << endl;

    containerSizes.push_back(numToInsert);
    double timeToVecAccess = timePushBack(numToInsert);
    double timeToDeqAccess = timePushFront(numToInsert);
    pushBackTimes.push_back(timeToVecAccess);
    pushFrontTimes.push_back(timeToDeqAccess);
    numToInsert *= 2;
  }

  cout << "\n100.0% complete\n\n";

  // Display results in a table format
  cout << "Results:\n";
  cout << "========\n";
  cout << left << setw(15) << "Container Size" << setw(15) << "Push Back (ms)"
       << setw(15) << "Push Front (ms)" << setw(15) << "Difference" << endl;
  cout << string(60, '-') << endl;

  for (size_t i = 0; i < containerSizes.size(); ++i) {
    double diff = pushFrontTimes[i] - pushBackTimes[i];
    cout << left << setw(15) << containerSizes[i] << setw(15) << fixed
         << setprecision(2) << pushBackTimes[i] << setw(15) << fixed
         << setprecision(2) << pushFrontTimes[i] << setw(15) << fixed
         << setprecision(2) << diff << endl;
  }

  // Calculate and display averages
  double avgVectorTime = 0, avgDequeTime = 0;
  for (size_t i = 0; i < pushBackTimes.size(); ++i) {
    avgVectorTime += pushBackTimes[i];
    avgDequeTime += pushFrontTimes[i];
  }
  avgVectorTime /= pushBackTimes.size();
  avgDequeTime /= pushFrontTimes.size();

  cout << "\nSummary:\n";
  cout << "========\n";
  cout << "Average push back time: " << fixed << setprecision(2)
       << avgVectorTime << " ms\n";
  cout << "Average push front time:  " << fixed << setprecision(2)
       << avgDequeTime << " ms\n";
  cout << "Performance difference:     " << fixed << setprecision(2)
       << avgDequeTime - avgVectorTime << " ms\n";

  if (avgVectorTime < avgDequeTime) {
    cout << "Push Back is faster on average!\n";
  } else if (avgDequeTime < avgVectorTime) {
    cout << "Push Front is faster on average!\n";
  } else {
    cout << "Both operations have similar performance!\n";
  }

  return 0;
}