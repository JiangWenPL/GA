#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
const int IterateGeneration = 100;
const double Mutation_Probability = 0.001;
const int Row_Max = 89266;
const int Col_Max = 5;
const int Individual_Max = 20000;
const int Chromosome_Legth = 28;
const int CoeffNum = 6 * 3 + 1;
const int Depend_Var = 3;
const int Cal_Fit_Num = 800;
// const int Generation_Max = 1000;
const int HexChromLength = 8;
const double Gene_Recombination_Probability = 0.5;
std::map<std::string, char> BinToHex = {
    {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
    {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
    {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
    {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}};
std::map<char, std::string> HexToBin = {
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
double Data[Row_Max][Col_Max];
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
// Global var:
Individual Unit[Individual_Max];
std::vector<Individual> BestUnit;
std::vector<Individual> WorstUnit;
int Generation = 0;
int Surive_Num = 0;
// Unit[GeneID].Coeff[0] is the constant.
// 1~6 is about x1.
bool Compare_Ind(Individual Ind1, Individual Ind2) {
  return (Ind1.Fitness < Ind2.Fitness);
}
char* Encode(double Code, char* Chrome) {
  char HexBuf[8 + 1];
  if (Code > 10 || Code < -10) Code = fmod(Code, 10);
  sprintf(HexBuf, "%07X", (int)floor(Code * 1000000));
  for (int Iter_HB = 0; Iter_HB < HexChromLength; Iter_HB++) {
    sprintf(Chrome + 4 * Iter_HB, "%s", HexToBin[HexBuf[Iter_HB]].c_str());
  }
  return Chrome;
}
double Decode(char* Chrome) {
  char DecodeBuf[8 + 1];
  memset(DecodeBuf, 0, sizeof(DecodeBuf));
  std::string Decoded = Chrome;
  for (int Iter_BH = 0; Iter_BH < HexChromLength; Iter_BH++) {
    DecodeBuf[Iter_BH] = BinToHex[Decoded.substr(Iter_BH * 4, 4)];
  }
  int decodedNum;
  sscanf(DecodeBuf, "%X", &decodedNum);
  return (decodedNum * 1.0 / 1000000);
}
double Function(const double* pCoeff, double x1, double x2, double x3) {
  return (pCoeff[0] + pCoeff[1] * exp(pCoeff[2] * x1) +
          pCoeff[3] * log(1 + x1) + pCoeff[4] * x1 + pCoeff[5] * x1 * x1 +
          pCoeff[6] * (1.0 / (1 + x1)) + pCoeff[7] * exp(pCoeff[8] * x2) +
          pCoeff[9] * log(1 + x2) + pCoeff[10] * x2 + pCoeff[11] * x2 * x2 +
          pCoeff[12] * (1.0 / (1 + x2)) + pCoeff[13] * exp(pCoeff[14] * x3) +
          pCoeff[15] * log(1 + x3) + pCoeff[16] * x3 + pCoeff[17] * x3 * x3 +
          pCoeff[18] * (1.0 / (1 + x3)));
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
  fprintf(fpCoeff, "Affter %d Generations:\n", Generation);
  for (int GeneID_WI = 0; GeneID_WI < Individual_Max;
       GeneID_WI++, pUnits_WI++) {
    fprintf(fpCoeff, "No.%3d Fitness:%f\n", GeneID_WI, pUnits_WI->Fitness);
    for (int iWI = 0; iWI < CoeffNum; iWI++) {
      fprintf(fpCoeff, "%.6f ", pUnits_WI->Coeff[iWI]);
    }
    fprintf(fpCoeff, "\n");
  }
  if (fclose(fpCoeff) != 0) return false;
  return true;
}
bool DEBUG_Write(const Individual* pDEBUG, int RangeInd, int Range_Coeff) {
  FILE* fpDEBUG = NULL;
  fpDEBUG = fopen("./DEBUG.txt", "w");
  if (fpDEBUG == NULL) return false;
  for (int GeneID_WI = 0; GeneID_WI < RangeInd; GeneID_WI++, pDEBUG++) {
    fprintf(fpDEBUG, "No.%3d Fitness:%f\n", GeneID_WI, pDEBUG->Fitness);
    for (int iWI = 0; iWI < Range_Coeff; iWI++) {
      fprintf(fpDEBUG, "%.6f ", pDEBUG->Coeff[iWI]);
    }
    fprintf(fpDEBUG, "\n");
  }
  if (fclose(fpDEBUG) != 0) return false;
  return true;
}
bool Write_Best() {
  FILE* fpBest = NULL;
  fpBest = fopen("./Best.txt", "a+");
  if (fpBest == NULL) return false;
  int cnt_WB = 0;
  for (std::vector<Individual>::iterator it_WB = BestUnit.begin();
       it_WB != BestUnit.end(); ++it_WB, ++cnt_WB) {
    fprintf(fpBest, "Generation %d Fitness:%.6f\n", cnt_WB, it_WB->Fitness);
    for (int iWB = 0; iWB < CoeffNum; iWB++) {
      fprintf(fpBest, "%.6f ", it_WB->Coeff[iWB]);
    }
    fprintf(fpBest, "\n");
  }
  if (fclose(fpBest) != 0) return false;
  return true;
}
bool Write_Fitness() {
  FILE *fpBFitness = NULL, *fpWFitness = NULL;
  fpBFitness = fopen("./Best_Fitness.txt", "a+");
  fpWFitness = fopen("./Worst_Fitness", "a+");
  if (fpBFitness == NULL || fpWFitness == NULL) return false;
  for (std::vector<Individual>::iterator it_WF_Best = BestUnit.begin();
       it_WF_Best != BestUnit.end(); ++it_WF_Best) {
    fprintf(fpBFitness, "%.6f\n", it_WF_Best->Fitness);
  }
  for (std::vector<Individual>::iterator it_WF_Worst = WorstUnit.begin();
       it_WF_Worst != WorstUnit.end(); ++it_WF_Worst) {
    fprintf(fpWFitness, "%.6f\n", it_WF_Worst->Fitness);
  }
  if (fclose(fpBFitness) != 0 || fclose(fpWFitness) != 0) return false;
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
    Rand_CF = (int)floor((1.0 * Row_Max * rand()) / RAND_MAX);
    if (Rand_CF == Row_Max) Rand_CF = Row_Max - 1;
    pCheck[Row_CF][0] = Data[Rand_CF][0];
    pCheck[Row_CF][1] = Data[Rand_CF][1];
    pCheck[Row_CF][2] = Data[Rand_CF][2];
    pCheck[Row_CF][3] = Data[Rand_CF][Depend_Var];
  }
  for (int GeneID_CF = 0; GeneID_CF < Individual_Max;
       GeneID_CF++, pUnits_CF++) {
    pUnits_CF->Fitness = 0;
    for (int i_CF = 0; i_CF < Cal_Fit_Num; i_CF++) {
      pUnits_CF->Fitness +=
          std::abs((Function(pUnits_CF->Coeff, pCheck[i_CF][0], pCheck[i_CF][1],
                             pCheck[i_CF][2])) -
                   pCheck[i_CF][3]);
      // printf("Unit[%d] the test case%d: %f\n", GeneID_CF, i_CF,
      //        std::abs((Function(pUnits_CF->Coeff, pCheck[i_CF][0],
      //                           pCheck[i_CF][1], pCheck[i_CF][2])) -
      //                 pCheck[i_CF][3]));
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
  std::sort(Temp_ind_begin, Temp_ind_begin + Individual_Max - 1, Compare_Ind);
  // Write_Individual(Temp_ind_begin);
  // DEBUG_Write(Temp_ind_begin, Individual_Max, CoeffNum);
  BestUnit.push_back(*Temp_ind_begin);
  WorstUnit.push_back(*(Temp_ind_begin + Individual_Max - 1));
  Surive_Num = 0;
  Temp_ind = Temp_ind_begin;
  for (int Sel_Id = 0; Sel_Id < Individual_Max; Sel_Id++, Temp_ind++) {
    Temp_ind->Surive = 1.0 - (1.0 / Individual_Max) * Sel_Id;
    if ((((double)rand()) / RAND_MAX) <= Temp_ind->Surive) {
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
  // DEBUG_Write(Sel_ind_Begin);
  free(Temp_ind_begin);
  free(Sel_ind_Begin);
  return Surive_Num;
}
void Gene_Mutation(Individual* pUnit_GM_Begin, int Surive_GM) {
  Individual* pUnit_GM = pUnit_GM_Begin;
  for (int it_GM = 0; it_GM < Surive_GM; it_GM++, pUnit_GM++) {
    for (int Coeff_GM = 0; Coeff_GM < CoeffNum; Coeff_GM++) {
      // Encode
      Encode(pUnit_GM->Coeff[Coeff_GM], (pUnit_GM->Chrom)[Coeff_GM]);
      // Mutation
      if (((double)rand()) / RAND_MAX < Mutation_Probability) {
        int Mutation_Index = (int)(27.0 * rand() / RAND_MAX);
        (pUnit_GM->Chrom)[Coeff_GM][Mutation_Index] =
            (pUnit_GM->Chrom)[Coeff_GM][Mutation_Index] == '0' ? '1' : '0';
      }
      // decode
      pUnit_GM->Coeff[Coeff_GM] = Decode((pUnit_GM->Chrom)[Coeff_GM]);
    }
  }
}
void Gene_Recombination(Individual* pUnit_GR_Begin, int Surive_GR) {
  Individual* pUnit_GR = pUnit_GR_Begin;
  for (int it_GR = 0; it_GR < Surive_GR; it_GR++, pUnit_GR++) {
    for (int Coeff_GR = 0; Coeff_GR < CoeffNum; Coeff_GR++) {
      // Recombination.
      if (((double)rand()) / RAND_MAX < Gene_Recombination_Probability) {
        int Recombination_Index = 1.0 * (Surive_GR - 1) * rand() / RAND_MAX;
        double Temp_Coeff = (pUnit_GR->Coeff)[Coeff_GR];
        (pUnit_GR->Coeff)[Coeff_GR] =
            (pUnit_GR_Begin[Recombination_Index]).Coeff[Coeff_GR];
        (pUnit_GR_Begin[Recombination_Index]).Coeff[Coeff_GR] = Temp_Coeff;
      }
    }
  }
}
void New_Generation(Individual* pUnit_NG_Begin, int Surive_NG) {
  int Half = Individual_Max / 2;
  if (Surive_NG < Half) {
    for (int iter_NG = Surive_NG, i_Better = 0; iter_NG < Half;
         iter_NG++, i_Better++) {
      pUnit_NG_Begin[iter_NG] = pUnit_NG_Begin[i_Better];
    }
  }
  for (int iterNG = 0; iterNG < Half; iterNG++) {
    pUnit_NG_Begin[Half + iterNG] = pUnit_NG_Begin[iterNG];
  }
}
int main() {
  srand(time(NULL));
  if (!Load_Data()) {
    printf("Error in Load Data!\n");
  }
  int order, Survival_Num;
  Init_Individual(Unit);
  do {
    for (int iter = 0; iter < IterateGeneration; iter++, Generation++) {
      Calculate_Fitness(Unit);
      Survival_Num = Selction(Unit);
      Gene_Mutation(Unit, Surive_Num);
      Gene_Recombination(Unit, Survival_Num);
      New_Generation(Unit, Surive_Num);
      printf("After %d Generations:\n", Generation);
      printf("  The Best perfom indvidual's fitness is %.6f\n",
             (BestUnit.back()).Fitness);
      printf("  The worst perfom indvidual's fitness is %.6f\n",
             (WorstUnit.back()).Fitness);
    }
    // std::cout << "Survival:" << Selction(Unit) << "\n";
    // if (!Write_Individual(Unit))
    //   printf("Error in Write individual information!\n");
    // Write_Individual(Unit);
  } while (scanf("%d", &order) && order);
  Write_Best();
  Write_Fitness();
  return 0;
}