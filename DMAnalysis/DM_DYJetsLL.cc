#include "DM_DYJetsLL.hh"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

DYJets::DYJets(){
  
};

DYJets::DYJets(const char* FileName ){
  
  F = new TFile(FileName);
  T = (TTree*)F->Get("outTree");
  CalcWeight();
  
  MRMin = 200.0;//nominal 150.
  RSQMin = 0.5;//nomimal 0.5
  //std::cout << "Number of expected events in DY: " << weight*T->GetEntries() << std::endl;
  
};

DYJets::~DYJets(){
  delete T;
};

bool DYJets::PrintEvents(){
  std::setprecision(15);
  std::cout << std::fixed;
  
  double NtotGen = 0, Nt_PV = 0, Nt_2J = 0, Nt_0b = 0, Nt_LepVeto = 0, N_In, N_PV, N_2J, N_0b, N_LepVeto;
  TTree* effT = (TTree*)F->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  effT->SetBranchAddress("Npassed_PV", &N_PV);
  effT->SetBranchAddress("Npassed_2Jet", &N_2J);
  effT->SetBranchAddress("Npassed_0btag", &N_0b);
  effT->SetBranchAddress("Npassed_LepVeto", &N_LepVeto);
  
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    NtotGen += N_In;
    Nt_PV += N_PV;
    Nt_2J += N_2J;
    Nt_0b += N_0b;
    Nt_LepVeto += N_LepVeto;
  }

  std::cout << "========================================" << std::endl;
  std::cout << "================DY JETS==================" << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "DYLL weighted Nt_In: " << NtotGen*weight << std::endl;
  std::cout << "DYLL weighted Nt_PV: " << Nt_PV*weight << std::endl;
  std::cout << "DYLL weighted Nt_2J: " << Nt_2J*weight << std::endl;
  std::cout << "DYLL weighted Nt_0b: " << Nt_0b*weight << std::endl;
  std::cout << "DYLL weighted Nt_LepVeto: " << Nt_LepVeto*weight << std::endl;

  std::cout << "NEntries weighted: " << T->GetEntries()*weight << "\n\n" << std::endl; 
  //std::cout << "========================================" << std::endl;

  double RSQ, MR;
  int BOX, nBtag;
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  
  long Nt_MR_RSQ_cut = 0, Nt_2muBox = 0,  Nt_1muBox = 0, Nt_0muBox = 0,	\
    Nt_MR_RSQ_cut0BTag = 0, Nt_2muBox0BTag = 0,  Nt_1muBox0BTag = 0, Nt_0muBox0BTag = 0;
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( RSQ > RSQMin && MR > MRMin ){
      Nt_MR_RSQ_cut++;
      if( BOX == 0 )Nt_0muBox++;
      if( BOX == 1 )Nt_1muBox++;
      if( BOX == 2 )Nt_2muBox++;
      
      if( nBtag == 0){
	Nt_MR_RSQ_cut0BTag++;
	if( BOX == 0 )Nt_0muBox0BTag++;
	if( BOX == 1 )Nt_1muBox0BTag++;
	if( BOX == 2 )Nt_2muBox0BTag++;
      }
      
    }
  }
  
  //std::cout << "========================================" << std::endl;

  std::cout << "DYLL weighted Nt_MR_RSQ_cut: " << Nt_MR_RSQ_cut*weight << std::endl;
  std::cout << "DYLL weighted Nt_0muBox: " << Nt_0muBox*weight << std::endl;
  std::cout << "DYLL  weighted Nt_1muBox: " << Nt_1muBox*weight << std::endl;
  std::cout << "DYLL  weighted Nt_2muBox: " << Nt_2muBox*weight << std::endl;

  std::cout << "DYLL weighted Nt_MR_RSQ_cut0BTag: " << Nt_MR_RSQ_cut0BTag*weight << std::endl;
  std::cout << "DYLL weighted Nt_0muBox0BTag: " << Nt_0muBox0BTag*weight << std::endl;
  std::cout << "DYLL  weighted Nt_1muBox0BTag: " << Nt_1muBox0BTag*weight << std::endl;
  std::cout << "DYLL  weighted Nt_2muBox0BTag: " << Nt_2muBox0BTag*weight << std::endl;
  
  std::cout << "DYLL Btag EVENTS: " << (Nt_MR_RSQ_cut - Nt_MR_RSQ_cut0BTag)*weight << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "========================================" << "\n\n" << std::endl;

  return true;
  
};



/*bool DYJets::PrintEventsMC(){
  std::setprecision(15);
  std::cout << std::fixed;
  
  double NtotGen = 0, Nt_PV = 0, Nt_2J = 0, Nt_0b = 0, Nt_LepVeto = 0, N_In, N_PV, N_2J, N_0b, N_LepVeto;

  TTree* effT = (TTree*)F->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  effT->SetBranchAddress("Npassed_PV", &N_PV);
  effT->SetBranchAddress("Npassed_2Jet", &N_2J);
  effT->SetBranchAddress("Npassed_0btag", &N_0b);
  effT->SetBranchAddress("Npassed_LepVeto", &N_LepVeto);
  
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    NtotGen += N_In;
    Nt_PV += N_PV;
    Nt_2J += N_2J;
    Nt_0b += N_0b;
    Nt_LepVeto += N_LepVeto;
  }

  std::cout << "========================================" << std::endl;
  std::cout << "================DY JETS==================" << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "DYLL weighted Nt_In: " << NtotGen*weight << std::endl;
  std::cout << "DYLL weighted Nt_PV: " << Nt_PV*weight << std::endl;
  std::cout << "DYLL weighted Nt_2J: " << Nt_2J*weight << std::endl;
  std::cout << "DYLL weighted Nt_0b: " << Nt_0b*weight << std::endl;
  std::cout << "DYLL weighted Nt_LepVeto: " << Nt_LepVeto*weight << std::endl;

  std::cout << "NEntries weighted: " << T->GetEntries()*weight << "\n\n" << std::endl; 
  //std::cout << "========================================" << std::endl;
  
  double RSQ, MR;
  int BOX, nBtag;
  
  int arrMax = 150;
  int nMC, idMC[arrMax], statusMC[arrMax], mothMC[arrMax];
  float energyMC[arrMax], etaMC[arrMax];
  double Mu_E[2], Mu_Py[2], Mu_Px[2];
  
  
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  T->SetBranchAddress("nMC", &nMC);
  T->SetBranchAddress("idMC", &idMC);
  T->SetBranchAddress("mothMC", &mothMC);
  T->SetBranchAddress("statusMC", &statusMC);
  T->SetBranchAddress("energyMC", &energyMC);
  T->SetBranchAddress("etaMC", &etaMC);
  T->SetBranchAddress("Mu_E", &Mu_E);
  T->SetBranchAddress("Mu_Py", &Mu_Py);
  T->SetBranchAddress("Mu_Px", &Mu_Px);
   
  
  long Nt_MR_RSQ_cut = 0, Nt_2muBox = 0,  Nt_1muBox = 0, Nt_0muBox = 0,	\
    Nt_MR_RSQ_cut0BTag = 0, Nt_2muBox0BTag = 0,  Nt_1muBox0BTag = 0, Nt_0muBox0BTag = 0;

  float diff1, diff2;
  int jmin1 = 0, jmin2 = 0, ctr = 0, flag = 0;
  
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    
    diff1 = diff2 = 999999.;
    flag = 0;
    
    for( int j = 0; j < nMC; j++ ){
      if( abs(idMC[j]) == 13 && energyMC[j]/cosh( etaMC[j] ) > 25&& statusMC[j] == 1 ){
	if( fabs( Mu_E[0] - energyMC[j] ) < diff1 ){
	  diff1 = fabs( Mu_E[0] - energyMC[j] );
	  jmin1 = j;
	}
	if( fabs( Mu_E[1] - energyMC[j] ) < diff2 ){
	  diff2 = fabs( Mu_E[1] - energyMC[j] );
	  jmin2 = j;
	}
	if(flag == 0){
	  ctr++;
	  flag = 1;
	}
	//std::cout << "=====================PASSSSSSSSSS=========================  " << energyMC[j]/cosh( etaMC[j] ) << std::endl;
	//std::cout << "=================================================" << std::endl;
	//std::cout << "j: "  << j << "  energyMC[j]: " << energyMC[j] << \
	  //" etaMC[j]: " << etaMC[j] << " PtMC[j]: " << energyMC[j]/cosh( etaMC[j] ) << "  mothMC[j]:  " << mothMC[j] << std::endl;
	  
	  
	  //std::cout << "\nMu_E[0]: " << Mu_E[0] << "  Mu_Pt[0]: " <<  sqrt( Mu_Py[0]*Mu_Py[0] + Mu_Px[0]*Mu_Px[0] )<< std::endl;
	  //std::cout << "\nMu_E[1]: " << Mu_E[1] << "  Mu_Pt[1]: " <<  sqrt( Mu_Py[1]*Mu_Py[1] + Mu_Px[1]*Mu_Px[1] )<< std::endl;
	  //std::cout << "=================================================" << std::endl;
	  }
      //std::cout << "nMC: " << nMC << "  idMC[6]:  " << idMC[6] << "  mothMC[6]:  " << mothMC[6] << "  statusMC[6]: " << statusMC[6] << std::endl;
      //std::cout << "nMC: " << nMC << "  idMC[7]:  " << idMC[7] << "  mothMC[7]:  " << mothMC[7] << "  statusMC[7]: " << statusMC[7] << std::endl;
      //std::cout << "nMC: " << nMC << "  idMC[8]:  " << idMC[8] << "  mothMC[8]:  " << mothMC[8] << "  statusMC[8]: " << statusMC[8] << std::endl;
    }
    
    //std::cout << "====================CTRCTRCTR===========================  " << ctr << std::endl;
    //std::cout << "j: "  << jmin1 << "  energyMC[j]: " << energyMC[jmin1] << \
      ///  " etaMC[j]: " << etaMC[jmin1] << " PtMC[j]: " << energyMC[jmin1]/cosh( etaMC[jmin1] ) << "  mothMC[j]:  " << mothMC[jmin1] << std::endl;
    
    
      // std::cout << "\nMu_E[0]: " << Mu_E[0] << "  Mu_Pt[0]: " <<  sqrt( Mu_Py[0]*Mu_Py[0] + Mu_Px[0]*Mu_Px[0] )<< std::endl;

      //std::cout << "j: "  << jmin2 << "  energyMC[j]: " << energyMC[jmin2] <<	\
      //      " etaMC[j]: " << etaMC[jmin2] << " PtMC[j]: " << energyMC[jmin2]/cosh( etaMC[jmin2] ) << "  mothMC[j]:  " << mothMC[jmin2] << std::endl;
      // std::cout << "\nMu_E[1]: " << Mu_E[1] << "  Mu_Pt[1]: " <<  sqrt( Mu_Py[1]*Mu_Py[1] + Mu_Px[1]*Mu_Px[1] )<< std::endl;
    
    if( RSQ > RSQMin && MR > MRMin ){
      Nt_MR_RSQ_cut++;
      if( BOX == 0 )Nt_0muBox++;
      if( BOX == 1 )Nt_1muBox++;
      if( BOX == 2 )Nt_2muBox++;
      
      if( nBtag == 0){
	Nt_MR_RSQ_cut0BTag++;
	if( BOX == 0 )Nt_0muBox0BTag++;
	if( BOX == 1 )Nt_1muBox0BTag++;
	if( BOX == 2 )Nt_2muBox0BTag++;
      }
      
    }
  }
  std::cout << "====================CTRCTRCTR===========================  " << ctr*weight << std::endl;
  //std::cout << "========================================" << std::endl;

  std::cout << "DYLL weighted Nt_MR_RSQ_cut: " << Nt_MR_RSQ_cut*weight << std::endl;
  std::cout << "DYLL weighted Nt_0muBox: " << Nt_0muBox*weight << std::endl;
  std::cout << "DYLL  weighted Nt_1muBox: " << Nt_1muBox*weight << std::endl;
  std::cout << "DYLL  weighted Nt_2muBox: " << Nt_2muBox*weight << std::endl;

  std::cout << "DYLL weighted Nt_MR_RSQ_cut0BTag: " << Nt_MR_RSQ_cut0BTag*weight << std::endl;
  std::cout << "DYLL weighted Nt_0muBox0BTag: " << Nt_0muBox0BTag*weight << std::endl;
  std::cout << "DYLL  weighted Nt_1muBox0BTag: " << Nt_1muBox0BTag*weight << std::endl;
  std::cout << "DYLL  weighted Nt_2muBox0BTag: " << Nt_2muBox0BTag*weight << std::endl;
  
  std::cout << "DYLL Btag EVENTS: " << (Nt_MR_RSQ_cut - Nt_MR_RSQ_cut0BTag)*weight << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "========================================" << "\n\n" << std::endl;

  return true;
  
};
*/


bool DYJets::CalcWeight(){
  
  double Ntot = 0, N_In;
  TTree* effT = (TTree*)F->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    Ntot += N_In;
  }
  
  weight = Lumi*sigma/Ntot;
  std::cout << "DYtoLL weight: " << weight << std::endl;
  
  return true;
  
};

TH1F DYJets::PlotMR_2Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* MR1 = new TH1F("MR1", "MR1BOX", MR_Bins, MR_Low, MR_High);
  TH1F* MR2 = new TH1F("MR2_DY", "MR2BOX_DY", MR_Bins, MR_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 2 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )MR2->Fill(MR, weight);
  }
  
  return *MR2;
};



TH1F DYJets::PlotMR_1Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* MR1 = new TH1F("MR1", "MR1BOX", MR_Bins, MR_Low, MR_High);
  TH1F* MR1 = new TH1F("MR1_DY", "MR1BOX_DY", MR_Bins, MR_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX==1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)MR1->Fill(MR, weight);
  }
  
  return *MR1;
};

TH1F DYJets::PlotMR_0Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* MR0 = new TH1F("MR0", "MR0BOX", MR_Bins, MR_Low, MR_High);
  TH1F* MR0 = new TH1F("MR0_DY", "MR0BOX_DY", MR_Bins, MR_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )MR0->Fill(MR, weight);
  }
  
  return *MR0;
};

TH1F  DYJets::PlotRSQ_2Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* RSQ1 = new TH1F("RSQ1", "RSQ1BOX", RSQ_Bins, RSQ_Low, RSQ_High);
  TH1F* RSQ2 = new TH1F("RSQ2_DY", "RSQ2BOX_DY", RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    //std::cout << "RSQ: " << RSQ << "  BOX:   " << BOX <<  std::endl;
    if( BOX == 2 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ2->Fill(RSQ, weight);
  }
  
  //std::cout << "bin: " << RSQ1->GetEntries() << std::endl;
  
  return *RSQ2;
  
};

TH1F  DYJets::PlotRSQ_1Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* RSQ1 = new TH1F("RSQ1", "RSQ1BOX", RSQ_Bins, RSQ_Low, RSQ_High);
  TH1F* RSQ1 = new TH1F("RSQ1_DY", "RSQ1BOX_DY", RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    //std::cout << "RSQ: " << RSQ << "  BOX:   " << BOX <<  std::endl;
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )RSQ1->Fill(RSQ, weight);
  }
  
  //std::cout << "bin: " << RSQ1->GetEntries() << std::endl;
  
  return *RSQ1;
  
};


TH1F  DYJets::PlotRSQ_0Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* RSQ0 = new TH1F("RSQ0", "RSQ0BOX", RSQ_Bins, RSQ_Low, RSQ_High);
  TH1F* RSQ0 = new TH1F("RSQ0_DY", "RSQ0BOX_DY", RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )RSQ0->Fill(RSQ, weight);
  }
  
  return *RSQ0;
  
};


TH2F DYJets::PlotRSQ_vs_MR_0Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH2F* RSQ_MR_0BOX = new TH2F("RSQ_MR_0BOX", "RSQ_VS_MR_0BOX", MR_Bins, MR_Low, MR_High, RSQ_Bins, RSQ_Low, RSQ_High);
  TH2F* RSQ_MR_0BOX = new TH2F("RSQ_MR_0BOX_DY", "RSQ_VS_MR_0BOX_DY", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )RSQ_MR_0BOX->Fill(MR, RSQ, weight);
  }
  
  return *RSQ_MR_0BOX;
  
};

TH2F DYJets::PlotRSQ_vs_MR_1Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH2F* RSQ_MR_1BOX = new TH2F("RSQ_MR_1BOX", "RSQ_VS_MR_1BOX", MR_Bins, MR_Low, MR_High, RSQ_Bins, RSQ_Low, RSQ_High);
  TH2F* RSQ_MR_1BOX = new TH2F("RSQ_MR_1BOX_DY", "RSQ_VS_MR_1BOX_DY", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )RSQ_MR_1BOX->Fill(MR, RSQ, weight);
  }
  
  return *RSQ_MR_1BOX;
  
};

TH2F DYJets::PlotRSQ_vs_MR_2Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH2F* RSQ_MR_1BOX = new TH2F("RSQ_MR_1BOX", "RSQ_VS_MR_1BOX", MR_Bins, MR_Low, MR_High, RSQ_Bins, RSQ_Low, RSQ_High);
  TH2F* RSQ_MR_2BOX = new TH2F("RSQ_MR_2BOX_DY", "RSQ_VS_MR_2BOX_DY", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 2 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )RSQ_MR_2BOX->Fill(MR, RSQ, weight);
  }
  
  return *RSQ_MR_2BOX;
  
};

std::vector<TH1F*> DYJets::PlotMETx(){
 double met, metcorr, RSQ, MR;
  int BOX, nBtag;
  
  std::vector< TH1F* > metvec;
  
  TH1F* METx[9];
  TString name;
  for(int l = 0; l < 3; l++ ){
    for( int m = 0; m < 3; m++ ){
      name = TString(Form("DYJets_metXBox%d_plotType%d",l,m));
      //std::cout << "index: " << (2*(l+1)- 1) + m << std::endl;
      METx[3*l + m] = new TH1F( name, name, 50, -300, 300 );
    }
  }
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  T->SetBranchAddress("metX", &met);
  T->SetBranchAddress("metCorrX", &metcorr);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    
    if( RSQ > RSQMin && MR > MRMin  && nBtag == 0 ){
      if( BOX == 0){
	METx[0]->Fill(met, weight);
	METx[1]->Fill(metcorr, weight);
	METx[2]->Fill(metcorr-met, weight);
	//std::cout << "deb0 " << std::endl;
      }else if( BOX == 1 ){
	METx[3]->Fill(met, weight);
	METx[4]->Fill(metcorr, weight);
	METx[5]->Fill(metcorr-met, weight);
	//std::cout << "deb1 " << std::endl;
      }else if( BOX == 2 ){
	METx[6]->Fill(met, weight);
	METx[7]->Fill(metcorr, weight);
	METx[8]->Fill(metcorr-met, weight);
	//std::cout << "deb3 " << std::endl; 
      }
    }
    
  }
  
  for(int j = 0; j < 9; j++){
    metvec.push_back(METx[j]);
  }
  // std::cout << "deb5 " << std::endl;
  
  return metvec;
};


std::vector<TH1F*> DYJets::PlotMETy(){
double met, metcorr, RSQ, MR;
  int BOX, nBtag;
  
  std::vector< TH1F* > metvec;
  TH1F* MET[9];
  TString name;
  for(int l = 0; l < 3; l++ ){
    for( int m = 0; m < 3; m++ ){
      name = TString(Form("DYJets_metY_Box%d_plotType%d",l,m));
      MET[3*l + m] = new TH1F( name, name, 50, -300, 300 );
    }
  }
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  T->SetBranchAddress("metY", &met);
  T->SetBranchAddress("metCorrY", &metcorr);
  std::cout << "Tree entries: " << T->GetEntries() << std::endl;
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    
    if( RSQ > RSQMin && MR > MRMin  && nBtag == 0 ){
      if( BOX == 0){
	MET[0]->Fill(met, weight);
	MET[1]->Fill(metcorr, weight);
	MET[2]->Fill(metcorr-met, weight);
      }else if( BOX == 1 ){
	MET[3]->Fill(met, weight);
	MET[4]->Fill(metcorr, weight);
	MET[5]->Fill(metcorr-met, weight);
      }else if( BOX == 2 ){
	MET[6]->Fill(met, weight);
	MET[7]->Fill(metcorr, weight);
	MET[8]->Fill(metcorr-met, weight);
	//std::cout << "METY debug: " << "entry: "  <<  i << " RSQ: " << RSQ << " MR: " << MR \
	//	  << " nBtag:" << nBtag << std::endl;
      }
    }
    
  }
  
  for(int j = 0; j < 9; j++){
    metvec.push_back(MET[j]);
  }
  
  return metvec;
};

std::vector<TH1F*> DYJets::PlotHT(){
  double h, met, metcorr;
  double RS, MR;
  int BOX, nBtag;
  
  std::vector< TH1F* > metvec;
  
  TH1F* HT[3];
  TString name;
  for(int l = 0; l < 3; l++ ){
    name = TString(Form("DYJets_HT_Box%d",l));
    HT[l] = new TH1F( name, name, 50, 0, 300 );
  }
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RS);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  T->SetBranchAddress("metX", &h);
  T->SetBranchAddress("metY", &met);
  T->SetBranchAddress("metCorrY", &metcorr);
  std::cout << "Tree entries: " << T->GetEntries() << std::endl;
    for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    
    if(  RS > RSQMin && MR > MRMin  && nBtag == 0 ){
      if( BOX == 0 ){
	HT[0]->Fill(h, weight);
      }else if( BOX == 1 ){
	HT[1]->Fill(h, weight);
      }else if( BOX == 2 ){
	//std::cout << "ht debug: " << "entry: "  <<  i << " RSQ: " << RS << " MR: " << MR \
	//<< " nBtag:" << nBtag << std::endl;
	HT[2]->Fill(h, weight);
      }
      
    }
    
  }
  
  for(int j = 0; j < 3; j++){
    metvec.push_back(HT[j]);
  }
  
  return metvec;
};


bool DYJets::SetBrachStatus(){
  T->SetBranchStatus("*",0); //disable all branches
  T->SetBranchStatus("RSQ",1);
  T->SetBranchStatus("MR",1);
  T->SetBranchStatus("BOX_NUM",1);
  T->SetBranchStatus("nBtag",1);
  T->SetBranchStatus("ht",1);
  T->SetBranchStatus("metX",1);
  T->SetBranchStatus("metY",1);
  T->SetBranchStatus("metCorrX",1);
  T->SetBranchStatus("metCorrY",1);
};
