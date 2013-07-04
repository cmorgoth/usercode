#ifndef DM_WJetsHTBins_HH
#define DM_WJetsHTBins_HH 1

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TEfficiency.h"
#include <vector>
#include <math.h>


class WJetsHTBins{
  
public:
  
  //static const int MR_Bins = 12;
  //static const int RSQ_Bins = 19;
  static const int MR_Bins = 6;
  static const int RSQ_Bins = 6;
  
  static const double sigma0 = 235.6*1000.;//fb (NNLO)
  //static const double sigma0 = 514.0*1000.;// (LO PREP)Possible 235.6pb
  static const double sigma1 = 90.27*1000.;//fb (NNLO)
  //static const double sigma1 = 237.0*1000.;//(LO PREP)Possible 90.27pb
  static const double sigma2 = 48.01*1000.;//fb (NNLO)
  // static const double sigma2 = 123.35*1000.;//fb (LO PREP)Possible 48.01pb
  //static const double sigma3 = 6.26*1000.;//fb (NNLO)
  static const double sigma3 = 38.3*1000.;//fb (LO PREP)
  static const double sigma4 = 25.22*1000.;//fb (LO PREP)
  
  static const float Lumi = 5.;//fb^{-1}
  //static const float Lumi = 12.;//fb^{-1}  
  
  static const int btagIndex = 0;//0->Veto Btag(Loose), 1-> Btag(Loose) >=1, 2-> BtagTight >=1
  
  static const float RSQ_BinArr[RSQ_Bins+1];
  static const float MR_BinArr[MR_Bins+1];
  
  
  WJetsHTBins();
  WJetsHTBins(int );
  WJetsHTBins(const char* );
  
  ~WJetsHTBins();
  
  TH1F PlotMR_1Box();
  TH1F PlotMR_0Box();
  
  TH1F  PlotRSQ_1Box();
  TH1F PlotRSQ_0Box();
  
  TH2F PlotRSQ_vs_MR_0Box();
  TH2F PlotRSQ_vs_MR_1Box();
  
  std::vector<TH2F*> Plot_2DRazor();
  std::vector<TH1F*> PlotMETmag();

  bool PrintEvents();
  bool SetBrachStatus();

  double HLTscale(double, double);
  double HLTscaleEle(double, double);

private:
  
  TTree* T;//HT_150_200
  TTree* T1;//HT_200_250
  TTree* T2;//HT_250_300
  TTree* T3;//HT_300_400
  TTree* T4;//HT_400_inf
  
  TFile* F;
  TFile* F1;
  TFile* F2;
  TFile* F3;
  TFile* F4;

  TH2F* hlt;
  TH2F* hlt_ele;
  TEfficiency* eff;
  TEfficiency* eff_ele;
  
  int metIndex;
  float MRMin;
  float RSQMin;

    
  float weight0;
  float weight1;
  float weight2;
  float weight3;
  float weight4;

  bool fBtag[3];
  TString BtagBranch;
  
};

#endif
