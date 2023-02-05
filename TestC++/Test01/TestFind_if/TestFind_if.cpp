// find_if example
#include <iostream>     // std::cout
#include <algorithm>    // std::find_if
#include <vector>       // std::vector
#include <map>
#include <tuple>

using namespace std;

bool IsOdd(int i) {
  return ((i % 2) == 1);
}

int main() {
  std::vector<int> myvector;
  map<int, tuple<int, int>> m0;

  

  m0.insert(pair<int, tuple<int, int>>(1, tuple<int, int>(10, 11)));
  m0.insert(pair<int, tuple<int, int>>(2, tuple<int, int>(20, 21)));
  m0.insert(pair<int, tuple<int, int>>(3, tuple<int, int>(30, 31)));
  m0.insert(pair<int, tuple<int, int>>(4, tuple<int, int>(40, 41)));
  m0.insert(pair<int, tuple<int, int>>(5, tuple<int, int>(50, 51)));

  auto xxx = m0[2];


  myvector.push_back(10);
  myvector.push_back(25);
  myvector.push_back(40);
  myvector.push_back(55);

  std::vector<int>::iterator it = std::find_if(myvector.begin(), myvector.end(), IsOdd);
  std::cout << "The first odd value is " << *it << '\n';

  return 0;
}