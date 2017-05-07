#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// struct individual {
//   char Chrom[6 * 3 + 1][Chromosome_Legth + 1];
//   double Coeff[Gene_Max][6 * 3 + 1];
//   double Fitness;
// };
const int HexChromLength = 7;
const char HexTab[][5] = {"0000", "0001", "0010", "0011", "0100", "0101",
                          "0110", "0111", "1000", "1001", "1010", "1011",
                          "1100", "1101", "1110", "1111"};
const map<string, char> BinToHex = {
    {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
    {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
    {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
    {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };
const map<char, string> HexToBin = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };
// void HexToBin(char *Hex, char *Buf) { ; }
int main() {
  // srand(time(NULL));
  // for (int i = 0; i < 10; i++) {
  //   cout << (4.0*rand() / RAND_MAX)-2<< " ";
  // }
  // cout << endl;
  double x = -1.234567;
  char HexBuf[8 + 2];
  char Chrome[28 + 1];
  sprintf(HexBuf, "%X", (int)floor(x * 1000000));
  printf("HexBuf=%s\n", HexBuf);
  for (int Iter_HB = 0; Iter_HB < HexChromLength - 1; Iter_HB++) {
    sprintf(Chrome + 4 * Iter_HB, "%s", HexToBin[HexBuf[Iter_HB]]);
  }
  printf("Aftter encode the chromosome is:\n%s\n", Chrome);
  return 0;
}