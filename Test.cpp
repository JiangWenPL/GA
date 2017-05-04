#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int main() {
  stringstream ss;
  string temp;
  // while (getline(cin, temp)) {
  //   ss << temp;
  //   int ac;
  //   while(ss >> ac){
  //     cout << "ac=" << ac << endl;
  //   }
  // }
  int ac;
  do {
    getline(cin, temp);
    ss << temp;
    while (ss >> ac) printf("Ac = %d\n", ac);
  }
  return 0;
}