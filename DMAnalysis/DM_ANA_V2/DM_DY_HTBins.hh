#ifndef DM_DY_HH_HT
#define DM_DY_HH_HT 1

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TEfficiency.h"
#include <vector>
#include <math.h>


class DY{
  
public:

  
  //static const int MR_Bins = 12;
  //static const int RSQ_Bins = 19;
  static const int MR_Bins = 6;
  static const int RSQ_Bins = 6;
  
  //static const double sigma0 = 452.75*1000.;//fb (NNLO)
  static const double sigma0 = 19.73*1000.;// (LO PREP)
  //static const double sigma1 = 190.39*1000.;//fb (NNLO)
  static const double sigma1 = 2.826*1000.;//(LO PREP)
  //static const double sigma2 = 49.28*1000.;//fb (NNLO)

  
  static const float Lumi = 5.;//fb^{-1}
  //static const float Lumi = 12.;//fb^{-1}  
  
  static const float RSQ_BinArr[RSQ_Bins+1];
  static const float MR_BinArr[MR_Bins+1];
  
  static const int btagIndex = 0;//0->Veto Btag(Loose), 1-> Btag(Loose) >=1, 2-> BtagTight >=1 
  
  DY();
  DY(int );
  DY(const char* );
  
  ~DY();
  
  TH1F PlotMR_2Box();
  TH1F PlotMR_1Box();
  TH1F PlotMR_0Box();
  
  TH1F PlotRSQ_2Box();
  TH1F PlotRSQ_1Box();
  TH1F PlotRSQ_0Box();
  
  TH2F PlotRSQ_vs_MR_0Box();
  TH2F PlotRSQ_vs_MR_1Box();
  TH2F PlotRSQ_vs_MR_2Box();
  
  std::vector<TH2F*> Plot_2DRazor();
  std::vector<TH1F*> PlotMETmag();
  
  bool PrintEvents();
  bool SetBrachStatus();

  double HLTscale(double, double);
  double HLTscaleEle(double, double);
  
private:
  
  TTree* T;//HT_200_140
  TTree* T1;//HT_400_inf
    
  TFile* F;
  TFile* F1;
    
  TH2F* hlt;
  TH2F* hlt_ele;
  TEfficiency* eff;
  TEfficiency* eff_ele;

  int metIndex;
  float MRMin;
  float RSQMin;

    
  float weight0;
  float weight1;
  
  bool fBtag[3];
  TString BtagBranch;
    
};

#endif
