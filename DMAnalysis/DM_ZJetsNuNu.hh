#ifndef DM_ZJETS_NUNU
#define DM_ZTETS_NUNU 1

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include <math.h>


class ZJetsNuNu{
  
public:

  
  static const int MR_Bins = 12;
  static const int RSQ_Bins = 19;

  
  //static const double sigma0 = 452.75*1000.;//fb (NNLO)
  static const double sigma0 = 381.2*1000.;// (LO PREP)
  //static const double sigma1 = 190.39*1000.;//fb (NNLO)
  static const double sigma1 = 160.3*1000.;//(LO PREP)
  //static const double sigma2 = 49.28*1000.;//fb (NNLO)
  static const double sigma2 = 41.49*1000.;//fb (LO PREP)
  //static const double sigma3 = 6.26*1000.;//fb (NNLO)
  static const double sigma3 = 5.274*1000.;//fb (LO PREP)
  
  static const float Lumi = 5.;//fb^{-1}
  
  static const float RSQ_BinArr[RSQ_Bins+1];
  static const float MR_BinArr[MR_Bins+1];
  
  
  ZJetsNuNu();
  ZJetsNuNu(const char* );
  
  ~ZJetsNuNu();
  
  TH1F PlotMR_1Box();
  TH1F PlotMR_0Box();
  
  TH1F  PlotRSQ_1Box();
  TH1F PlotRSQ_0Box();
  
  TH2F PlotRSQ_vs_MR_0Box();
  TH2F PlotRSQ_vs_MR_1Box();

  bool PrintEvents();
  bool SetBrachStatus();

private:
  
  TTree* T;//HT_50_100
  TTree* T1;//HT_100_200
  TTree* T2;//HT_200_400
  TTree* T3;//HT_400_inf
  
  TFile* F;
  TFile* F1;
  TFile* F2;
  TFile* F3;
  

  float MRMin;
  float RSQMin;

    
  float weight0;
  float weight1;
  float weight2;
  float weight3;
  
};



#endif
