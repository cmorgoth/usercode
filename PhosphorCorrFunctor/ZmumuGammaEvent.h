//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Feb 24 03:19:01 2013 by ROOT version 5.32/00
// from TTree ZmumuGammaEvent/ZmumuGammaEvent
// found on file: ZmumuGammaNtuple_Run2012CForHCP.root
//////////////////////////////////////////////////////////

#ifndef ZmumuGammaEvent_h
#define ZmumuGammaEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class ZmumuGammaEvent {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         Weight;
   UInt_t          RunNumber;
   UInt_t          LumiSectionNumber;
   UInt_t          EventNumber;
   UInt_t          NPU;
   Float_t         Rho;
   UInt_t          NVertices;
   Float_t         Mass;
   Float_t         DileptonMass;
   Float_t         PhotonPt;
   Float_t         PhotonEta;
   Float_t         PhotonPhi;
   Float_t         PhotonR9;
   Float_t         PhotonIsEB;
   Float_t         PhotonHoE;
   Float_t         SCEt;
   Float_t         SCE;
   Float_t         SCRawE;
   Float_t         SCEta;
   Float_t         SCEtaWidth;
   Float_t         SCPhiWidth;
   Float_t         PhoToTrackDeltaR;
   Float_t         PhoPassElectronVeto;
   Float_t         PhoHasMatchedConversion;
   Float_t         PhoHasPixelMatch;
   Float_t         PhoSigmaIEtaIEta;
   Float_t         PhoTrackIso;
   Float_t         PhoEcalIso;
   Float_t         PhoHcalIso;
   Float_t         PhoPdgId;
   Float_t         PhoCrackCorr;
   Float_t         Mu1Pt;
   Float_t         Mu1Eta;
   Float_t         Mu1Phi;
   Float_t         Mu1Charge;
   Float_t         Mu1TrackChi2;
   Float_t         Mu1TrackNormalizedChi2;
   Float_t         Mu1DeltaR;
   Float_t         Mu1CalEnergyEm;
   Float_t         Mu1CalEnergyEmMax;
   Float_t         Mu1CalEnergyEmHad;
   Float_t         Mu2Pt;
   Float_t         Mu2Eta;
   Float_t         Mu2Phi;
   Float_t         Mu2Charge;
   Float_t         Mu2TrackChi2;
   Float_t         Mu2TrackNormalizedChi2;
   Float_t         Mu2DeltaR;
   Float_t         Mu2CalEnergyEm;
   Float_t         Mu2CalEnergyEmMax;
   Float_t         Mu2CalEnergyEmHad;
   Float_t         MinDeltaEta;
   Float_t         MinDeltaR;
   Float_t         MinDeltaPhi;
   Float_t         kRatio;
   Float_t         PreshowerE;
   Float_t         GenMu1Pt;
   Float_t         GenMu1Eta;
   Float_t         GenMu1Phi;
   Float_t         GenMu2Pt;
   Float_t         GenMu2Eta;
   Float_t         GenMu2Phi;
   Float_t         GenPhoE;
   Float_t         GenPhoEt;
   Float_t         GenPhoEta;
   Float_t         GenPhoPhi;
   Float_t         GenPhoMotherPdgId;
   Bool_t          IsFSR;
   Bool_t          IsISR;
   Int_t           PhoIEtaX;
   Int_t           PhoIPhiY;
   Int_t           MuNearIEtaX;
   Int_t           MuNearIPhiY;
   Bool_t          MuNearIsEB;
   Int_t           MuNearIndex;

   // List of branches
   TBranch        *b_Weight;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_LumiSectionNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_NPU;   //!
   TBranch        *b_Rho;   //!
   TBranch        *b_NVertices;   //!
   TBranch        *b_Mass;   //!
   TBranch        *b_DileptonMass;   //!
   TBranch        *b_PhotonPt;   //!
   TBranch        *b_PhotonEta;   //!
   TBranch        *b_PhotonPhi;   //!
   TBranch        *b_PhotonR9;   //!
   TBranch        *b_PhotonIsEB;   //!
   TBranch        *b_PhotonHoE;   //!
   TBranch        *b_SCEt;   //!
   TBranch        *b_SCE;   //!
   TBranch        *b_SCRawE;   //!
   TBranch        *b_SCEta;   //!
   TBranch        *b_SCEtaWidth;   //!
   TBranch        *b_SCPhiWidth;   //!
   TBranch        *b_PhoToTrackDeltaR;   //!
   TBranch        *b_PhoPassElectronVeto;   //!
   TBranch        *b_PhoHasMatchedConversion;   //!
   TBranch        *b_PhoHasPixelMatch;   //!
   TBranch        *b_PhoSigmaIEtaIEta;   //!
   TBranch        *b_PhoTrackIso;   //!
   TBranch        *b_PhoEcalIso;   //!
   TBranch        *b_PhoHcalIso;   //!
   TBranch        *b_PhoPdgId;   //!
   TBranch        *b_PhoCrackCorr;   //!
   TBranch        *b_Mu1Pt;   //!
   TBranch        *b_Mu1Eta;   //!
   TBranch        *b_Mu1Phi;   //!
   TBranch        *b_Mu1Charge;   //!
   TBranch        *b_Mu1TrackChi2;   //!
   TBranch        *b_Mu1TrackNormalizedChi2;   //!
   TBranch        *b_Mu1DeltaR;   //!
   TBranch        *b_Mu1CalEnergyEm;   //!
   TBranch        *b_Mu1CalEnergyEmMax;   //!
   TBranch        *b_Mu1CalEnergyEmHad;   //!
   TBranch        *b_Mu2Pt;   //!
   TBranch        *b_Mu2Eta;   //!
   TBranch        *b_Mu2Phi;   //!
   TBranch        *b_Mu2Charge;   //!
   TBranch        *b_Mu2TrackChi2;   //!
   TBranch        *b_Mu2TrackNormalizedChi2;   //!
   TBranch        *b_Mu2DeltaR;   //!
   TBranch        *b_Mu2CalEnergyEm;   //!
   TBranch        *b_Mu2CalEnergyEmMax;   //!
   TBranch        *b_Mu2CalEnergyEmHad;   //!
   TBranch        *b_MinDeltaEta;   //!
   TBranch        *b_MinDeltaR;   //!
   TBranch        *b_MinDeltaPhi;   //!
   TBranch        *b_kRatio;   //!
   TBranch        *b_PreshowerE;   //!
   TBranch        *b_GenMu1Pt;   //!
   TBranch        *b_GenMu1Eta;   //!
   TBranch        *b_GenMu1Phi;   //!
   TBranch        *b_GenMu2Pt;   //!
   TBranch        *b_GenMu2Eta;   //!
   TBranch        *b_GenMu2Phi;   //!
   TBranch        *b_GenPhoE;   //!
   TBranch        *b_GenPhoEt;   //!
   TBranch        *b_GenPhoEta;   //!
   TBranch        *b_GenPhoPhi;   //!
   TBranch        *b_GenPhoMotherPdgId;   //!
   TBranch        *b_IsFSR;   //!
   TBranch        *b_IsISR;   //!
   TBranch        *b_PhoIEtaX;   //!
   TBranch        *b_PhoIPhiY;   //!
   TBranch        *b_MuNearIEtaX;   //!
   TBranch        *b_MuNearIPhiY;   //!
   TBranch        *b_MuNearIsEB;   //!
   TBranch        *b_MuNearIndex;   //!

   ZmumuGammaEvent(TTree *tree=0);
   virtual ~ZmumuGammaEvent();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZmumuGammaEvent_cxx
ZmumuGammaEvent::ZmumuGammaEvent(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ZmumuGammaNtuple_Run2012CForHCP.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ZmumuGammaNtuple_Run2012CForHCP.root");
      }
      f->GetObject("ZmumuGammaEvent",tree);

   }
   Init(tree);
}

ZmumuGammaEvent::~ZmumuGammaEvent()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ZmumuGammaEvent::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ZmumuGammaEvent::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ZmumuGammaEvent::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("LumiSectionNumber", &LumiSectionNumber, &b_LumiSectionNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("NPU", &NPU, &b_NPU);
   fChain->SetBranchAddress("Rho", &Rho, &b_Rho);
   fChain->SetBranchAddress("NVertices", &NVertices, &b_NVertices);
   fChain->SetBranchAddress("Mass", &Mass, &b_Mass);
   fChain->SetBranchAddress("DileptonMass", &DileptonMass, &b_DileptonMass);
   fChain->SetBranchAddress("PhotonPt", &PhotonPt, &b_PhotonPt);
   fChain->SetBranchAddress("PhotonEta", &PhotonEta, &b_PhotonEta);
   fChain->SetBranchAddress("PhotonPhi", &PhotonPhi, &b_PhotonPhi);
   fChain->SetBranchAddress("PhotonR9", &PhotonR9, &b_PhotonR9);
   fChain->SetBranchAddress("PhotonIsEB", &PhotonIsEB, &b_PhotonIsEB);
   fChain->SetBranchAddress("PhotonHoE", &PhotonHoE, &b_PhotonHoE);
   fChain->SetBranchAddress("SCEt", &SCEt, &b_SCEt);
   fChain->SetBranchAddress("SCE", &SCE, &b_SCE);
   fChain->SetBranchAddress("SCRawE", &SCRawE, &b_SCRawE);
   fChain->SetBranchAddress("SCEta", &SCEta, &b_SCEta);
   fChain->SetBranchAddress("SCEtaWidth", &SCEtaWidth, &b_SCEtaWidth);
   fChain->SetBranchAddress("SCPhiWidth", &SCPhiWidth, &b_SCPhiWidth);
   fChain->SetBranchAddress("PhoToTrackDeltaR", &PhoToTrackDeltaR, &b_PhoToTrackDeltaR);
   fChain->SetBranchAddress("PhoPassElectronVeto", &PhoPassElectronVeto, &b_PhoPassElectronVeto);
   fChain->SetBranchAddress("PhoHasMatchedConversion", &PhoHasMatchedConversion, &b_PhoHasMatchedConversion);
   fChain->SetBranchAddress("PhoHasPixelMatch", &PhoHasPixelMatch, &b_PhoHasPixelMatch);
   fChain->SetBranchAddress("PhoSigmaIEtaIEta", &PhoSigmaIEtaIEta, &b_PhoSigmaIEtaIEta);
   fChain->SetBranchAddress("PhoTrackIso", &PhoTrackIso, &b_PhoTrackIso);
   fChain->SetBranchAddress("PhoEcalIso", &PhoEcalIso, &b_PhoEcalIso);
   fChain->SetBranchAddress("PhoHcalIso", &PhoHcalIso, &b_PhoHcalIso);
   fChain->SetBranchAddress("PhoPdgId", &PhoPdgId, &b_PhoPdgId);
   fChain->SetBranchAddress("PhoCrackCorr", &PhoCrackCorr, &b_PhoCrackCorr);
   fChain->SetBranchAddress("Mu1Pt", &Mu1Pt, &b_Mu1Pt);
   fChain->SetBranchAddress("Mu1Eta", &Mu1Eta, &b_Mu1Eta);
   fChain->SetBranchAddress("Mu1Phi", &Mu1Phi, &b_Mu1Phi);
   fChain->SetBranchAddress("Mu1Charge", &Mu1Charge, &b_Mu1Charge);
   fChain->SetBranchAddress("Mu1TrackChi2", &Mu1TrackChi2, &b_Mu1TrackChi2);
   fChain->SetBranchAddress("Mu1TrackNormalizedChi2", &Mu1TrackNormalizedChi2, &b_Mu1TrackNormalizedChi2);
   fChain->SetBranchAddress("Mu1DeltaR", &Mu1DeltaR, &b_Mu1DeltaR);
   fChain->SetBranchAddress("Mu1CalEnergyEm", &Mu1CalEnergyEm, &b_Mu1CalEnergyEm);
   fChain->SetBranchAddress("Mu1CalEnergyEmMax", &Mu1CalEnergyEmMax, &b_Mu1CalEnergyEmMax);
   fChain->SetBranchAddress("Mu1CalEnergyEmHad", &Mu1CalEnergyEmHad, &b_Mu1CalEnergyEmHad);
   fChain->SetBranchAddress("Mu2Pt", &Mu2Pt, &b_Mu2Pt);
   fChain->SetBranchAddress("Mu2Eta", &Mu2Eta, &b_Mu2Eta);
   fChain->SetBranchAddress("Mu2Phi", &Mu2Phi, &b_Mu2Phi);
   fChain->SetBranchAddress("Mu2Charge", &Mu2Charge, &b_Mu2Charge);
   fChain->SetBranchAddress("Mu2TrackChi2", &Mu2TrackChi2, &b_Mu2TrackChi2);
   fChain->SetBranchAddress("Mu2TrackNormalizedChi2", &Mu2TrackNormalizedChi2, &b_Mu2TrackNormalizedChi2);
   fChain->SetBranchAddress("Mu2DeltaR", &Mu2DeltaR, &b_Mu2DeltaR);
   fChain->SetBranchAddress("Mu2CalEnergyEm", &Mu2CalEnergyEm, &b_Mu2CalEnergyEm);
   fChain->SetBranchAddress("Mu2CalEnergyEmMax", &Mu2CalEnergyEmMax, &b_Mu2CalEnergyEmMax);
   fChain->SetBranchAddress("Mu2CalEnergyEmHad", &Mu2CalEnergyEmHad, &b_Mu2CalEnergyEmHad);
   fChain->SetBranchAddress("MinDeltaEta", &MinDeltaEta, &b_MinDeltaEta);
   fChain->SetBranchAddress("MinDeltaR", &MinDeltaR, &b_MinDeltaR);
   fChain->SetBranchAddress("MinDeltaPhi", &MinDeltaPhi, &b_MinDeltaPhi);
   fChain->SetBranchAddress("kRatio", &kRatio, &b_kRatio);
   fChain->SetBranchAddress("PreshowerE", &PreshowerE, &b_PreshowerE);
   fChain->SetBranchAddress("GenMu1Pt", &GenMu1Pt, &b_GenMu1Pt);
   fChain->SetBranchAddress("GenMu1Eta", &GenMu1Eta, &b_GenMu1Eta);
   fChain->SetBranchAddress("GenMu1Phi", &GenMu1Phi, &b_GenMu1Phi);
   fChain->SetBranchAddress("GenMu2Pt", &GenMu2Pt, &b_GenMu2Pt);
   fChain->SetBranchAddress("GenMu2Eta", &GenMu2Eta, &b_GenMu2Eta);
   fChain->SetBranchAddress("GenMu2Phi", &GenMu2Phi, &b_GenMu2Phi);
   fChain->SetBranchAddress("GenPhoE", &GenPhoE, &b_GenPhoE);
   fChain->SetBranchAddress("GenPhoEt", &GenPhoEt, &b_GenPhoEt);
   fChain->SetBranchAddress("GenPhoEta", &GenPhoEta, &b_GenPhoEta);
   fChain->SetBranchAddress("GenPhoPhi", &GenPhoPhi, &b_GenPhoPhi);
   fChain->SetBranchAddress("GenPhoMotherPdgId", &GenPhoMotherPdgId, &b_GenPhoMotherPdgId);
   fChain->SetBranchAddress("IsFSR", &IsFSR, &b_IsFSR);
   fChain->SetBranchAddress("IsISR", &IsISR, &b_IsISR);
   fChain->SetBranchAddress("PhoIEtaX", &PhoIEtaX, &b_PhoIEtaX);
   fChain->SetBranchAddress("PhoIPhiY", &PhoIPhiY, &b_PhoIPhiY);
   fChain->SetBranchAddress("MuNearIEtaX", &MuNearIEtaX, &b_MuNearIEtaX);
   fChain->SetBranchAddress("MuNearIPhiY", &MuNearIPhiY, &b_MuNearIPhiY);
   fChain->SetBranchAddress("MuNearIsEB", &MuNearIsEB, &b_MuNearIsEB);
   fChain->SetBranchAddress("MuNearIndex", &MuNearIndex, &b_MuNearIndex);
   Notify();
}

Bool_t ZmumuGammaEvent::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZmumuGammaEvent::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ZmumuGammaEvent::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ZmumuGammaEvent_cxx
