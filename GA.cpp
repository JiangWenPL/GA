#include <cctype>
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
const int Row_Max = 89266;
const int Col_Max = 5;
const int Individual_Max = 200;
const int Chromosome_Legth = 24;
const int Individual_Number = 200;
const int CoeffNum = 6 * 3 + 1;
const int Depend_Var = 4;
const int Cal_Fit_Num = 800;
const int Generation_Max = 1000;
double Data[Row_Max][Col_Max];
struct Individual {
  char Chrom[6 * 3 + 1][Chromosome_Legth + 1];
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
bool Compare_Ind(Individual* pInd1, Individual* pInd2) {
  return (pInd1->Fitness < pInd2->Fitness);
}
// Global var:
Individual Unit[Individual_Max];
Individual BestUnit[Generation_Max];
int Generation = 0;
int Surive_Num = 0;
// Unit[GeneID].Coeff[0] is the constant.
// 1~6 is about x1.
double Function(const double* pCoeff, double x1, double x2, double x3) {
  return (pCoeff[0] + pCoeff[1] * exp(pCoeff[2] * x1) +
          pCoeff[3] * log(pCoeff[4] * x1) + pCoeff[5] * x1 +
          pCoeff[6] * (1.0 / x1) + pCoeff[7] * exp(pCoeff[8] * x2) +
          pCoeff[9] * log(pCoeff[10] * x2) + pCoeff[11] * x2 +
          pCoeff[12] * (1.0 / x2) + pCoeff[13] * exp(pCoeff[14] * x3) +
          pCoeff[15] * log(pCoeff[16] * x3) + pCoeff[17] * x3 +
          pCoeff[18] * (1.0 / x3));
}
bool Load_Data() {
  FILE* fpData = NULL;
  fpData = fopen("./Data.txt", "r");
  if (fpData == NULL) return false;
  for (int i = 0; i < Row_Max; i++) {
    for (int j = 0; j < Col_Max; j++) {
      fscanf(fpData, "%lf", &Data[i][j]);
    }
  }
  if (fclose(fpData) != 0) return false;
  return true;
}
bool Write_Individual(const Individual* pUnits_WI) {
  FILE* fpCoeff = NULL;
  fpCoeff = fopen("./Coeff.txt", "a+");
  if (fpCoeff == NULL) return false;
  for (int GeneID_WI = 0; GeneID_WI < Individual_Max;
       GeneID_WI++, pUnits_WI++) {
    fprintf(fpCoeff, "No.%3d Fitness:%f\n", GeneID_WI, pUnits_WI->Fitness);
    for (int iWI = 0; iWI < CoeffNum; iWI++) {
      fprintf(fpCoeff, "%f ", pUnits_WI->Coeff[iWI]);
    }
    fprintf(fpCoeff, "\n");
  }
  if (fclose(fpCoeff) != 0) return false;
  return true;
}
void Init_Individual(Individual* pUnits_II) {
  for (int GeneID_II = 0; GeneID_II < Individual_Max;
       GeneID_II++, pUnits_II++) {
    for (int iII = 0; iII < CoeffNum; iII++) {
      pUnits_II->Coeff[iII] = (4.0 * rand() / RAND_MAX) - 2;
    }
  }
}
void Calculate_Fitness(Individual* pUnits_CF) {
  double(*pCheck)[4] = (double(*)[4])malloc(sizeof(double) * Cal_Fit_Num * 4);
  for (int Row_CF = 0, Rand_CF = 0; Row_CF < Cal_Fit_Num; Row_CF++) {
    Rand_CF = (int)floor((1.0 * Row_Max * rand() / RAND_MAX));
    if (Rand_CF == Row_Max) Rand_CF = Row_Max - 1;
    pCheck[Row_CF][0] = Data[Rand_CF][0];
    pCheck[Row_CF][1] = Data[Rand_CF][2];
    pCheck[Row_CF][2] = Data[Rand_CF][3];
    pCheck[Row_CF][3] = Data[Rand_CF][Depend_Var];
  }
  for (int GeneID_CF = 0; GeneID_CF < Individual_Max;
       GeneID_CF++, pUnits_CF++) {
    pUnits_CF->Fitness = 0;
    for (int i_CF = 0; i_CF < Cal_Fit_Num; i_CF++) {
      pUnits_CF->Fitness = pow((Function(pUnits_CF->Coeff, pCheck[i_CF][0],
                                         pCheck[i_CF][1], pCheck[i_CF][2])) -
                                   pCheck[i_CF][3],
                               2);
    }
  }
  free(pCheck);
}
int Selction(Individual* pUnits_CF) {
  // Nature selction

  Individual* Temp_ind_begin =
      (Individual*)malloc(sizeof(Individual) * Individual_Max);
  Individual* Sel_ind_Begin =
      (Individual*)malloc(sizeof(Individual) * Individual_Max);
  Individual* Sel_ind = Sel_ind_Begin;
  Individual* pIter = pUnits_CF;
  Individual* Temp_ind = Temp_ind_begin;
  for (int Cp_Id = 0; Cp_Id < Individual_Max; Cp_Id++, Temp_ind++, pIter++) {
    *Temp_ind = *pIter;
  }
  std::sort(Temp_ind, Temp_ind + Individual_Max - 1, Compare_Ind);
  Surive_Num = 0;
  for (int Sel_Id = 0; Sel_Id < Individual_Max; Sel_Id++, Temp_ind++) {
    Temp_ind->Surive = 1.0 - 0.005 * Sel_Id;
    if ((rand() / RAND_MAX) <= Temp_ind->Surive) {
      Surive_Num++;
      Temp_ind->Alive = true;
      *Sel_ind = *Temp_ind;
      Sel_ind++;
    } else {
      Temp_ind->Alive = false;
    }
  }
  pIter = pUnits_CF;
  Individual* Sel_Iter = Sel_ind_Begin;
  for (int Cp_Id = 0; Cp_Id < Surive_Num; Cp_Id++, pIter++, Sel_Iter++) {
    *pIter = *Sel_Iter;
  }
  free(Temp_ind_begin);
  free(Sel_ind_Begin);
  return Surive_Num;
}
void Gene_Encoude(Individual* pUnits_GE, int Surive_Num) { ; }
int main() {
  srand(time(NULL));
  if (!Load_Data()) {
    printf("Error in Load Data!\n");
  }
  // if(!Write_Individual(Unit))
  //   printf("Error in Write individual information!\n");
  return 0;
}