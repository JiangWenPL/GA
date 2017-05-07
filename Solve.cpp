#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG_HOUR
struct Status {
  int Mine_Level;
  int A_Level;
  int B_Level;
  int C_Level;
  int Resources_First;
  int Resources_Second;
  int Resources_Third;
  double score;
  Status() {  // Constructor
    Mine_Level = 1;
    A_Level = 1;
    B_Level = 1;
    C_Level = 1;
    Resources_First = 0;
    Resources_Second = 0;
    Resources_Third = 0;
    score = 0;
  }
} Player;

const int MineProduct[] = {0, 60, 120, 180, 240, 300, 360, 420, 480, 540, 600};
// The index of array means the levael of mine.
// Count from level 1.
const int Mine = 0;
const int A = 1;
const int B = 2;
const int C = 3;
const int Origin_Protect_1 = 480;
const int Origin_Protect_2 = 720;
const int Origin_Protect_3 = 1200;
const double Beta = 0.1;
const double Gamma = 0.05;
const double Alpha = 2;
const double Theta = 0.1;
const int MineNeed[4][10] = {
    {0, 830, 1630, 4900, 14700, 51300, 97100, 194200, 388000, 776000},
    {0, 660, 1320, 2600, 5200, 9200, 16900, 38000, 76000, 228000},
    {0, 960, 2880, 5760, 8640, 17280, 51840, 86500, 173000, 519000},
    {0, 2300, 6900, 13800, 27650, 51840, 89800, 137100, 274000, 810000}};
// The 1st demision index means the kinds of buliding: Mine -> 0, A -> 1, B ->
// 2, C -> 3, etc.
// The 2nd demision index means the cureent level which has not been upgraded.
// Also count frome level 1.

int main() {
  int i, k[11], n = 1, j;  // i->mine level ,k[i]->count ,n->best mine level
  int Alevel, Blevel, Clevel;
  for (Alevel = 2; Alevel <= 10; Alevel++) {
    for (Blevel = 2; Blevel <= 10; Blevel++) {
      for (Clevel = 2; Clevel <= 10; Clevel++) {
        Player.Resources_First += MineProduct[Player.Mine_Level];
        Player.Resources_Second += MineProduct[Player.Mine_Level];
        Player.Resources_Third += MineProduct[Player.Mine_Level];

        for (i = 1; i < 11; i++) {
          for (k[i] = 1;; k[i]++) {
            if (Player.Resources_First >= MineNeed[Mine][Player.Mine_Level]) {
              Player.Resources_First -= MineNeed[Mine][Player.Mine_Level];
              Player.Mine_Level++;
            }
            if (Player.Resources_Second >= MineNeed[B][Player.B_Level]) {
              Player.Resources_Second -= MineNeed[B][Player.B_Level];
              Player.B_Level++;
            }
            if (Player.Resources_Third >= MineNeed[C][Player.C_Level]) {
              Player.Resources_Third -= MineNeed[C][Player.C_Level];
              Player.C_Level++;
            }
            if (Player.Mine_Level == i) break;

            Player.Resources_First += MineProduct[Player.Mine_Level];
            Player.Resources_Second += MineProduct[Player.Mine_Level];
            Player.Resources_Third += MineProduct[Player.Mine_Level];
          }
          for (k[i]++;; k[i]++) {
            if (Player.Resources_First >= MineNeed[A][Player.A_Level]) {
              Player.Resources_First -= MineNeed[A][Player.A_Level];
              Player.A_Level++;
            }
            if (Player.Resources_Second >= MineNeed[B][Player.B_Level]) {
              Player.Resources_Second -= MineNeed[B][Player.B_Level];
              Player.B_Level++;
            }
            if (Player.Resources_Third >= MineNeed[C][Player.C_Level]) {
              Player.Resources_Third -= MineNeed[C][Player.C_Level];
              Player.C_Level++;
            }

            if (Player.A_Level >= Alevel && Player.B_Level >= Blevel &&
                Player.C_Level >= Clevel)
              break;
            Player.Resources_First += MineProduct[Player.Mine_Level];
            Player.Resources_Second += MineProduct[Player.Mine_Level];
            Player.Resources_Third += MineProduct[Player.Mine_Level];
          }
          Player.Mine_Level = 1;
          Player.A_Level = 1;
          Player.B_Level = 1;
          Player.C_Level = 1;
          Player.Resources_First = 0;
          Player.Resources_Second = 0;
          Player.Resources_Third = 0;
        }
        for (j = 1, n = 1; j <= 10; j++) {
          if (k[j] < k[n]) n = j;
        }
        printf(
            "Alevel=%d,Blevel=%d,Clevel=%d best mine level is %d , count is "
            "%d\n",
            Alevel, Blevel, Clevel, n, k[n]);
        printf("\n");
      }
    }
  }
//   getchar();
//   getchar();
  return 0;
}
