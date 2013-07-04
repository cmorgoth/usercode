#ifndef DM_WJETS_HH
#define DM_WJETS_HH 1

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include <stdio.h>
#include <math.h>
//using namespace std;

class WJets{
  
public:
  
  static const int MR_Bins = 12;
  static const int RSQ_Bins = 19;
  //static const double sigma = 36257.2*1000.;//fb (NNLO)
  static const double sigma = 30400*1000.;//fb (LO)
  
  
  static const float Lumi = 5.;//fb^-1

  // static const float MR_Low = 150.;
  //static const float MR_High = 1000.;
  //static const float RSQ_Low = 0.5;
  //static const float RSQ_High = 1.2;
  
  static const float RSQ_BinArr[RSQ_Bins+1];
  static const float MR_BinArr[MR_Bins+1];

   
  
  WJets();
  WJets(const char* );
  
  ~WJets();
  
  TH1F PlotMR_1Box();
  TH1F PlotMR_0Box();
  
  TH1F  PlotRSQ_1Box();
  TH1F PlotRSQ_0Box();
  
  TH2F PlotRSQ_vs_MR_0Box();
  TH2F PlotRSQ_vs_MR_1Box();
  
  bool  CalcWeight();
  bool PrintEvents();

  std::vector<TH1F*> PlotMETx();
  std::vector<TH1F*> PlotMETy();
  std::vector<TH1F*> PlotMETmag();
  std::vector<TH1F*> PlotMETphi();
  
  std::vector<TH1F*> PlotHT();
  std::vector<TH1F*> PlotMHTmag();
  std::vector<TH1F*> PlotMHTphi();

  bool SetBrachStatus();
  
private:
  
  TTree* T;
  TFile* F;

  float MRMin;
  float RSQMin;
  float weight;
  
};



#endif
