/*
*    Tribalism.cpp
*    Cpp Project for 2017 ZJU Mathematical Modeling Contest.
*	 Team production.
*	 Team member: Jiang Wen, He Kangrui, Cao Zhefeng.
*    This file was created by Wen Jiang on May 3, 2017.
*    Copyright (c) 2017 Wen Jiang. All rights reserved.
*/

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

#define UI
// #define DEBUG
// If you want play with failure loss, define LOSE_LOST
#define LOSE_LOST

using namespace std;
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

const int MineProduct[] = {0, 120, 180, 240, 300, 360, 420, 480, 540, 600};
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
void Fight(Status *pPlayer);
void PrintStatus(Status Current) {
#ifdef UI
  puts("You current status is here:");
  printf(
      "  Mine_Level = %2d    A_Level = %2d    B_Level = %2d    C_Level = "
      "%2d\n",
      Current.Mine_Level, Current.A_Level, Current.B_Level, Current.C_Level);
  printf("  Resources Ⅰ : %6d\n", Current.Resources_First);
  printf("  Resources Ⅱ : %6d\n", Current.Resources_Second);
  printf("  Resources Ⅲ : %6d\n", Current.Resources_Third);
  printf("  Your mine can prouduce %3d units per hour\n",
         MineProduct[Current.Mine_Level]);
  printf("  Your score: %3f\n", Current.score);
  printf("You can do things below:\n");
  printf("  0: Upgrade mine, which needs %6d Resources Ⅰ\n",
         MineNeed[Mine][Current.Mine_Level]);
  if (MineNeed[Mine][Current.Mine_Level] < Current.Resources_First)
    printf("    Sufficent resouces\n");
  else
    printf("    !!! Insufficient resources\n");
  printf("  1: Upgrade buliding A, which needs %6d Resources Ⅰ\n",
         MineNeed[A][Current.Mine_Level]);
  if (MineNeed[A][Current.Mine_Level] < Current.Resources_First)
    printf("    Sufficent resouces\n");
  else
    printf("    !!! Insufficient resources\n");
  printf("  2: Upgrade buliding B, which needs %6d Resources Ⅱ\n",
         MineNeed[B][Current.Mine_Level]);
  if (MineNeed[B][Current.Mine_Level] < Current.Resources_Second)
    printf("    Sufficent resouces\n");
  else
    printf("    !!! Insufficient resources\n");
  printf("  3: Upgrade buliding B, which needs %6d Resources Ⅲ\n",
         MineNeed[C][Current.Mine_Level]);
  if (MineNeed[C][Current.Mine_Level] < Current.Resources_Third)
    printf("    Sufficent resouces\n");
  else
    printf("    !!! Insufficient resources\n");
  printf("Type index(s) of action(s) to make decision:\n");
#endif  // UI
}
int main() {
  stringstream orders;
  string buffer;
  srand((unsigned)time(NULL));
  int action = -1;
  int hour = 0;
#ifdef UI
  puts("Welcome to the world of trabalism");
#endif  // UI
  do {
    printf(
        "+++++++++++++++++++++++++++++Hour "
        "%d+++++++++++++++++++++++++++++++++\n",
        hour++);
    orders.str(buffer);
#ifdef DEBUG
    cout << "Buffer=" << buffer << endl;
#endif  // DEBUG
// buffer.clear();
#ifdef DEBUG
    orders >> action;
    cout << "Action=" << action << endl;
#endif  // DEBUG
    while ((orders >> action)) {
#ifdef DEBUG
      // cout << "Action=" << action << endl;
      printf("---------------------------------\n");
#endif  // DEBUG
      // Becuse there probablly be many orders by player
      // Using stringstream to handle it one by one.
      switch (action) {
        case Mine:  // Upgrade Mine
#ifdef UI
          puts("You choose to upgrade Mine...");
          if (MineNeed[Mine][Player.Mine_Level] < Player.Resources_First) {
            Player.Resources_First -= MineNeed[Mine][Player.Mine_Level];
            Player.Mine_Level++;
            printf("Upgrade Mine complete\n");
          } else
            puts("Eroor! Insufficinet resource Ⅰ");
#endif  // UI
          break;
        case A:
#ifdef UI
          puts("You choose to upgrade buliding A...");
          if (MineNeed[A][Player.A_Level] < Player.Resources_First) {
            Player.Resources_First -= MineNeed[A][Player.A_Level];
            Player.A_Level++;
            printf("Upgrade bulding A complete\n");
          } else
            puts("Eroor! Insufficinet resource Ⅰ");
#endif  // UI
          break;
        case B:
#ifdef UI
          puts("You choose to upgrade buliding B...");
          if (MineNeed[B][Player.B_Level] < Player.Resources_Second) {
            Player.Resources_Second -= MineNeed[B][Player.B_Level];
            Player.B_Level++;
            printf("Upgrade bulding B complete\n");
          } else
            puts("Eroor! Insufficinet resource Ⅱ");
#endif  // UI
          break;
        case C:
#ifdef UI
          puts("You choose to upgrade buliding C...");
          if (MineNeed[C][Player.C_Level] < Player.Resources_Third) {
            Player.Resources_Third -= MineNeed[C][Player.C_Level];
            Player.C_Level++;
            printf("Upgrade bulding C complete\n");
          } else
            puts("Eroor! Insufficinet resource Ⅲ");
#endif  // UI
          break;
        default:
          break;
      }
    }
    orders.clear();
    // TODO: Fight module
    Fight(&Player);
    PrintStatus(Player);
    // The gorwth of resources
    Player.Resources_First += MineProduct[Player.Mine_Level];
    Player.Resources_Second += MineProduct[Player.Mine_Level];
    Player.Resources_Third += MineProduct[Player.Mine_Level];
  } while (getline(cin, buffer));
  return 0;
}
void Fight(Status *pPlayer) {
  double random_Num = (double)(rand()) / RAND_MAX;
  double Victory_Possibilty = 0.5 + (pPlayer->C_Level - 1) * Gamma;
#ifdef UI
  puts("You are fighting with an enemy.");
  if (Victory_Possibilty > random_Num) {
    puts("Congratulations! You win");
    double winner_points = 1 + (pPlayer->B_Level - 1) * Beta;
    printf("You get %4f Points\n", winner_points);
    pPlayer->score += winner_points;
  } else {
    puts("You fail...");
#ifdef LOSE_LOST
    int Protect_1 =
        Origin_Protect_1 * (int)pow(2, (double)(pPlayer->A_Level - 1));
    int Protect_2 =
        Origin_Protect_2 * (int)pow(2, (double)(pPlayer->A_Level - 1));
    int Protect_3 =
        Origin_Protect_3 * (int)pow(2, (double)(pPlayer->A_Level - 1));
    int Lost_1 = (pPlayer->Resources_First - Protect_1 > 0)
                     ? (pPlayer->Resources_First - Protect_1) * Theta
                     : 0;
    int Lost_2 = (pPlayer->Resources_Second - Protect_2 > 0)
                     ? (pPlayer->Resources_First - Protect_2) * Theta
                     : 0;
    int Lost_3 = (pPlayer->Resources_Third - Protect_3 > 0)
                     ? (pPlayer->Resources_First - Protect_3) * Theta
                     : 0;
    pPlayer->Resources_First -= Lost_1;
    pPlayer->Resources_Second -= Lost_2;
    pPlayer->Resources_Third -= Lost_3;
    puts("Your loss:");
    printf("  Resources Ⅰ : %6d\n", Lost_1);
    printf("  Resources Ⅱ : %6d\n", Lost_2);
    printf("  Resources Ⅲ : %6d\n", Lost_3);
#endif  // For the third question about failure's lost.
  }
#endif  // UI
}