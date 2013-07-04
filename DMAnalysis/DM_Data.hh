#ifndef DM_DATA
#define DM_DATA 1

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include <math.h>

class Data{
  
public:
  
  static const int MR_Bins = 12;
  static const int RSQ_Bins = 19;
  //static const double sigma = 3503.71*1000.;//fb
  //static const double sigma = 350.*1000.;//fb
  
  //static const float Lumi = 12.;//fb^-1
  // static const float MR_Low = 150.;
  //static const float MR_High = 1000.;
  //static const float RSQ_Low = 0.5;
  //static const float RSQ_High = 1.2;
  
  static const float RSQ_BinArr[RSQ_Bins+1];
  static const float MR_BinArr[MR_Bins+1];

  
  Data();
  Data(const char* );
  
  ~Data();
  
  TH1F PlotMR_2Box();
  TH1F PlotMR_1Box();
  TH1F PlotMR_0Box();
  
  TH1F PlotRSQ_2Box();
  TH1F PlotRSQ_1Box();
  TH1F PlotRSQ_0Box();
  
  
  TH2F PlotRSQ_vs_MR_0Box();
  TH2F PlotRSQ_vs_MR_1Box();
  TH2F PlotRSQ_vs_MR_2Box();
  
  //bool CalcWeight();
  bool PrintEvents();
  bool SetBrachStatus();

  std::vector<TH1F*> PlotMETx();
  std::vector<TH1F*> PlotMETy();
  std::vector<TH1F*> PlotHT();
  
private:

  
  TTree* T;
  TFile* F;
  
  float MRMin;
  float RSQMin;
  float weight;
  
};


#endif
