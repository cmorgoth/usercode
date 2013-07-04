#ifndef DM_DYJETS_LL
#define DM_DYJETS_LL 1

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include <math.h>

class DYJets{
  
public:
  
  static const int MR_Bins = 12;
  static const int RSQ_Bins = 19;
  //static const double sigma = 3503.71*1000.;//fb (NNLO)
  static const double sigma = 2950*1000.;//fb (LO)
  
  
  static const float Lumi = 5.;//fb^-1
  // static const float MR_Low = 150.;
  //static const float MR_High = 1000.;
  //static const float RSQ_Low = 0.5;
  //static const float RSQ_High = 1.2;
  
  static const float RSQ_BinArr[RSQ_Bins+1];
  static const float MR_BinArr[MR_Bins+1];

  
  DYJets();
  DYJets(const char* );
  
  ~DYJets();
  
  TH1F PlotMR_2Box();
  TH1F PlotMR_1Box();
  TH1F PlotMR_0Box();
  
  TH1F PlotRSQ_2Box();
  TH1F PlotRSQ_1Box();
  TH1F PlotRSQ_0Box();
  
  
  TH2F PlotRSQ_vs_MR_0Box();
  TH2F PlotRSQ_vs_MR_1Box();
  TH2F PlotRSQ_vs_MR_2Box();
  
  bool CalcWeight();
  bool PrintEvents();
  bool PrintEventsMC();

  std::vector<TH1F*> PlotMETx();
  std::vector<TH1F*> PlotMETy();
  std::vector<TH1F*> PlotHT();

  bool SetBrachStatus();

private:

  
  TTree* T;
  TFile* F;
  
  float MRMin;
  float RSQMin;
  float weight;
  
};


#endif
