#include "DM_DY_HTBins.hh"
#include <iostream>

DY::DY(){ };

DY::DY(int metIndex){
  
  MRMin = 200.0;//nominal 150.0
  RSQMin = 0.5;//nominal 0.5
  this->metIndex = metIndex;
  
  double N_In = 0 , Ntot = 0;
  double Nexp = 0;
  
  /////////////////////////////////////////
  ///////////Trigger Efficiency////////////
  ////////////////////////////////////////
  TFile* file = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/V07_5_3_X/MuHad-Run2012AB/out/hlt_eff_mr200_MoreBin_ABCD_PT80v2Muon.root");
  
  eff = (TEfficiency*)file->Get("Eff2d");
  TFile* file1 = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/V07_5_3_X/EleHad-Run2012AB/out/hlt_eff_mr200_MoreBin_PT80.root");
  
  eff_ele = (TEfficiency*)file->Get("Eff2d");
  
  ///////////////////////////////////////
  ////////////////HT bins Trees/////////
  //////////////////////////////////////  
  
  //F = TFile::Open("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/afs/DY_NoILV_samples/DYJetsHT200To400_NoILV_Total.root");
  
  F = TFile::Open("root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/ILV/DYJetsHT200To400_ILV_v3.root");

  TTree* effT = (TTree*)F->Get("effTree");
  T = (TTree*)F->Get("outTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  
  Ntot = 0;
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    Ntot += N_In;
  }
  weight0 = Lumi*sigma0/Ntot;
  Nexp += weight0*T->GetEntries(); 
  
  //F1 = TFile::Open("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/afs/DY_NoILV_samples/DYJetsHT400_NoILV_Totalv2.root");
  
  F1 = TFile::Open("root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/ILV/DYJetsHT400_ILV.root");
  
  effT = (TTree*)F1->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  T1 = (TTree*)F1->Get("outTree");
  Ntot = 0;
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    Ntot += N_In;
  }
  
  weight1 = Lumi*sigma1/Ntot;
  Nexp += weight1*T1->GetEntries(); 
  
  
  std::cout << "Weight 0: " << weight0 << std::endl;
  std::cout << "Weight 1: " << weight1 << std::endl;
  
  ////////////////////////////////////////////////////////////////
  ////////// Including Btag capability///////////////////////////
  ///////////////////////////////////////////////////////////////
  
  if( btagIndex == 0 || btagIndex == 1 ){
    this->BtagBranch = "nBtag";
  }else{
    this->BtagBranch = "nBtagTight";
  }
  
  std::cout << "----------------Branch Name:  " << BtagBranch << std::endl;
  
};

DY::DY(const char* FileName ){
  
  //F = new TFile(FileName);
  //T0 = (TTree*)F->Get("outTree");
  
};

DY::~DY(){
  delete T;
  delete T1;
  delete F;
  delete F1;
};


bool DY::PrintEvents(){
  
  double NtotGen = 0, Nt_PV = 0, Nt_2J = 0, Nt_0b = 0, Nt_LepVeto = 0, N_In, N_PV, N_2J, N_0b, N_LepVeto;
  TTree* effT = (TTree*)F->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  effT->SetBranchAddress("Npassed_PV", &N_PV);
  effT->SetBranchAddress("Npassed_2Jet", &N_2J);
  effT->SetBranchAddress("Npassed_0btag", &N_0b);
  effT->SetBranchAddress("Npassed_LepVeto", &N_LepVeto);
  
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    NtotGen += N_In*weight0;
    Nt_PV += N_PV*weight0;
    Nt_2J += N_2J*weight0;
    Nt_0b += N_0b*weight0;
    Nt_LepVeto += N_LepVeto*weight0;
  }
  
  //second HTbin
  effT = (TTree*)F1->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  effT->SetBranchAddress("Npassed_PV", &N_PV);
  effT->SetBranchAddress("Npassed_2Jet", &N_2J);
  effT->SetBranchAddress("Npassed_0btag", &N_0b);
  effT->SetBranchAddress("Npassed_LepVeto", &N_LepVeto);
  
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    NtotGen += N_In*weight1;
    Nt_PV += N_PV*weight1;
    Nt_2J += N_2J*weight1;
    Nt_0b += N_0b*weight1;
    Nt_LepVeto += N_LepVeto*weight1;
  }
  
  
  std::cout << "============================================" << std::endl;
  std::cout << "================DY + Jets===================" << std::endl;
  std::cout << "============================================" << std::endl;

  std::cout << "DY weighted Nt_In: " << NtotGen << std::endl;
  std::cout << "DY weighted Nt_PV: " << Nt_PV << std::endl;
  std::cout << "DY weighted Nt_2J: " << Nt_2J << std::endl;
  std::cout << "DY weighted Nt_0b: " << Nt_0b << std::endl;
  std::cout << "DY weighted Nt_LepVeto: " << Nt_LepVeto << std::endl;

  std::cout << "DY weighted Nt_tree: " << T->GetEntries()*weight0 + T1->GetEntries()*weight1 << "\n\n" << std::endl;

  //After Selection cuts
  double RSQ[4], MR[4];
  int BOX, nBtag;
  
  double Nt_MR_RSQ_cut0BTag = 0.0, Nt_2muBox0BTag = 0.0,  Nt_1muBox0BTag = 0.0, Nt_0muBox0BTag = 0.0,\
    Nt_MR_RSQ_cut = 0.0, Nt_2muBox = 0.0,  Nt_1muBox = 0.0, Nt_0muBox = 0.0, Nt_Btags = 0.0;

  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin ){
      Nt_MR_RSQ_cut += weight0;
      
      if( BOX == 0 )Nt_0muBox += weight0;
      if( BOX == 1 )Nt_1muBox += weight0;
      if( BOX == 2 )Nt_2muBox += weight0;
      
      if( nBtag == 0 ){
	
	Nt_MR_RSQ_cut0BTag += weight0;
	
	if( BOX == 0 )Nt_0muBox0BTag += weight0;
	if( BOX == 1 )Nt_1muBox0BTag += weight0;
	if( BOX == 2 )Nt_2muBox0BTag += weight0;
	
      }
      
    }
    
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);

    if( RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin ){
      Nt_MR_RSQ_cut += weight1;
      
      if( BOX == 0 )Nt_0muBox += weight1;
      if( BOX == 1 )Nt_1muBox += weight1;
      if( BOX == 2 )Nt_2muBox += weight1;
      
      if( nBtag == 0 ){
	
	Nt_MR_RSQ_cut0BTag += weight1;
	
	if( BOX == 0 )Nt_0muBox0BTag += weight1;
	if( BOX == 1 )Nt_1muBox0BTag += weight1;
	if( BOX == 2 )Nt_2muBox0BTag += weight1;
	
      }
      
    }


  }
  
  std::cout << "DY weighted Nt_MR_RSQ_cut: " << Nt_MR_RSQ_cut << std::endl;
  std::cout << "DY weighted Nt_0muBox: " << Nt_0muBox << std::endl;
  std::cout << "DY weighted Nt_1muBox: " << Nt_1muBox << std::endl;
  std::cout << "DY weighted Nt_2muBox: " << Nt_2muBox << std::endl;

  std::cout << "DY weighted Nt_MR_RSQ_cut0Btag: " << Nt_MR_RSQ_cut0BTag << std::endl;
  std::cout << "DY weighted Nt_0muBox0Btag: " << Nt_0muBox0BTag << std::endl;
  std::cout << "DY weighted Nt_1muBox0Btag: " << Nt_1muBox0BTag << std::endl;
  std::cout << "DY weighted Nt_2muBox0Btag: " << Nt_2muBox0BTag << std::endl;

  std::cout << "DY Btag EVENTS: " << Nt_MR_RSQ_cut - Nt_MR_RSQ_cut0BTag << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "========================================" << "\n\n" << std::endl;
  
  return true;
  
  
};

TH1F DY::PlotMR_2Box(){
  
  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH1F* MR2 = new TH1F("MR2", "MR2BOX", MR_Bins, MR_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( BOX == 2 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex] ){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      MR2->Fill(MR[metIndex], weight0*hltWeight);
    }
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( BOX == 2 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex] ){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      MR2->Fill(MR[metIndex], weight1*hltWeight);
    }
  }

  return *MR2;
};


TH1F DY::PlotMR_1Box(){

  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH1F* MR1 = new TH1F("MR1", "MR1BOX", MR_Bins, MR_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 1 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex] ){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      MR1->Fill(MR[metIndex], weight0*hltWeight);
    }
  }

  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 1 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex] ){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      MR1->Fill(MR[metIndex], weight1*hltWeight);
    }
  }

  return *MR1;
};


TH1F DY::PlotMR_0Box(){
  
  double RSQ[4], MR[4];
  double hltWeight = 0.0; 
  int BOX, nBtag;
  TH1F* MR0 = new TH1F("MR0", "MR0BOX", MR_Bins, MR_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( BOX == 0 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      MR0->Fill(MR[metIndex], weight0*hltWeight);
    }
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( BOX == 0 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      MR0->Fill(MR[metIndex], weight1*hltWeight);
    }
  }
  
  return *MR0;
};


TH1F  DY::PlotRSQ_2Box(){

  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH1F* RSQ2 = new TH1F("RSQ2", "RSQ2BOX", RSQ_Bins, RSQ_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 2 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ2->Fill(RSQ[metIndex], weight0*hltWeight);
    }
  }

  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 2 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ2->Fill(RSQ[metIndex], weight1*hltWeight);
    }
  }

  return *RSQ2;

};

TH1F DY::PlotRSQ_1Box(){
  
  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH1F* RSQ1 = new TH1F("RSQ1", "RSQ1BOX", RSQ_Bins, RSQ_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( BOX == 1 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ1->Fill(RSQ[metIndex], weight0*hltWeight);
    }
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( BOX == 1 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ1->Fill(RSQ[metIndex], weight1*hltWeight);
    }
  }
  
  return *RSQ1;
  
};


TH1F  DY::PlotRSQ_0Box(){
  
  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH1F* RSQ0 = new TH1F("RSQ0", "RSQ0BOX", RSQ_Bins, RSQ_BinArr);
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 0 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ0->Fill(RSQ[metIndex], weight0*hltWeight);
    }
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 0 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ0->Fill(RSQ[metIndex], weight1*hltWeight);
    }
  }
  
  return *RSQ0;
  
};


TH2F DY::PlotRSQ_vs_MR_0Box(){
  
  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH2F* RSQ_MR_0BOX = new TH2F("RSQ_MR_0BOX", "RSQ_VS_MR_0BOX", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 0 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ_MR_0BOX->Fill(MR[metIndex], RSQ[metIndex], weight0*hltWeight);
    }
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 0 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ_MR_0BOX->Fill(MR[metIndex], RSQ[metIndex], weight1*hltWeight);
    }
  }
  
  return *RSQ_MR_0BOX;
  
};

TH2F DY::PlotRSQ_vs_MR_1Box(){
  
  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH2F* RSQ_MR_1BOX = new TH2F("RSQ_MR_1BOX", "RSQ_VS_MR_1BOX", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( BOX == 1 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ_MR_1BOX->Fill(MR[metIndex], RSQ[metIndex], weight0*hltWeight);
    }
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 1 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ_MR_1BOX->Fill(MR[metIndex], RSQ[metIndex], weight1*hltWeight);
    }
  }
  
  return *RSQ_MR_1BOX;
  
};

TH2F DY::PlotRSQ_vs_MR_2Box(){

  double RSQ[4], MR[4];
  double hltWeight = 0.0;
  int BOX, nBtag;
  TH2F* RSQ_MR_2BOX = new TH2F("RSQ_MR_2BOX", "RSQ_VS_MR_2BOX", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 2 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ_MR_2BOX->Fill(MR[metIndex], RSQ[metIndex], weight0*hltWeight);
    }
  }

  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    if( BOX == 2 && RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin && fBtag[btagIndex]){
      hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
      if( hltWeight == 0.0 )hltWeight = 1.0;
      RSQ_MR_2BOX->Fill(MR[metIndex], RSQ[metIndex], weight1*hltWeight);
    }
  }

  return *RSQ_MR_2BOX;

};

std::vector<TH1F*> DY::PlotMETmag(){
  double metX[4], metcorrX[4], metY[4], metcorrY[4], ht, RSQ[4], MR[4], run/*, ls, evNum*/;
  double mht[3];
  int BOX, nBtag, N_Jets;

  std::vector< TH1F* > metvec;
  TH1F* MET[12];
  TString name;
  double hltWeight;
  for(int l = 0; l < 3; l++ ){
    for( int m = 0; m < 3; m++ ){
      name = TString(Form("BaseDM_METmag_Box%d_plotType%d",l,m));
      MET[3*l + m] = new TH1F( name, name, 50, 0, 1000 );
    }
  }
  
  MET[9] = new TH1F( "NJETS0_Z", "NJETS 0 BOX", 9, 1, 10);
  MET[10] = new TH1F( "NJETS1_Z", "NJETS 1 BOX", 9, 1, 10);
  MET[11] = new TH1F( "NJETS2_Z", "NJETS 2 BOX", 9, 1, 10);
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  T->SetBranchAddress("ht", &ht);
  T->SetBranchAddress("mht", &mht[0]);
  T->SetBranchAddress("metX", metX);
  T->SetBranchAddress("metCorrX", metcorrX);
  T->SetBranchAddress("metY", metY);
  T->SetBranchAddress("metCorrY", metcorrY);
  T->SetBranchAddress("N_Jets", &N_Jets);
  
  float metmag = 0.;
  float metmagcorr = 0.;
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);

    metmag = sqrt(metX[metIndex]*metX[metIndex]+metY[metIndex]*metY[metIndex]);
    metmagcorr = sqrt(metcorrX[metIndex]*metcorrX[metIndex]+metcorrY[metIndex]*metcorrY[metIndex]);
    if( RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin  && fBtag[btagIndex] ){
      if( BOX == 0){
        hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        MET[0]->Fill(metmag, weight0*hltWeight);
        MET[1]->Fill(metmagcorr, weight0*hltWeight);
        MET[2]->Fill(metmagcorr-metmag, weight0*hltWeight);
        MET[9]->Fill(N_Jets,weight0*hltWeight);
      }else if( BOX == 1 ){
        hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        MET[3]->Fill(metmag, weight0*hltWeight);
        MET[4]->Fill(metmagcorr, weight0*hltWeight);
        MET[5]->Fill(metmagcorr-metmag, weight0*hltWeight);
        MET[10]->Fill(N_Jets,weight0*hltWeight);
      }else if( BOX == 2 ){
        hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        MET[6]->Fill(metmag, weight0*hltWeight);
        MET[7]->Fill(metmagcorr, weight0*hltWeight);
        MET[8]->Fill(metmagcorr-metmag, weight0*hltWeight);
        MET[11]->Fill(N_Jets,weight0*hltWeight);
      }
    }
    
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  T1->SetBranchAddress("ht", &ht);
  T1->SetBranchAddress("mht", &mht[0]);
  T1->SetBranchAddress("metX", metX);
  T1->SetBranchAddress("metCorrX", metcorrX);
  T1->SetBranchAddress("metY", metY);
  T1->SetBranchAddress("metCorrY", metcorrY);
  T1->SetBranchAddress("N_Jets", &N_Jets);
  
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    metmag = sqrt(metX[metIndex]*metX[metIndex]+metY[metIndex]*metY[metIndex]);
    metmagcorr = sqrt(metcorrX[metIndex]*metcorrX[metIndex]+metcorrY[metIndex]*metcorrY[metIndex]);
    if( RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin  && fBtag[btagIndex] ){
      if( BOX == 0){
        hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        MET[0]->Fill(metmag, weight1*hltWeight);
        MET[1]->Fill(metmagcorr, weight1*hltWeight);
        MET[2]->Fill(metmagcorr-metmag, weight1*hltWeight);
        MET[9]->Fill(N_Jets,weight1*hltWeight);
      }else if( BOX == 1 ){
        hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        MET[3]->Fill(metmag, weight1*hltWeight);
        MET[4]->Fill(metmagcorr, weight1*hltWeight);
        MET[5]->Fill(metmagcorr-metmag, weight1*hltWeight);
        MET[10]->Fill(N_Jets,weight1*hltWeight);
      }else if( BOX == 2 ){
	hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        MET[6]->Fill(metmag, weight1*hltWeight);
        MET[7]->Fill(metmagcorr, weight1*hltWeight);
        MET[8]->Fill(metmagcorr-metmag, weight1*hltWeight);
        MET[11]->Fill(N_Jets,weight1*hltWeight);
      }
    }
    
  }
  
  for(int j = 0; j < 12; j++){
    metvec.push_back(MET[j]);
  }
  
  return metvec;
  
};

std::vector<TH2F*> DY::Plot_2DRazor(){
  double RSQ[4], MR[4];
  int BOX, nBtag;
  
  std::vector< TH2F* > Razor2DVec;
  TH2F* Razor2D[3];
  TString name;
  double hltWeight;
  for(int l = 0; l < 3; l++ ){
    name = TString(Form("Razor2D_DY_%dmu_Box",l));
    Razor2D[l] = new TH2F( name, name, 200, 100., 1500., 200, 0.0, 1.5);
  }
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", RSQ);
  T->SetBranchAddress("MR", MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress(BtagBranch, &nBtag);
  
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( /*RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin  &&*/ fBtag[btagIndex] ){
      if( BOX == 0){
        hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        Razor2D[0]->Fill(MR[metIndex], RSQ[metIndex], weight0*hltWeight);
      }else if( BOX == 1 ){
        hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        Razor2D[1]->Fill(MR[metIndex], RSQ[metIndex], weight0*hltWeight);
      }else if( BOX == 2 ){
        hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        Razor2D[2]->Fill(MR[metIndex], RSQ[metIndex], weight0*hltWeight);
      }
    }
    
  }
  
  T1->SetBranchAddress("RSQ", RSQ);
  T1->SetBranchAddress("MR", MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress(BtagBranch, &nBtag);
  
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    fBtag[0] = (nBtag == 0);
    fBtag[1] = fBtag[2] = (nBtag >= 1);
    
    if( /*RSQ[metIndex] > RSQMin && MR[metIndex] > MRMin  && */fBtag[btagIndex] ){
      if( BOX == 0){
        hltWeight = HLTscaleEle( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        Razor2D[0]->Fill(MR[metIndex], RSQ[metIndex], weight1*hltWeight);
      }else if( BOX == 1 ){
        hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
	if( hltWeight == 0.0 )hltWeight = 1.0;
        Razor2D[1]->Fill(MR[metIndex], RSQ[metIndex], weight1*hltWeight);
      }else if( BOX == 2 ){
        hltWeight = HLTscale( MR[metIndex], RSQ[metIndex]);
        if( hltWeight == 0.0 )hltWeight = 1.0;
        Razor2D[2]->Fill(MR[metIndex], RSQ[metIndex], weight1*hltWeight);
      }
    }
    
  }
  
  for(int j = 0; j < 3; j++){
    Razor2DVec.push_back(Razor2D[j]);
  }
  
  return Razor2DVec;
  
};

bool DY::SetBrachStatus(){

  T->SetBranchStatus("*",0); //disable all branches
  T->SetBranchStatus("RSQ",1);
  T->SetBranchStatus("MR",1);
  T->SetBranchStatus("BOX_NUM",1);
  T->SetBranchStatus("nBtag",1);
  T->SetBranchStatus("nBtagTight",1);
  T->SetBranchStatus("ht",1);
  T->SetBranchStatus("metX",1);
  T->SetBranchStatus("metY",1);
  T->SetBranchStatus("metCorrX",1);
  T->SetBranchStatus("metCorrY",1);
  T->SetBranchStatus("N_Jets",1);
  
  T1->SetBranchStatus("*",0); //disable all branches
  T1->SetBranchStatus("RSQ",1);
  T1->SetBranchStatus("MR",1);
  T1->SetBranchStatus("BOX_NUM",1);
  T1->SetBranchStatus("nBtag",1);
  T1->SetBranchStatus("nBtagTight",1);
  T1->SetBranchStatus("ht",1);
  T1->SetBranchStatus("metX",1);
  T1->SetBranchStatus("metY",1);
  T1->SetBranchStatus("metCorrX",1);
  T1->SetBranchStatus("metCorrY",1);
  T1->SetBranchStatus("N_Jets",1);

};

double DY::HLTscale(double MR, double R2){

  int MRbin = -1;
  int R2bin = -1;
  
  const double R2A[] = {0.35, 0.5, 0.6, 0.8, 1.5};
  const double MRA[] = {200., 300., 400. ,500., 2000.};
  
  int Nbins = 4;
  
  for(int j = 0; j <= Nbins; j++){
    if( R2 > R2A[j]){
      if(R2 < R2A[j + 1]){
        R2bin = j+1;
        break;
      }
    }
  }

  for(int j = 0; j <= Nbins; j++){
    if( MR > MRA[j]){
      if(MR < MRA[j + 1]){
        MRbin = j+1;
        break;
      }
    }
  }

  //return hlt->GetBinContent( MRbin, R2bin );
  return eff->GetEfficiency(eff->GetGlobalBin(MRbin, R2bin , 0));
};

double DY::HLTscaleEle(double MR, double R2){
  
  int MRbin = -1;
  int R2bin = -1;
  
  const double R2A[] = {0.35, 0.5, 0.6, 0.8, 1.5};
  const double MRA[] = {200., 300., 400. ,500., 2000.};
  
  int Nbins = 4;

  for(int j = 0; j <= Nbins; j++){
    if( R2 > R2A[j]){
      if(R2 < R2A[j + 1]){
        R2bin = j+1;
        break;
      }
    }
  }

  for(int j = 0; j <= Nbins; j++){
    if( MR > MRA[j]){
      if(MR < MRA[j + 1]){
        MRbin = j+1;
        break;
      }
    }
  }
  
  //return hlt_ele->GetBinContent( MRbin, R2bin );
  return eff_ele->GetEfficiency(eff_ele->GetGlobalBin(MRbin, R2bin , 0));
  
};


