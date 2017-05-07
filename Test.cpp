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
const int CoeffNum = 6*3 + 1;
struct Individual {
  char Chrom[CoeffNum][Chromosome_Legth];
  double Coeff[CoeffNum];
  double Fitness;
  double Surive;
  bool Alive;
  // Individual() {
  //   memset(Chrom, 0, sizeof(Chrom));
  //   memset(Coeff, 0, sizeof(Coeff));
  //   Fitness = 0;
  // }
};
const int HexChromLength = 8;
const char HexTab[][5] = {"0000", "0001", "0010", "0011", "0100", "0101",
                          "0110", "0111", "1000", "1001", "1010", "1011",
                          "1100", "1101", "1110", "1111"};
map<string, char> BinToHex = {
    {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
    {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
    {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
    {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};
map<char, string> HexToBin = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
// void HexToBin(char *Hex, char *Buf) { ; }
char *Encode(double Code, char *Chrome) {
  char HexBuf[8 + 1];
  if (Code > 10 || Code < -10) Code = fmod(Code,10);
  sprintf(HexBuf, "%07X", (int)floor(Code * 1000000));
  for (int Iter_HB = 0; Iter_HB < HexChromLength; Iter_HB++) {
    sprintf(Chrome + 4 * Iter_HB, "%s", HexToBin[HexBuf[Iter_HB]].c_str());
  }
  return Chrome;
}
double Decode(char *Chrome) {
  char DecodeBuf[8 + 1];
  memset(DecodeBuf, 0, sizeof(DecodeBuf));
  string Decoded = Chrome;
  for (int Iter_BH = 0; Iter_BH < HexChromLength; Iter_BH++) {
    DecodeBuf[Iter_BH] = BinToHex[Decoded.substr(Iter_BH * 4, 4)];
  }
  int decodedNum;
  sscanf(DecodeBuf, "%X", &decodedNum);
  return (decodedNum * 1.0 / 1000000);
}
int main() {
  // srand(time(NULL));
  // for (int i = 0; i < 10; i++) {
  //   cout << (4.0*rand() / RAND_MAX)-2<< " ";
  // }
  // cout << endl;
  // double x = 9.9999999;
  // char HexBuf[8 + 1];
  // char Chrome[28 + 1];
  // cout << "Origin Num = " << (int)floor(x * 1000000) << endl;
  // sprintf(HexBuf, "%X", (int)floor(x * 1000000));
  // printf("HexBuf=%s\n", HexBuf);
  // for (int Iter_HB = 0; Iter_HB < HexChromLength; Iter_HB++) {
  //   sprintf(Chrome + 4 * Iter_HB, "%s", HexToBin[HexBuf[Iter_HB]].c_str());
  // }
  // printf("Aftter encode the chromosome is:\n%s\n", Chrome);
  // char DecodeBuf[8 + 1];
  // string Decoded = Chrome;
  // for (int Iter_BH = 0; Iter_BH < HexChromLength; Iter_BH++) {
  //   cout << "Substring = " << Decoded.substr(Iter_BH * 4, 4) << '\n';
  //   printf("%d: %c\n", Iter_BH, BinToHex[Decoded.substr(Iter_BH * 4, 4)]);
  //   DecodeBuf[Iter_BH] = BinToHex[Decoded.substr(Iter_BH * 4, 4)];
  // }
  // printf("After decode:\n%s\n", DecodeBuf);
  // int decodedNum;
  // sscanf(DecodeBuf, "%X", &decodedNum);
  // printf("DecodedNum=%d\n", decodedNum);
  double a = -111.23456;
  char b[28];
  Encode(a, b);
  Individual A, B;
  // printf("Encoded: %s\n", b);
  cout << Decode(b) << endl;
  printf("%f", fmod(a, 10));
  return 0;
}