#include "DM_ZJetsNuNu.hh"
#include <iostream>

ZJetsNuNu::ZJetsNuNu(){

  MRMin = 200.0;//nominal 150.0
  RSQMin = 0.5;//nominal 0.5
  //std::cout << "+++++++++++++++++++++++++++" << std::endl;
  double N_In = 0 , Ntot = 0;
  
  double Nexp = 0;

  //F = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJetsToNuNu_50_HT_100_Total.root");
  F = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJETS_ToNuNu_50_HT_100_MET_afterBug.root");
  TTree* effT = (TTree*)F->Get("effTree");
  T = (TTree*)F->Get("outTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  Ntot = 0;
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    Ntot += N_In;
  }
  //std::cout << "Ntot HT50-100: " << Ntot << std::endl;
  weight0 = Lumi*sigma0/Ntot;
  Nexp += weight0*T->GetEntries(); 
  //std::cout << "Expected Number of events ZJetsNuNu HT 50-100: " << weight0*T->GetEntries() << std::endl;
  //F1 = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJetsToNuNu_100_HT_200_Total.root");
  F1 = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJETS_ToNuNu_100_HT_200_MET_afterBug.root");
  effT = (TTree*)F1->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  T1 = (TTree*)F1->Get("outTree");
  Ntot = 0;
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    Ntot += N_In;
  }
  //std::cout << "Ntot HT100-200: " << Ntot << std::endl;
  
  weight1 = Lumi*sigma1/Ntot;
  Nexp += weight1*T1->GetEntries(); 
  //std::cout << "Expected Number of events ZJetsNuNu HT 100-200: " << weight1*T1->GetEntries() << std::endl;
  
  //F2 = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJetsToNuNu_200_HT_400_Total.root");
  F2 = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJETS_ToNuNu_200_HT_400_MET_afterBug.root");
  effT = (TTree*)F2->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  T2 = (TTree*)F2->Get("outTree");
  Ntot = 0;
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    Ntot += N_In;
    //std::cout << "N_IN2: " << N_In << std::endl;
  }
  //std::cout << "Ntot HT200-400: " << Ntot << std::endl;
  weight2 = Lumi*sigma2/Ntot;
  Nexp += weight2*T2->GetEntries(); 
  //std::cout << "Expected Number of events ZJetsNuNu HT 200-400: " << weight2*T2->GetEntries() << std::endl;

  //F3 = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJetsToNuNu_400_HT_inf_Tot.root");
  F3 = new TFile("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/ZJetsToNuNuAllRootFiles/ZJETS_ToNuNu_400_HT_inf_MET_afterBug.root");
  effT = (TTree*)F3->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  T3 = (TTree*)F3->Get("outTree");
  Ntot = 0;
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    Ntot += N_In;
    //std::cout << "N_IN3: " << N_In << std::endl;
  }
  //std::cout << "Ntot HT400-inf: " << Ntot << std::endl;
  weight3 = Lumi*sigma3/Ntot;
  Nexp += weight3*T3->GetEntries(); 
  //delete F;
  //delete effT;
  //std::cout << "Expected Number of events ZJetsNuNu: " << Nexp << std::endl;
  //std::cout << "Expected Number of events ZJetsNuNu HT 400-inf: " << weight3*T3->GetEntries() << std::endl;
};

ZJetsNuNu::ZJetsNuNu(const char* FileName ){
  
  //F = new TFile(FileName);
  //T0 = (TTree*)F->Get("outTree");
  
};

ZJetsNuNu::~ZJetsNuNu(){
  delete T;
  delete T1;
  delete T2;
  delete T3;
  delete F;
  delete F1;
  delete F2;
  delete F3;
};


bool ZJetsNuNu::PrintEvents(){

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
  
  //Thrid HTbin
  effT = (TTree*)F2->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  effT->SetBranchAddress("Npassed_PV", &N_PV);
  effT->SetBranchAddress("Npassed_2Jet", &N_2J);
  effT->SetBranchAddress("Npassed_0btag", &N_0b);
  effT->SetBranchAddress("Npassed_LepVeto", &N_LepVeto);
  
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    NtotGen += N_In*weight2;
    Nt_PV += N_PV*weight2;
    Nt_2J += N_2J*weight2;
    Nt_0b += N_0b*weight2;
    Nt_LepVeto += N_LepVeto*weight2;
  }

  //Fourth HTbin
  effT = (TTree*)F3->Get("effTree");
  effT->SetBranchAddress("Npassed_In", &N_In);
  effT->SetBranchAddress("Npassed_PV", &N_PV);
  effT->SetBranchAddress("Npassed_2Jet", &N_2J);
  effT->SetBranchAddress("Npassed_0btag", &N_0b);
  effT->SetBranchAddress("Npassed_LepVeto", &N_LepVeto);
  
  for (int i = 0; i < effT->GetEntries(); i++){
    effT->GetEntry(i);
    NtotGen += N_In*weight3;
    Nt_PV += N_PV*weight3;
    Nt_2J += N_2J*weight3;
    Nt_0b += N_0b*weight3;
    Nt_LepVeto += N_LepVeto*weight3;
  }
  
  std::cout << "========================================" << std::endl;
  std::cout << "================ZJets===================" << std::endl;
  std::cout << "========================================" << std::endl;

  std::cout << "Znunu weighted Nt_In: " << NtotGen << std::endl;
  std::cout << "Znunu weighted Nt_PV: " << Nt_PV << std::endl;
  std::cout << "Znunu weighted Nt_2J: " << Nt_2J << std::endl;
  std::cout << "Znunu weighted Nt_0b: " << Nt_0b << std::endl;
  std::cout << "Znunu weighted Nt_LepVeto: " << Nt_LepVeto << std::endl;

  std::cout << "Znunu weighted Nt_tree: " << T->GetEntries()*weight0 +T1->GetEntries()*weight1 +  T2->GetEntries()*weight2 + T3->GetEntries()*weight3 << "\n\n" << std::endl;

  //std::cout << "========================================" << std::endl;

  //After Selection cuts
  double RSQ, MR;
  int BOX, nBtag;
  
  double Nt_MR_RSQ_cut0BTag = 0.0, Nt_2muBox0BTag = 0.0,  Nt_1muBox0BTag = 0.0, Nt_0muBox0BTag = 0.0,\
    Nt_MR_RSQ_cut = 0.0, Nt_2muBox = 0.0,  Nt_1muBox = 0.0, Nt_0muBox = 0.0, Nt_Btags = 0.0;

  //std::cout << "weights: " << weight0 << " " << weight1 << " " << weight2 << " " << weight3 << std::endl; 
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( RSQ > RSQMin && MR > MRMin ){
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
  
  T1->SetBranchAddress("RSQ", &RSQ);
  T1->SetBranchAddress("MR", &MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);

    if( RSQ > RSQMin && MR > MRMin ){
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
  
  T2->SetBranchAddress("RSQ", &RSQ);
  T2->SetBranchAddress("MR", &MR);
  T2->SetBranchAddress("BOX_NUM", &BOX);
  T2->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T2->GetEntries(); i++){
    T2->GetEntry(i);
    
    if( RSQ > RSQMin && MR > MRMin ){
      Nt_MR_RSQ_cut += weight2;
      
      if( BOX == 0 )Nt_0muBox += weight2;
      if( BOX == 1 )Nt_1muBox += weight2;
      if( BOX == 2 )Nt_2muBox += weight2;
      
      if( nBtag == 0 ){
	
	Nt_MR_RSQ_cut0BTag += weight2;
	
	if( BOX == 0 )Nt_0muBox0BTag += weight2;
	if( BOX == 1 )Nt_1muBox0BTag += weight2;
	if( BOX == 2 )Nt_2muBox0BTag += weight2;
	
      }
      
    }
    
  }
  
  T3->SetBranchAddress("RSQ", &RSQ);
  T3->SetBranchAddress("MR", &MR);
  T3->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T3->GetEntries(); i++){
    T3->GetEntry(i);
    
    if( RSQ > RSQMin && MR > MRMin ){
      Nt_MR_RSQ_cut += weight3;
      
      if( BOX == 0 )Nt_0muBox += weight3;
      if( BOX == 1 )Nt_1muBox += weight3;
      if( BOX == 2 )Nt_2muBox += weight3;
      
      if( nBtag == 0 ){
	
	Nt_MR_RSQ_cut0BTag += weight3;
	
	if( BOX == 0 )Nt_0muBox0BTag += weight3;
	if( BOX == 1 )Nt_1muBox0BTag += weight3;
	if( BOX == 2 )Nt_2muBox0BTag += weight3;
	
      }
      
    }
    
    
  }

  //std::cout << "========================================" << std::endl;
  std::cout << "Znunu weighted Nt_MR_RSQ_cut: " << Nt_MR_RSQ_cut << std::endl;
  std::cout << "Znunu weighted Nt_0muBox: " << Nt_0muBox << std::endl;
  std::cout << "Znunu weighted Nt_1muBox: " << Nt_1muBox << std::endl;
  std::cout << "Znunu weighted Nt_2muBox: " << Nt_2muBox << std::endl;

  std::cout << "Znunu weighted Nt_MR_RSQ_cut0Btag: " << Nt_MR_RSQ_cut0BTag << std::endl;
  std::cout << "Znunu weighted Nt_0muBox0Btag: " << Nt_0muBox0BTag << std::endl;
  std::cout << "Znunu weighted Nt_1muBox0Btag: " << Nt_1muBox0BTag << std::endl;
  std::cout << "Znunu weighted Nt_2muBox0Btag: " << Nt_2muBox0BTag << std::endl;

  std::cout << "Znunu Btag EVENTS: " << Nt_MR_RSQ_cut - Nt_MR_RSQ_cut0BTag << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "========================================" << "\n\n" << std::endl;
  
  return true;
  
  
};

TH1F ZJetsNuNu::PlotMR_1Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* MR1 = new TH1F("MR1", "MR1BOX", MR_Bins, MR_Low, MR_High);
  TH1F* MR1 = new TH1F("MR1", "MR1BOX", MR_Bins, MR_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX==1 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )MR1->Fill(MR, weight0);
  }
  
  T1->SetBranchAddress("RSQ", &RSQ);
  T1->SetBranchAddress("MR", &MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    if( BOX==1 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )MR1->Fill(MR, weight1);
  }

  T2->SetBranchAddress("RSQ", &RSQ);
  T2->SetBranchAddress("MR", &MR);
  T2->SetBranchAddress("BOX_NUM", &BOX);
  T2->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T2->GetEntries(); i++){
    T2->GetEntry(i);
    if( BOX==1 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )MR1->Fill(MR, weight2);
  }
  
  T3->SetBranchAddress("RSQ", &RSQ);
  T3->SetBranchAddress("MR", &MR);
  T3->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T3->GetEntries(); i++){
    T3->GetEntry(i);
    if( BOX==1 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )MR1->Fill(MR, weight3);
  }
  
  return *MR1;
};

TH1F ZJetsNuNu::PlotMR_0Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* MR0 = new TH1F("MR0", "MR0BOX", MR_Bins, MR_Low, MR_High);
  TH1F* MR0 = new TH1F("MR0", "MR0BOX", MR_Bins, MR_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)MR0->Fill(MR);
  }
  
  T1->SetBranchAddress("RSQ", &RSQ);
  T1->SetBranchAddress("MR", &MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)MR0->Fill(MR, weight1);
  }
  
  T2->SetBranchAddress("RSQ", &RSQ);
  T2->SetBranchAddress("MR", &MR);
  T2->SetBranchAddress("BOX_NUM", &BOX);
  T2->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T2->GetEntries(); i++){
    T2->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)MR0->Fill(MR, weight2);
  }
  
  T3->SetBranchAddress("RSQ", &RSQ);
  T3->SetBranchAddress("MR", &MR);
  T3->SetBranchAddress("BOX_NUM", &BOX);
  T3->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T3->GetEntries(); i++){
    T3->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)MR0->Fill(MR, weight3);
  }
  
  
  return *MR0;
};


TH1F  ZJetsNuNu::PlotRSQ_1Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* RSQ1 = new TH1F("RSQ1", "RSQ1BOX", RSQ_Bins, RSQ_Low, RSQ_High);
  TH1F* RSQ1 = new TH1F("RSQ1", "RSQ1BOX", RSQ_Bins, RSQ_BinArr);

  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ1->Fill(RSQ, weight0);
  }
  
  T1->SetBranchAddress("RSQ", &RSQ);
  T1->SetBranchAddress("MR", &MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ1->Fill(RSQ, weight1);
  }
  
  T2->SetBranchAddress("RSQ", &RSQ);
  T2->SetBranchAddress("MR", &MR);
  T2->SetBranchAddress("BOX_NUM", &BOX);
  T2->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T2->GetEntries(); i++){
    T2->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ1->Fill(RSQ, weight2);
  }
  
  T3->SetBranchAddress("RSQ", &RSQ);
  T3->SetBranchAddress("MR", &MR);
  T3->SetBranchAddress("BOX_NUM", &BOX);
  T3->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T3->GetEntries(); i++){
    T3->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ1->Fill(RSQ, weight3);
  }
  
 
  
  return *RSQ1;
  
};


TH1F  ZJetsNuNu::PlotRSQ_0Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH1F* RSQ0 = new TH1F("RSQ0", "RSQ0BOX", RSQ_Bins, RSQ_Low, RSQ_High);
  TH1F* RSQ0 = new TH1F("RSQ0", "RSQ0BOX", RSQ_Bins, RSQ_BinArr);
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ0->Fill(RSQ, weight0);
  }
  
  T1->SetBranchAddress("RSQ", &RSQ);
  T1->SetBranchAddress("MR", &MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ0->Fill(RSQ, weight1);
  }
  
  T2->SetBranchAddress("RSQ", &RSQ);
  T2->SetBranchAddress("MR", &MR);
  T2->SetBranchAddress("BOX_NUM", &BOX);
  T2->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T2->GetEntries(); i++){
    T2->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ0->Fill(RSQ, weight2);
  }
  
  T3->SetBranchAddress("RSQ", &RSQ);
  T3->SetBranchAddress("MR", &MR);
  T3->SetBranchAddress("BOX_NUM", &BOX);
  T3->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T3->GetEntries(); i++){
    T3->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0 )RSQ0->Fill(RSQ, weight3);
  }
  
  return *RSQ0;
  
};


TH2F ZJetsNuNu::PlotRSQ_vs_MR_0Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH2F* RSQ_MR_0BOX = new TH2F("RSQ_MR_0BOX", "RSQ_VS_MR_0BOX", MR_Bins, MR_Low, MR_High, RSQ_Bins, RSQ_Low, RSQ_High);
  TH2F* RSQ_MR_0BOX = new TH2F("RSQ_MR_0BOX", "RSQ_VS_MR_0BOX", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);
  
  SetBrachStatus();
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_0BOX->Fill(MR, RSQ, weight0);
  }
  
  T1->SetBranchAddress("RSQ", &RSQ);
  T1->SetBranchAddress("MR", &MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_0BOX->Fill(MR, RSQ, weight1);
  }
  
  T2->SetBranchAddress("RSQ", &RSQ);
  T2->SetBranchAddress("MR", &MR);
  T2->SetBranchAddress("BOX_NUM", &BOX);
  T2->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T2->GetEntries(); i++){
    T2->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_0BOX->Fill(MR, RSQ, weight2);
  }
  
  T3->SetBranchAddress("RSQ", &RSQ);
  T3->SetBranchAddress("MR", &MR);
  T3->SetBranchAddress("BOX_NUM", &BOX);
  T3->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T3->GetEntries(); i++){
    T3->GetEntry(i);
    if( BOX == 0 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_0BOX->Fill(MR, RSQ, weight3);
  }
  
  return *RSQ_MR_0BOX;
  
};

TH2F ZJetsNuNu::PlotRSQ_vs_MR_1Box(){
  
  double RSQ, MR;
  int BOX, nBtag;
  //TH2F* RSQ_MR_1BOX = new TH2F("RSQ_MR_1BOX", "RSQ_VS_MR_1BOX", MR_Bins, MR_Low, MR_High, RSQ_Bins, RSQ_Low, RSQ_High);
  TH2F* RSQ_MR_1BOX = new TH2F("RSQ_MR_1BOX", "RSQ_VS_MR_1BOX", MR_Bins, MR_BinArr, RSQ_Bins, RSQ_BinArr);
  SetBrachStatus();
  
  T->SetBranchAddress("RSQ", &RSQ);
  T->SetBranchAddress("MR", &MR);
  T->SetBranchAddress("BOX_NUM", &BOX);
  T->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T->GetEntries(); i++){
    T->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_1BOX->Fill(MR, RSQ, weight0);
  }
  
  T1->SetBranchAddress("RSQ", &RSQ);
  T1->SetBranchAddress("MR", &MR);
  T1->SetBranchAddress("BOX_NUM", &BOX);
  T1->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T1->GetEntries(); i++){
    T1->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_1BOX->Fill(MR, RSQ, weight1);
  }
  
  T2->SetBranchAddress("RSQ", &RSQ);
  T2->SetBranchAddress("MR", &MR);
  T2->SetBranchAddress("BOX_NUM", &BOX);
  T2->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T2->GetEntries(); i++){
    T2->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_1BOX->Fill(MR, RSQ, weight2);
  }
  
  T3->SetBranchAddress("RSQ", &RSQ);
  T3->SetBranchAddress("MR", &MR);
  T3->SetBranchAddress("BOX_NUM", &BOX);
  T3->SetBranchAddress("nBtag", &nBtag);
  for(int i = 0; i < T3->GetEntries(); i++){
    T3->GetEntry(i);
    if( BOX == 1 && RSQ > RSQMin && MR > MRMin && nBtag == 0)RSQ_MR_1BOX->Fill(MR, RSQ, weight3);
  }
  
  return *RSQ_MR_1BOX;
  
};


bool ZJetsNuNu::SetBrachStatus(){

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

  T1->SetBranchStatus("*",0); //disable all branches
  T1->SetBranchStatus("RSQ",1);
  T1->SetBranchStatus("MR",1);
  T1->SetBranchStatus("BOX_NUM",1);
  T1->SetBranchStatus("nBtag",1);
  T1->SetBranchStatus("ht",1);
  T1->SetBranchStatus("metX",1);
  T1->SetBranchStatus("metY",1);
  T1->SetBranchStatus("metCorrX",1);
  T1->SetBranchStatus("metCorrY",1);
  
  T2->SetBranchStatus("*",0); //disable all branches
  T2->SetBranchStatus("RSQ",1);
  T2->SetBranchStatus("MR",1);
  T2->SetBranchStatus("BOX_NUM",1);
  T2->SetBranchStatus("nBtag",1);
  T2->SetBranchStatus("ht",1);
  T2->SetBranchStatus("metX",1);
  T2->SetBranchStatus("metY",1);
  T2->SetBranchStatus("metCorrX",1);
  T2->SetBranchStatus("metCorrY",1);
  
  T3->SetBranchStatus("*",0); //disable all branches
  T3->SetBranchStatus("RSQ",1);
  T3->SetBranchStatus("MR",1);
  T3->SetBranchStatus("BOX_NUM",1);
  T3->SetBranchStatus("nBtag",1);
  //T3->SetBranchStatus("ht",1);
  //T3->SetBranchStatus("metX",1);
  //T3->SetBranchStatus("metY",1);
  //T3->SetBranchStatus("metCorrX",1);
  //T3->SetBranchStatus("metCorrY",1);

};
