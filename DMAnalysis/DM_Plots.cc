#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include <list>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TProfile.h>
#include <TVector.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <TBranch.h>
//#include <RooRealVar.h>
//#include <RooDataSet.h>
#include <TRandom3.h>
#include <TDatime.h>
#include <TLatex.h>
#include <TColor.h>
#include <TStyle.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TF1.h>
#include <TColorWheel.h>

void setstyle(int istyle);

vector<char*> title;

TColor *icolor[9][2];
int color_list[4][10];
int style_list[4][10];

double L = 5.; //integrated luminosity in fb^{-1}
double LUMI = 5.;
double ZJets_CrossSection = 3532.8149*TMath::Power(10,3);
//double WJets_CrossSection = 37509.0*TMath::Power(10,3);//Was before
//double WJets_CrossSection = 36257.2*TMath::Power(10,3);//8TeV
double WJets_CrossSection = 31314.2*TMath::Power(10,3);//7TeV
double TTBar_CrossSection = 225.1967*TMath::Power(10,3);//fb
double ZNuNu1_CrossSection = 381.2*1.2*TMath::Power(10,3);
double ZNuNu2_CrossSection = 160.3*1.2*TMath::Power(10,3);
double ZNuNu3_CrossSection = 41.49*1.2*TMath::Power(10,3);
double ZNuNu4_CrossSection = 5.274*1.2*TMath::Power(10,3);

void VarBin_MC() {

  setstyle(0);

  //Int_t MR_Bin_Entries = 5;
  //Int_t RSQ_Bin_Entries = 5;
  Int_t MR_Bin_Entries = 200;
  Int_t RSQ_Bin_Entries = 200;
  int MRBin = 40;
  int RSQBin = 40;
  Double_t mRbin[5] = {150, 300, 500, 1000, 3000};
  Double_t RsqBin[5] = {0.5, 0.6, 0.9, 1.2, 1.8};
  
  Double_t RSQ_, MR_;
  Int_t nBtagLoose_, nBtagTight_, N_Jets_, BOX_NUM_;

  //TFile *ZJets_File = new TFile("MonteCarlo/DYJets_MonteCarlo/DYJets_Final.root");
  TFile *ZJets_File = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/out/DYJETS_DM.root");//Cristian Files
  TFile *WJets_File = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/out/WJETS_DM.root");//Cristian Files
  //TFile *TTBar_File = new TFile("MonteCarlo/TTBar_MonteCarlo/TTJets_Final.root");
  TFile *TTBar_File = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/out/TTJETS_DM.root");//Cristian Files
  //TFile *Data_File = new TFile("HTMHTRun2012_Total.root");//Waiting for Data

  //TFile *ZNuNu_File1 = new TFile("MonteCarlo/Znn_MonteCarlo/Processed_Znn_Files/ZJetsToNuNu50HT100.root");//No MC yet
  //TFile *ZNuNu_File2 = new TFile("MonteCarlo/Znn_MonteCarlo/Processed_Znn_Files/ZJetsToNuNu100HT200.root");//No MC yet
  //TFile *ZNuNu_File3 = new TFile("MonteCarlo/Znn_MonteCarlo/Processed_Znn_Files/ZJetsToNuNu200HT400.root");//No MC yet
  //TFile *ZNuNu_File4 = new TFile("MonteCarlo/Znn_MonteCarlo/Processed_Znn_Files/ZJetsToNuNu400HTinf.root");//No MC yet

  
  TTree *ZJets_Tree = (TTree*)ZJets_File->Get("outTree");
  TTree *WJets_Tree = (TTree*)WJets_File->Get("outTree");
  TTree *TTBar_Tree = (TTree*)TTBar_File->Get("outTree");
  //TTree *ZJets_Tree = (TTree*)ZJets_File->Get("outTree;2");
  //TTree *WJets_Tree = (TTree*)WJets_File->Get("outTree;2");
  //TTree *TTBar_Tree = (TTree*)TTBar_File->Get("outTree;2");
  //TTree *Data_Tree = (TTree*)Data_File->Get("outTree;2");
  //TTree *ZNuNu_Tree1 = (TTree*)ZNuNu_File1->Get("outTree;2");
  //TTree *ZNuNu_Tree2 = (TTree*)ZNuNu_File2->Get("outTree;2");

  //TTree *ZNuNu_Tree3 = (TTree*)ZNuNu_File3->Get("outTree;2");
  //TTree *ZNuNu_Tree4 = (TTree*)ZNuNu_File4->Get("outTree;2");

  TTree *ZJets_Eff = (TTree*)ZJets_File->Get("effTree");
  TTree *WJets_Eff = (TTree*)WJets_File->Get("effTree");
  TTree *TTBar_Eff = (TTree*)TTBar_File->Get("effTree");
  //TTree *ZNuNu_Eff1 = (TTree*)ZNuNu_File1->Get("effTree");
  //TTree *ZNuNu_Eff2 = (TTree*)ZNuNu_File2->Get("effTree");
  //TTree *ZNuNu_Eff3 = (TTree*)ZNuNu_File3->Get("effTree");
  //TTree *ZNuNu_Eff4 = (TTree*)ZNuNu_File4->Get("effTree");

  Int_t N_Entries_ZJets = ZJets_Tree->GetEntries();
  Int_t N_Entries_WJets = WJets_Tree->GetEntries();
  Int_t N_Entries_TTBar = TTBar_Tree->GetEntries();
  //Int_t N_Entries_Data = Data_Tree->GetEntries();
  //Int_t N_Entries_ZNuNu1 = ZNuNu_Tree1->GetEntries();
  //Int_t N_Entries_ZNuNu2 = ZNuNu_Tree2->GetEntries();
  //Int_t N_Entries_ZNuNu3 = ZNuNu_Tree3->GetEntries();
  //Int_t N_Entries_ZNuNu4 = ZNuNu_Tree4->GetEntries();

  Double_t Weight_ZJets, Weight_WJets, Weight_TTBar, Weight_ZNuNu1, Weight_ZNuNu2, Weight_ZNuNu3, Weight_ZNuNu4;
  Double_t Ntot_ZJets = 0.0;
  Double_t Ntot_WJets = 0.0;
  Double_t Ntot_TTBar = 0.0;
  Double_t Ntot_ZNuNu1 = 0.0;
  Double_t Ntot_ZNuNu2 = 0.0;
  Double_t Ntot_ZNuNu3 = 0.0;
  Double_t Ntot_ZNuNu4 = 0.0;
  Double_t Npassed_In_;
  Double_t ZJets_Background = 0.0;
  Double_t WJets_Background = 0.0;


  
  //WJETS bkg variables for ttbar boxes and no btag boxes
  double WJ_Bkg_0Mu = .0;
  double WJ_Bkg_1Mu = .0;
  double WJ_Bkg_2Mu = .0;
  
  double WJ_TTBOX_0Mu = .0;
  double WJ_TTBOX_1Mu = .0;
  double WJ_TTBOX_2Mu = .0;
  
  ////////////////////////////////////////////////////////////
  //TTbar bkg variables for ttbar boxes and no btag boxes
  double TTBar_Bkg_0Mu = .0;
  double TTBar_Bkg_1Mu = .0;
  double TTBar_Bkg_2Mu = .0;
  
  double TTBar_TTBOX_0Mu = .0;
  double TTBar_TTBOX_1Mu = .0;
  double TTBar_TTBOX_2Mu = .0;
  
  ////////////////////////////////////////////////////////////
  Double_t Data_Count = 0.0;

  ZJets_Eff->SetBranchAddress("Npassed_In",&Npassed_In_);
  WJets_Eff->SetBranchAddress("Npassed_In",&Npassed_In_);
  TTBar_Eff->SetBranchAddress("Npassed_In",&Npassed_In_);
  //ZNuNu_Eff1->SetBranchAddress("Npassed_In",&Npassed_In_);
  //ZNuNu_Eff2->SetBranchAddress("Npassed_In",&Npassed_In_);
  //ZNuNu_Eff3->SetBranchAddress("Npassed_In",&Npassed_In_);
  //ZNuNu_Eff4->SetBranchAddress("Npassed_In",&Npassed_In_);

  for (Int_t i = 0; i < ZJets_Eff->GetEntries(); i++) {
    ZJets_Eff->GetEntry(i);
    Ntot_ZJets += Npassed_In_;
  }

  for (Int_t i = 0; i < WJets_Eff->GetEntries(); i++) {
    WJets_Eff->GetEntry(i);
    Ntot_WJets += Npassed_In_;
  }

  for (Int_t i = 0; i < TTBar_Eff->GetEntries(); i++) {
    TTBar_Eff->GetEntry(i);
    Ntot_TTBar += Npassed_In_;
  }
  std::cout << "===============Ngen Events:" << Ntot_TTBar << std::endl;
  
  /*
  for (Int_t i = 0; i < ZNuNu_Eff1->GetEntries(); i++) {
    ZNuNu_Eff1->GetEntry(i);
    Ntot_ZNuNu1 += Npassed_In_;
  }

  for (Int_t i = 0; i < ZNuNu_Eff2->GetEntries(); i++) {
    ZNuNu_Eff2->GetEntry(i);
    Ntot_ZNuNu2 += Npassed_In_;
  }  

  for (Int_t i = 0; i < ZNuNu_Eff3->GetEntries(); i++) {
    ZNuNu_Eff3->GetEntry(i);
    Ntot_ZNuNu3 += Npassed_In_;
  } 
  
  for (Int_t i = 0; i < ZNuNu_Eff4->GetEntries(); i++) {
    ZNuNu_Eff4->GetEntry(i);
    Ntot_ZNuNu4 += Npassed_In_;
  }
  */
  
  Weight_ZJets = ZJets_CrossSection/(double(Ntot_ZJets));
  Weight_WJets = WJets_CrossSection/(double(Ntot_WJets));
  Weight_TTBar = TTBar_CrossSection/(double(Ntot_TTBar));

  std::cout << "===============SCALE FACTOR:" << L*Weight_TTBar << std::endl;
 
  //Weight_ZNuNu1 = ZNuNu1_CrossSection/(double(Ntot_ZNuNu1));
  //Weight_ZNuNu2 = ZNuNu2_CrossSection/(double(Ntot_ZNuNu2));
  //Weight_ZNuNu3 = ZNuNu3_CrossSection/(double(Ntot_ZNuNu3));
  //Weight_ZNuNu4 = ZNuNu4_CrossSection/(double(Ntot_ZNuNu4));
  
  //TH2D *ZJets_0MuBox_MC = new TH2D("2D Hist Plot 0","R-M_{R} Parameter Space - Data 0", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *ZJets_1MuBox_MC = new TH2D("2D Hist Plot 1","R-M_{R} Parameter Space - Data 1", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *WJets_0MuBox_MC = new TH2D("2D Hist Plot 2","R-M_{R} Parameter Space - Data 2", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *WJets_1MuBox_MC = new TH2D("2D Hist Plot 3","R-M_{R} Parameter Space - Data 3", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *TTBar_0MuBox_MC = new TH2D("2D Hist Plot 4","R-M_{R} Parameter Space - Data 4", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *TTBar_1MuBox_MC = new TH2D("2D Hist Plot 5","R-M_{R} Parameter Space - Data 5", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *MC_0Mu = new TH2D("2D Hist Plot 6","R-M_{R} Parameter Space - Data 6", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin); 
  //TH2D *MC_1Mu = new TH2D("2D Hist Plot 7","R-M_{R} Parameter Space - Data 7", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *MC_2Mu = new TH2D("2D Hist Plot 8","R-M_{R} Parameter Space - Data 8", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  //TH2D *MC_TTBar = new TH2D("2D Hist Plot 9","R-M_{R} Parameter Space - Data 9", MR_Bin_Entries-1, mRbin, RSQ_Bin_Entries-1, RsqBin);
  
  TH2D *TTBar_0MuBox_MC = new TH2D("2D Hist Plot 4","R-M_{R} Parameter Space - Data 4", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D *TTBar_1MuBox_MC = new TH2D("2D Hist Plot 5","R-M_{R} Parameter Space - Data 5", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D* ZJets_0MuBox_MC = new TH2D("2D Hist Plot 0","R-M_{R} Parameter Space - Data 5", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D* ZJets_1MuBox_MC = new TH2D("2D Hist Plot 1","R-M_{R} Parameter Space - Data 5", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D* WJets_0MuBox_MC = new TH2D("2D Hist Plot 2","R-M_{R} Parameter Space - Data 5", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D* WJets_1MuBox_MC = new TH2D("2D Hist Plot 3","R-M_{R} Parameter Space - Data 5", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D *MC_0Mu = new TH2D("2D Hist Plot 6","R-M_{R} Parameter Space - Data 6", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5); 
  TH2D *MC_1Mu = new TH2D("2D Hist Plot 7","R-M_{R} Parameter Space - Data 7", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D *MC_2Mu = new TH2D("2D Hist Plot 8","R-M_{R} Parameter Space - Data 8", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);
  TH2D *MC_TTBar = new TH2D("2D Hist Plot 9","R-M_{R} Parameter Space - Data 9", MR_Bin_Entries-1, 0, 1500, RSQ_Bin_Entries-1, 0, 1.5);

  
  TH1F* MC_TT_JetMult_0btag_0Mu = new TH1F("MC_TT_JetMult_0btag_0Mu", "TTbar Jet Multiplicity Zero Btag 0 mu", 7, 0, 7);
  TH1F* MC_TT_JetMult_0btag_1Mu = new TH1F("MC_TT_JetMult_0btag_1Mu", "TTbar Jet Multiplicity Zero Btag 1 mu", 7, 0, 7);
  TH1F* MC_TT_JetMult_0btag_2Mu = new TH1F("MC_TT_JetMult_0btag_2Mu", "TTbar Jet Multiplicity Zero Btag 2mu", 7, 0, 7);
  
  TH1F* MC_TT_JetMult_2btag_0Mu = new TH1F("MC_TT_JetMult_2btag_0Mu", "TTbar Jet Multiplicity Two Btag 0 muon", 7, 0, 7);
  TH1F* MC_TT_JetMult_2btag_1Mu = new TH1F("MC_TT_JetMult_2btag_1Mu", "TTbar Jet Multiplicity Two Btag 1 muon", 7, 0, 7);
  TH1F* MC_TT_JetMult_2btag_2Mu = new TH1F("MC_TT_JetMult_2btag_2Mu", "TTbar Jet Multiplicity Two Btag 2 muon", 7, 0, 7);
  
  //MR and RSQ for TTbar

  TH1F* MR_0Mu_0btag = new TH1F("MR_0Mu_0btag", "TTbar 0 Muon 0 Btag MR", MRBin, 0, 1500);
  TH1F* RSQ_0Mu_0btag = new TH1F("RSQ_0Mu_0btag", "TTbar 0 Muon 0 Btag R^{2}", RSQBin, 0, 1.5);
  
  TH1F* MR_0Mu_2btag = new TH1F("MR_0Mu_2btag", "TTbar 0 Muon 2 Btag MR", MRBin, 0, 1500);
  TH1F* RSQ_0Mu_2btag = new TH1F("RSQ_0Mu_2btag", "TTbar 0 Muon 2 Btag R^{2}", RSQBin, 0, 1.5);
  
  TH1F* MR_0Mu_2btag_weight = new TH1F("MR_0Mu_2btag_weight", "TTbar 0 Muon 2 Btag MR Weighted", MRBin, 0, 1500);
  TH1F* RSQ_0Mu_2btag_weight = new TH1F("RSQ_0Mu_2btag_weight", "TTbar 0 Muon 2 Btag R^{2} Weighted", RSQBin, 0, 1.5);
  
  TH1F* MultRatio_0mu = new TH1F("MultRatio_0mu","One to Zero Btag Ratio",7,0,7);
  TH1F* MultRatio_1mu = new TH1F("MultRatio_1mu","One to Zero Btag Ratio",7,0,7);
  TH1F* MultRatio_2mu = new TH1F("MultRatio_2mu","One to Zero Btag Ratio",7,0,7);
  
  TH1F* TwoBtag_0mu_to1mu = new TH1F("MultRatio_0to1","One to Zero Btag Ratio",7,0,7);
  TH1F* TwoBtag_0mu_to2mu = new TH1F("MultRatio_0to2","One to Zero Btag Ratio",7,0,7);
  TH1F* TwoBtag_1mu_to2mu = new TH1F("MultRatio_1to2","One to Zero Btag Ratio",7,0,7);
  
  ZJets_Tree->SetBranchAddress("RSQ",&RSQ_);
  ZJets_Tree->SetBranchAddress("MR",&MR_);
  ZJets_Tree->SetBranchAddress("BOX_NUM",&BOX_NUM_);
  
  WJets_Tree->SetBranchAddress("RSQ",&RSQ_);
  WJets_Tree->SetBranchAddress("MR",&MR_);
  WJets_Tree->SetBranchAddress("BOX_NUM",&BOX_NUM_);

  TTBar_Tree->SetBranchAddress("RSQ",&RSQ_);
  TTBar_Tree->SetBranchAddress("MR",&MR_);
  TTBar_Tree->SetBranchAddress("nBtag",&nBtagLoose_);
  TTBar_Tree->SetBranchAddress("nBtagTight",&nBtagTight_);
  TTBar_Tree->SetBranchAddress("BOX_NUM",&BOX_NUM_);
  TTBar_Tree->SetBranchAddress("N_Jets",&N_Jets_);
  
  //ZNuNu_Tree1->SetBranchAddress("RSQ",&RSQ_);
  //ZNuNu_Tree1->SetBranchAddress("MR",&MR_);
  //ZNuNu_Tree1->SetBranchAddress("BOX_NUM",&BOX_NUM_);
  
  //ZNuNu_Tree2->SetBranchAddress("RSQ",&RSQ_);
  //ZNuNu_Tree2->SetBranchAddress("MR",&MR_);
  //ZNuNu_Tree2->SetBranchAddress("BOX_NUM",&BOX_NUM_);
  
  //ZNuNu_Tree3->SetBranchAddress("RSQ",&RSQ_);
  //ZNuNu_Tree3->SetBranchAddress("MR",&MR_);
  //ZNuNu_Tree3->SetBranchAddress("BOX_NUM",&BOX_NUM_);
  
  //ZNuNu_Tree4->SetBranchAddress("RSQ",&RSQ_);
  //ZNuNu_Tree4->SetBranchAddress("MR",&MR_);
  //ZNuNu_Tree4->SetBranchAddress("BOX_NUM",&BOX_NUM_);
  
  for(Int_t i = 1; i < N_Entries_WJets; i++) {
    WJets_Tree->GetEntry(i);
    
    if (BOX_NUM_ == 0) {
      WJets_0MuBox_MC->Fill(MR_, RSQ_, LUMI*Weight_WJets);
      MC_0Mu->Fill(MR_,RSQ_,LUMI*Weight_WJets);
      WJets_Background += LUMI*Weight_WJets;
      if( RSQ_ > 0.5 && MR_ > 150 )WJ_Bkg_0Mu += LUMI*Weight_WJets;
      
    }else if (BOX_NUM_ == 1) {
      WJets_1MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_WJets);
      MC_1Mu->Fill(MR_,RSQ_, LUMI*Weight_WJets);
      WJets_Background += LUMI*Weight_WJets;
      if( RSQ_ > 0.5 && MR_ > 150 )WJ_Bkg_1Mu += LUMI*Weight_WJets;
    }else if (BOX_NUM_ == 2){
      if( RSQ_ > 0.5 && MR_ > 150 )WJ_Bkg_2Mu += LUMI*Weight_WJets;
    }else{
      std::cout << " NO BOX FOR WJ CASE" << std::endl;
    }
  }
  
  for(Int_t i = 1; i < N_Entries_ZJets; i++) {
    ZJets_Tree->GetEntry(i);
    
    if (BOX_NUM_==0) {
      ZJets_0MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZJets);
      MC_0Mu->Fill(MR_,RSQ_,LUMI*Weight_ZJets);
      ZJets_Background += LUMI*Weight_ZJets;
    }
    
    else if (BOX_NUM_==1) {
      ZJets_1MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZJets);
      MC_1Mu->Fill(MR_,RSQ_, LUMI*Weight_ZJets);
      ZJets_Background += LUMI*Weight_ZJets;
    }
    
    else if (BOX_NUM_==2)
      MC_2Mu->Fill(MR_,RSQ_, LUMI*Weight_ZJets);
  }
  

  //Jet Multiplity plots for TTbar BOX
  for(Int_t i = 1; i < N_Entries_TTBar; i++) {
    TTBar_Tree->GetEntry(i);
    if( nBtagLoose_ == 1 && nBtagTight_ == 1 && RSQ_ > 0.5 && MR_ > 150 ){
      if( BOX_NUM_ == 0 ){
        //MultRatio_0mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	MultRatio_0mu->Fill(N_Jets_);
      }else if( BOX_NUM_ == 1 ){
        //MultRatio_1mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	MultRatio_1mu->Fill(N_Jets_);
      }else if( BOX_NUM_ ==2 ){
        //MultRatio_2mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	MultRatio_2mu->Fill(N_Jets_);
      }
    }
  }
  
  //Ratio Jet Multiplcity TTbar box
  TwoBtag_0mu_to1mu->Divide(MultRatio_0mu, MultRatio_1mu, 1, 1, "");
  TwoBtag_0mu_to2mu->Divide(MultRatio_0mu, MultRatio_2mu, 1, 1, "");
  TwoBtag_1mu_to2mu->Divide(MultRatio_1mu, MultRatio_2mu, 1, 1, "");
  
  for(Int_t i = 1; i < N_Entries_TTBar; i++) {
    TTBar_Tree->GetEntry(i);
    
    if (nBtagLoose_==0) {
      if( nBtagTight_ > 0){
	std::cout << "ZERO BLoose and No Zero Btight" << std::endl; 
      }
      
      if (BOX_NUM_==0) {
	TTBar_0MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_TTBar);
	MC_0Mu->Fill(MR_,RSQ_,LUMI*Weight_TTBar);
	if( RSQ_ > 0.5 && MR_ > 150 )TTBar_Bkg_0Mu += LUMI*Weight_TTBar;
	//std::cout << "TTBar_Background: " << TTBar_Background << std::endl;
      }else if (BOX_NUM_==1) {
	TTBar_1MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_TTBar);
	MC_1Mu->Fill(MR_,RSQ_, LUMI*Weight_TTBar);
	//TTBar_Background += LUMI*Weight_TTBar;
	if( RSQ_ > 0.5 && MR_ > 150 )TTBar_Bkg_1Mu += LUMI*Weight_TTBar;
      }else if ( BOX_NUM_ == 2 ){
	if( RSQ_ > 0.5 && MR_ > 150 )TTBar_Bkg_2Mu += LUMI*Weight_TTBar;
      }else{
	std::cout << " NO BOX FOR 0BTAG CASE" << std::endl;
      }
    }
    
    else if ((nBtagLoose_==1) && (nBtagTight_==1) && (BOX_NUM_==1)) MC_TTBar->Fill(MR_,RSQ_,LUMI*Weight_TTBar);
    
    
    //New Cristian Plots
    if( nBtagLoose_ == 0  && nBtagTight_ == 0 && RSQ_ > 0.5 && MR_ > 150 ){
      if( BOX_NUM_ == 0 ){
	//MC_TT_JetMult_0btag_0Mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	//MR_0Mu_0btag->Fill(MR_, LUMI*Weight_TTBar);
	//RSQ_0Mu_0btag->Fill(RSQ_, LUMI*Weight_TTBar);
	MC_TT_JetMult_0btag_0Mu->Fill(N_Jets_);
	MR_0Mu_0btag->Fill(MR_);
	RSQ_0Mu_0btag->Fill(RSQ_);
      }else if( BOX_NUM_ == 1 ){
	//MC_TT_JetMult_0btag_1Mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	MC_TT_JetMult_0btag_1Mu->Fill(N_Jets_);
      }else if( BOX_NUM_ ==2 ){
	//MC_TT_JetMult_0btag_2Mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	MC_TT_JetMult_0btag_2Mu->Fill(N_Jets_);
      }
    }else if( nBtagLoose_ == 1 && nBtagTight_ == 1 && RSQ_ > 0.5 && MR_ > 150 ){
      if( BOX_NUM_ == 0 ){
	//MC_TT_JetMult_2btag_0Mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	//MR_0Mu_2btag->Fill(MR_, LUMI*Weight_TTBar);
	//RSQ_0Mu_2btag->Fill(RSQ_, LUMI*Weight_TTBar);
	MC_TT_JetMult_2btag_0Mu->Fill(N_Jets_);
	MR_0Mu_2btag->Fill(MR_);
	RSQ_0Mu_2btag->Fill(RSQ_);
      }else if( BOX_NUM_ == 1 ){
	//MC_TT_JetMult_2btag_1Mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	MC_TT_JetMult_2btag_1Mu->Fill(N_Jets_);
      }else if( BOX_NUM_ ==2 ){
	//MC_TT_JetMult_2btag_2Mu->Fill(N_Jets_, LUMI*Weight_TTBar);
	MC_TT_JetMult_2btag_2Mu->Fill(N_Jets_);
      }
    }
    
    
  }

  std::cout << "TTBar_Bkg_0Mu: " << TTBar_Bkg_0Mu << std::endl;
  std::cout << "TTBar_Bkg_1Mu: " << TTBar_Bkg_1Mu << std::endl;
  std::cout << "TTBar_Bkg_2Mu: " << TTBar_Bkg_2Mu << std::endl;
  std::cout << "WJ_Bkg_0Mu: " << WJ_Bkg_0Mu << std::endl;
  std::cout << "WJ_Bkg_1Mu: " << WJ_Bkg_1Mu << std::endl;
  std::cout << "WJ_Bkg_2Mu: " << WJ_Bkg_2Mu << std::endl;
  
  
  /*
    for(Int_t i = 1; i < N_Entries_ZNuNu1; i++) {
    ZNuNu_Tree1->GetEntry(i);
    
    if (BOX_NUM_==0) {
    ZJets_0MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu1);
	MC_0Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu1);
	ZJets_Background += LUMI*Weight_ZNuNu1;
      }
      
      else if (BOX_NUM_==1) {
      ZJets_1MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu1);
	MC_1Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu1);
	ZJets_Background += LUMI*Weight_ZNuNu1;
	}
	}
	
	for(Int_t i = 1; i < N_Entries_ZNuNu2; i++) {
	ZNuNu_Tree2->GetEntry(i);
    
	if (BOX_NUM_==0) {
	ZJets_0MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu2);
	MC_0Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu2);
	ZJets_Background += LUMI*Weight_ZNuNu2;
      }

      else if (BOX_NUM_==1) {
	ZJets_1MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu2);
	MC_1Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu2);
	ZJets_Background += LUMI*Weight_ZNuNu2;
      }
  }

  for(Int_t i = 1; i < N_Entries_ZNuNu3; i++) {
    ZNuNu_Tree3->GetEntry(i);
    
      if (BOX_NUM_==0) {
	ZJets_0MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu3);
	MC_0Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu3);
	ZJets_Background += LUMI*Weight_ZNuNu3;
      }

      else if (BOX_NUM_==1) {
	ZJets_1MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu3);
	MC_1Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu3);
	ZJets_Background += LUMI*Weight_ZNuNu3;
      }
  }

  for(Int_t i = 1; i < N_Entries_ZNuNu4; i++) {
    ZNuNu_Tree4->GetEntry(i);
    
      if (BOX_NUM_==0) {
	ZJets_0MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu4);
	MC_0Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu4);
	ZJets_Background += LUMI*Weight_ZNuNu4;
      }

      else if (BOX_NUM_==1) {
	ZJets_1MuBox_MC->Fill(MR_,RSQ_, LUMI*Weight_ZNuNu4);
	MC_1Mu->Fill(MR_,RSQ_,LUMI*Weight_ZNuNu4);
	ZJets_Background += LUMI*Weight_ZNuNu4;
      }
  }
  */
  TFile Output1("MC_ZJ.root","recreate");
  //TTree *OutputTree = new TTree("T","test");
  ZJets_0MuBox_MC->Write("ZeroMuonBoxZJets");
  ZJets_1MuBox_MC->Write("OneMuonBoxZJets");
  WJets_0MuBox_MC->Write("TwoMuonBoxZJets");
  WJets_1MuBox_MC->Write("ZeroMuonBoxWJets");
  TTBar_0MuBox_MC->Write("ZeroMuonBoxTTJets");
  TTBar_1MuBox_MC->Write("OneMuonBoxTTJets");
  MC_0Mu->Write("ZeroMuonBoxMC");
  MC_1Mu->Write("OneMuonBoxMC");
  MC_2Mu->Write("TwoMuonBoxMC");
  MC_TTBar->Write("TTJetsMC");
  TwoBtag_0mu_to1mu->Write();
  TwoBtag_0mu_to2mu->Write();
  TwoBtag_1mu_to2mu->Write();
  
  TCanvas C("C", "C", 1024, 1024);
  
  C.cd();
  MC_TT_JetMult_0btag_2Mu->SetFillColor(8);
  MC_TT_JetMult_0btag_1Mu->SetFillColor(4);
  MC_TT_JetMult_0btag_0Mu->SetFillColor(2);
  
  MC_TT_JetMult_0btag_1Mu->Draw();
  MC_TT_JetMult_0btag_0Mu->Draw("same");
  MC_TT_JetMult_0btag_2Mu->Draw("same");
  
  // ...
  
  C.SaveAs("ZeroBtagJetMult.pdf");
  
  MC_TT_JetMult_0btag_0Mu->Write("MC_TT_JetMult_0btag_0Mu");
  MC_TT_JetMult_0btag_1Mu->Write("MC_TT_JetMult_0btag_1Mu");
  MC_TT_JetMult_0btag_2Mu->Write("MC_TT_JetMult_0btag_2Mu");
  
  MR_0Mu_2btag->SetFillColor(2);
  RSQ_0Mu_2btag->SetFillColor(2);
  MR_0Mu_0btag->SetFillColor(8);
  RSQ_0Mu_0btag->SetFillColor(8);

  TCanvas C2("C", "C", 1024, 1024);
  C2.cd();
  
  MR_0Mu_2btag->Draw();
  MR_0Mu_0btag->Draw("same");
  C2.SaveAs("MR_2b_0b.pdf");
  
  MR_0Mu_2btag->Write("MR_ZeroMuon2B");
  RSQ_0Mu_2btag->Write("RSQ_ZeroMuon2B");
  MR_0Mu_0btag->Write("MR_ZeroMuonZeroB");
  RSQ_0Mu_0btag->Write("RSQ_ZeroMuonZeroB");
  
  //Two Btag Multiplicity Plots
  TCanvas C3("C", "C", 1024, 1024);
  C3.cd();
  
  MC_TT_JetMult_2btag_2Mu->SetFillColor(8);
  MC_TT_JetMult_2btag_1Mu->SetFillColor(4);
  MC_TT_JetMult_2btag_0Mu->SetFillColor(2);
  
  MC_TT_JetMult_2btag_1Mu->Draw();
  MC_TT_JetMult_2btag_0Mu->Draw("same");
  MC_TT_JetMult_2btag_2Mu->Draw("same");
  
  // ...
  
  C3.SaveAs("TwoBtagJetMult.pdf");
  
  MC_TT_JetMult_2btag_0Mu->Write("MC_TT_JetMult_2btag_0Mu");
  MC_TT_JetMult_2btag_1Mu->Write("MC_TT_JetMult_2btag_1Mu");
  MC_TT_JetMult_2btag_2Mu->Write("MC_TT_JetMult_2btag_2Mu");
  
  Output1.Close();
  
  //OutputTree1->Branch("RSQ_MR","TH2D",&ZJets_0MuBox_MC);
  //OutputTree1->Fill();
  //Output1.Write();

  /*
  TFile Output2("VarBin_Histograms/MC_Bkgnd_Prediction/MC_ZJets_1Mu.root","recreate");
  TTree *OutputTree2 = new TTree("T","test");
  OutputTree2->Branch("RSQ_MR","TH2D",&ZJets_1MuBox_MC);
  OutputTree2->Fill();
  Output2.Write();

  TFile Output3("VarBin_Histograms/MC_Bkgnd_Prediction/MC_WJets_0Mu.root","recreate");
  TTree *OutputTree3 = new TTree("T","test");
  OutputTree3->Branch("RSQ_MR","TH2D",&WJets_0MuBox_MC);
  OutputTree3->Fill();
  Output3.Write();

  TFile Output4("VarBin_Histograms/MC_Bkgnd_Prediction/MC_WJets_1Mu.root","recreate");
  TTree *OutputTree4 = new TTree("T","test");
  OutputTree4->Branch("RSQ_MR","TH2D",&WJets_1MuBox_MC);
  OutputTree4->Fill();
  Output4.Write();

  TFile Output5("VarBin_Histograms/MC_Bkgnd_Prediction/MC_TTBar_0Mu.root","recreate");
  TTree *OutputTree5 = new TTree("T","test");
  OutputTree5->Branch("RSQ_MR","TH2D",&TTBar_0MuBox_MC);
  OutputTree5->Fill();
  Output5.Write();

  TFile Output6("VarBin_Histograms/MC_Bkgnd_Prediction/MC_TTBar_1Mu.root","recreate");
  TTree *OutputTree6 = new TTree("T","test");
  OutputTree6->Branch("RSQ_MR","TH2D",&TTBar_1MuBox_MC);
  OutputTree6->Fill();
  Output6.Write();

  TFile Output7("VarBin_Histograms/MC_Bkgnd_Prediction/MC_0Mu.root","recreate");
  TTree *OutputTree7 = new TTree("T","test");
  OutputTree7->Branch("RSQ_MR","TH2D",&MC_0Mu);
  OutputTree7->Fill();
  Output7.Write();

  TFile Output8("VarBin_Histograms/MC_Bkgnd_Prediction/MC_1Mu.root","recreate");
  TTree *OutputTree8 = new TTree("T","test");
  OutputTree8->Branch("RSQ_MR","TH2D",&MC_1Mu);
  OutputTree8->Fill();
  Output8.Write();

  TFile Output9("VarBin_Histograms/MC_Bkgnd_Prediction/MC_2Mu.root","recreate");
  TTree *OutputTree9 = new TTree("T","test");
  OutputTree9->Branch("RSQ_MR","TH2D",&MC_2Mu);
  OutputTree9->Fill();
  Output9.Write();

  TFile Output10("VarBin_Histograms/MC_Bkgnd_Prediction/MC_TTBar.root","recreate");
  TTree *OutputTree10 = new TTree("T","test");
  OutputTree10->Branch("RSQ_MR","TH2D",&MC_TTBar);
  OutputTree10->Fill();
  Output10.Write();

  */
}

void setstyle(int istyle) {
	
	// For the canvas:
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetCanvasDefH(300); //Height of canvas
	gStyle->SetCanvasDefW(600); //Width of canvas
	gStyle->SetCanvasDefX(0);   //POsition on screen
	gStyle->SetCanvasDefY(0);
	
	// For the Pad:
	gStyle->SetPadBorderMode(0);
	// gStyle->SetPadBorderSize(Width_t size = 1);
	gStyle->SetPadColor(kWhite);
	gStyle->SetPadGridX(false);
	gStyle->SetPadGridY(false);
	gStyle->SetGridColor(0);
	gStyle->SetGridStyle(3);
	gStyle->SetGridWidth(1);
	
	// For the frame:
	gStyle->SetFrameBorderMode(0);
	gStyle->SetFrameBorderSize(1);
	gStyle->SetFrameFillColor(0);
	gStyle->SetFrameFillStyle(0);
	gStyle->SetFrameLineColor(1);
	gStyle->SetFrameLineStyle(1);
	gStyle->SetFrameLineWidth(1);
	
	// set the paper & margin sizes
	gStyle->SetPaperSize(20,26);
	gStyle->SetPadTopMargin(0.065);
	gStyle->SetPadRightMargin(0.065);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.17);
	
	// use large Times-Roman fonts
	gStyle->SetTitleFont(132,"xyz");  // set the all 3 axes title font
	gStyle->SetTitleFont(132," ");    // set the pad title font
	gStyle->SetTitleSize(0.06,"xyz"); // set the 3 axes title size
	gStyle->SetTitleSize(0.06," ");   // set the pad title size
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetLabelColor(1,"xyz");
	gStyle->SetTextFont(132);
	gStyle->SetTextSize(0.08);
	gStyle->SetStatFont(132);
	
	// use bold lines and markers
	gStyle->SetMarkerStyle(8);
	gStyle->SetHistLineWidth(1.85);
	gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
	
	//..Get rid of X error bars
	gStyle->SetErrorX(0.001);
	
	// do not display any of the standard histogram decorations
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(11111111);
	
	// put tick marks on top and RHS of plots
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	
	// set a decent palette
	gStyle->SetPalette(1);
	
	gStyle->cd();
	
	//TColorWheel *w = new TColorWheel();
	
	icolor[0][1] = new TColor(1390, 0.90, 0.60, 0.60, ""); //red
	icolor[0][0] = new TColor(1391, 0.70, 0.25, 0.25, "");
	icolor[1][1] = new TColor(1392, 0.87, 0.87, 0.91, ""); //blue
	icolor[1][0] = new TColor(1393, 0.59, 0.58, 0.91, "");
	icolor[2][1] = new TColor(1394, 0.65, 0.55, 0.85, ""); //violet (gamma)
	icolor[2][0] = new TColor(1395, 0.49, 0.26, 0.64, "");
	icolor[3][1] = new TColor(1396, 0.95, 0.95, 0.60, ""); // yellow (alpha)
	icolor[3][0] = new TColor(1397, 0.95, 0.95, 0.00, "");
	icolor[4][1] = new TColor(1398, 0.75, 0.92, 0.68, ""); //green (2beta+gamma)
	icolor[4][0] = new TColor(1399, 0.36, 0.57, 0.30, "");
	icolor[5][1] = new TColor(1400, 0.97, 0.50, 0.09, ""); // orange
	icolor[5][0] = new TColor(1401, 0.76, 0.34, 0.09, "");
	icolor[6][1] = new TColor(1402, 0.97, 0.52, 0.75, ""); // pink
	icolor[6][0] = new TColor(1403, 0.76, 0.32, 0.51, "");
	icolor[7][1] = new TColor(1404, 0.49, 0.60, 0.82, ""); // dark blue (kpnn)
	icolor[7][0] = new TColor(1405, 0.43, 0.48, 0.52, "");
	icolor[8][1] = new TColor(1406, 0.70, 0.70, 0.70, "");  // black
	icolor[8][0] = new TColor(1407, 0.40, 0.40, 0.40, "");
	
	
	if(istyle == 0){
		
		//SM MC
		color_list[3][0] = kCyan+3;
		
		//DATA
		color_list[0][0] = 1;
		color_list[0][1] = 2;
		color_list[0][2] = 4;
		style_list[0][0] = 20;
		style_list[0][1] = 23;
		
		//BKG MC
		color_list[1][0] = 0;
		color_list[1][3] = kGreen-9; //Light green
		color_list[1][5] = kOrange-2; //dark blue
		color_list[1][4] = kGreen+3; //yellow
		color_list[1][1] = kBlue-10; //light blue
		color_list[1][2] = kBlue+4; //dark green
		style_list[1][0] = 1001;
		style_list[1][1] = 1001;
		style_list[1][2] = 3002;
		style_list[1][3] = 1001;
		style_list[1][4] = 1001;
		style_list[1][5] = 1001;
		
		//SIG MC
		color_list[2][0] = 1;
		color_list[2][1] = 1;
		color_list[2][2] = 1;
		style_list[2][0] = 2;
		style_list[2][1] = 5;
	}
	if(istyle == 1){
		
		//SM MC
		color_list[3][0] = kSpring+4;
		
		//DATA
		color_list[0][0] = 1;
		color_list[0][1] = 2;
		color_list[0][2] = 4;
		style_list[0][0] = 20;
		style_list[0][1] = 23;
		
		//BKG MC
		color_list[1][0] = 0;
		color_list[1][1] = kGreen-9; //Light green
		color_list[1][2] = kGreen+3; //dark blue
		color_list[1][3] = kYellow-7; //yellow
		color_list[1][4] = kBlue-10; //light blue
		color_list[1][5] = kBlue+4; //dark blue
		style_list[1][0] = 1001;
		style_list[1][1] = 1001;
		style_list[1][2] = 3002;
		style_list[1][3] = 1001;
		style_list[1][4] = 1001;
		style_list[1][5] = 1001;
		
		//SIG MC
		color_list[2][0] = 1;
		color_list[2][1] = 1;
		color_list[2][2] = 1;
		style_list[2][0] = 2;
		style_list[2][1] = 5;
	}
	if(istyle == 2){
		
		//SM MC
		color_list[3][0] = kMagenta+2;
		
		//DATA
		color_list[0][0] = 1;
		color_list[0][1] = 2;
		color_list[0][2] = 4;
		style_list[0][0] = 20;
		style_list[0][1] = 23;
		
		//BKG MC
		color_list[1][0] = 0;
		color_list[1][3] = kRed-9; //Light green
		color_list[1][5] = kRed+3; //dark blue
		color_list[1][4] = kYellow-7; //yellow
		color_list[1][1] = kMagenta-10; //light blue
		color_list[1][2] = kMagenta+4; //dark green
		style_list[1][0] = 1001;
		style_list[1][1] = 1001;
		style_list[1][2] = 3002;
		style_list[1][3] = 1001;
		style_list[1][4] = 1001;
		style_list[1][5] = 1001;
		
		//SIG MC
		color_list[2][0] = 1;
		color_list[2][1] = 1;
		color_list[2][2] = 1;
		style_list[2][0] = 2;
		style_list[2][1] = 5;
	}
	
}
