#ifndef DM_BASE_HH
#define DM_BASE_HH 1

#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TEfficiency.h"
#include <vector>
#include <map>
#include  <string>
#include <stdio.h>
#include <math.h>
//#include <iostream>
#include <sstream>
#include <fstream>
//using namespace std;

//Base Dark Matter Analysis Class
//Every other class (for each individual bkg channel and Data ) inherits from this one
//Defines de metods and constants commom for all the channels
//Baseline cuts, plots for MR and RSQ in different signal and control samples


class BaseDM{
  
public:
  
  //static const int MR_Bins = 12;
  //static const int RSQ_Bins = 19;
  static const int MR_Bins = 6;
  static const int RSQ_Bins = 6;

  static const float Lumi = 5.;//fb^-1
  //static const float Lumi = 12.;//fb^-1 
  
  static const double RSQ_BinArr[RSQ_Bins+1];
  static const double MR_BinArr[MR_Bins+1];
  
  static const int btagIndex = 0;//0->Veto Btag(Loose), 1-> Btag(Loose) >=1, 2-> BtagTight >=1
  
  BaseDM();
  BaseDM( const char*, TString , int);//constructor for Data
  BaseDM( const char*, TString, float, int );//constructor for MC
  
  ~BaseDM();
  
  virtual TH1F PlotMR_2Box();
  virtual TH1F PlotMR_1Box();
  virtual TH1F PlotMR_0Box();
  
  virtual TH1F PlotRSQ_2Box();
  virtual TH1F PlotRSQ_1Box();
  virtual TH1F PlotRSQ_0Box();
  
  virtual TH2F PlotRSQ_vs_MR_0Box(TH2F* );
  virtual TH2F PlotRSQ_vs_MR_1Box(TH2F* );
  virtual TH2F PlotRSQ_vs_MR_2Box(TH2F* );

  virtual std::vector<TH2F*> Plot_2DRazor();
  
  virtual bool CalcWeight();
  virtual bool PrintEvents();
  virtual double GetWeight(){return weight;};

  virtual std::vector<TH1F*> PlotMETx();
  virtual std::vector<TH1F*> PlotMETy();
  virtual std::vector<TH1F*> PlotMETmag();
  virtual std::vector<TH1F*> PlotMETphi(){};
  
  virtual std::vector<TH1F*> PlotHT();
  virtual std::vector<TH1F*> PlotMHTmag(){};
  virtual std::vector<TH1F*> PlotMHTphi(){};
  
  //virtual bool FillVecBadHcalEvents();
  
  virtual bool SetBrachStatus();

  virtual double HLTscale(double, double);
  virtual double HLTscaleEle(double, double);
  
private:
  TTree* T;
  TFile* F;
  
  TH2F* hlt;
  TH2F* hlt_ele;

  TEfficiency* eff;
  TEfficiency* eff_ele;
  
  int metIndex;//0, 1, 2, 3 (2: type1 pfMET Correction)
  float MRMin;
  float RSQMin;
  float weight;
  float sigma;
  TString processName;
  bool fBtag[3];
  TString BtagBranch;

  //std::map< std::string, bool > HcalBadRuns;
  //std::stringstream ss;

  //bool isData;

  
  
};



#endif
