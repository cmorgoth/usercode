#include <iostream>
#include "PhosphorCorrectorFunctor.hh"
#include "muon_corr_2012.hh"
#include <math.h>
#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"

int main(){
  
  zgamma::PhosphorCorrectionFunctor* obj = new zgamma::PhosphorCorrectionFunctor("phosphor_numbers_oct9.txt");
  
  //Rochester corrections for Muons Creating an Object
  rochcor *rmcor = new rochcor();
  
  TLorentzVector genmu; //TLorentzVector of the generated muon- : only forMC
  TLorentzVector genmubar; //TLorentzVector of the generated muon+ : only for MC
  TLorentzVector mu; //TLorentzVector of the reconstructed muon-
  TLorentzVector mubar; //TLorentzVector of the reconstructed muon+
  
  TLorentzVector* mmFV;//FV: Four Vector
  
  TFile *oldfile = new TFile("/afs/cern.ch/work/s/sixie/public/EnergyScaleAndResolution/ZmumuGammaEvents/WithPhotonRegression/ZmumuGammaNtuple_DYM50.root");
  TTree *oldtree = (TTree*)oldfile->Get("ZmumuGammaEvent");
  long nentries = oldtree->GetEntries();
  
  float PhoPt, PhoEta, GenPhoE, mmg, mm, Mu1Pt, Mu1Phi, Mu1Eta, Mu2Pt,\
    Mu2Eta, Mu2Phi, GenMu1Pt, GenMu1Eta, GenMu1Phi, GenMu2Pt, GenMu2Eta, \
    GenMu2Phi, Mu1Charge, Mu2Charge;
  bool IsFSR;

  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile("SIXIE_LAST_VERSION/PhotonRegression/ZmumuGammaNtuple_DYM50_MuCorr.root","recreate");
  TTree *newtree = oldtree->CloneTree(0);

  float PhoPt_new, mmg_new, mm_new, Mu1Pt_new, Mu1Eta_new, Mu1Phi_new, Mu2Pt_new, Mu2Eta_new, Mu2Phi_new;
 
  oldtree->SetBranchAddress("Mass", &mmg);  
  oldtree->SetBranchAddress("PhotonPt", &PhoPt);
  oldtree->SetBranchAddress("PhotonEta", &PhoEta);
  oldtree->SetBranchAddress("GenPhoE", &GenPhoE);
  oldtree->SetBranchAddress("Mass", &mmg);
  oldtree->SetBranchAddress("DileptonMass", &mm);
  oldtree->SetBranchAddress("IsFSR", &IsFSR);
  oldtree->SetBranchAddress("Mu1Pt", &Mu1Pt);
  oldtree->SetBranchAddress("Mu1Charge", &Mu1Charge);
  oldtree->SetBranchAddress("Mu1Eta", &Mu1Eta);
  oldtree->SetBranchAddress("Mu1Phi", &Mu1Phi);
  oldtree->SetBranchAddress("Mu2Charge", &Mu2Charge);
  oldtree->SetBranchAddress("Mu2Pt", &Mu2Pt);
  oldtree->SetBranchAddress("Mu2Eta", &Mu2Eta);
  oldtree->SetBranchAddress("Mu2Phi", &Mu2Phi);
  oldtree->SetBranchAddress("GenMu1Pt", &GenMu1Pt);
  oldtree->SetBranchAddress("GenMu1Eta", &GenMu1Eta);
  oldtree->SetBranchAddress("GenMu1Phi", &GenMu1Phi);
  oldtree->SetBranchAddress("GenMu2Pt", &GenMu2Pt);
  oldtree->SetBranchAddress("GenMu2Eta", &GenMu2Eta);
  oldtree->SetBranchAddress("GenMu2Phi", &GenMu2Phi);
  //New Variables Used
  //3-body invariant mass
  newtree->SetBranchAddress("Mass", &mmg_new);
  //Photon Energy or Pt(whatever you like since PhotonEta is not corrected)
  newtree->SetBranchAddress("PhotonPt", &PhoPt_new);
  
  
  //Muon variables and Dimuon Invariant Mass
  newtree->SetBranchAddress("DileptonMass", &mm_new);
  newtree->SetBranchAddress("Mu1Pt", &Mu1Pt_new);
  newtree->SetBranchAddress("Mu1Eta", &Mu1Eta_new);
  newtree->SetBranchAddress("Mu1Phi", &Mu1Phi_new);
  newtree->SetBranchAddress("Mu2Pt", &Mu2Pt_new);
  newtree->SetBranchAddress("Mu2Eta", &Mu2Eta_new);
  newtree->SetBranchAddress("Mu2Phi", &Mu2Phi_new);
  
    
  for (long i = 0; i < nentries; i++) {
    oldtree->GetEntry(i);
    
    std::cout << "M1:  " <<  Mu1Charge << std::endl;
    std::cout << "M2:  " <<  Mu2Charge << std::endl;
    std::cout << "M1 PT:  " << Mu1Pt << std::endl;
    std::cout << "M2 PT:  " << Mu2Pt << std::endl;

    if(Mu1Charge == -1 && Mu2Charge == 1){
      mu.SetPxPyPzE( Mu1Pt*cos(Mu1Phi),				\
		     Mu1Pt*sin(Mu1Phi),				\
		     Mu1Pt*sinh(Mu1Eta),			\
		     Mu1Pt*cosh(Mu1Eta) );
      
      mubar.SetPxPyPzE( Mu2Pt*cos(Mu2Phi),     \
			Mu2Pt*sin(Mu2Phi),     \
			Mu2Pt*sinh(Mu2Eta),    \
			Mu2Pt*cosh(Mu2Eta) );
      
      genmu.SetPxPyPzE( GenMu1Pt*cos(GenMu1Phi),	\
			GenMu1Pt*sin(GenMu1Phi),	\
			GenMu1Pt*sinh(GenMu1Eta),	\
			GenMu1Pt*cosh(GenMu1Eta));
      
      genmubar.SetPxPyPzE( GenMu2Pt*cos(GenMu2Phi),	\
			   GenMu2Pt*sin(GenMu2Phi),	\
			   GenMu2Pt*sinh(GenMu2Eta),	\
			   GenMu2Pt*cosh(GenMu2Eta) );

      rmcor->momcor_mc(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_mc(mubar, 1., 0, 0); // for positive reconstructed muon
      Mu1Pt_new = mu.Pt();
      Mu1Eta_new = mu.Eta();
      Mu1Phi_new = mu.Phi();
      Mu2Pt_new = mubar.Pt();
      Mu2Eta_new = mubar.Eta();
      Mu2Phi_new = mubar.Phi();
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else if(Mu1Charge == 1 && Mu2Charge == -1){
      mubar.SetPxPyPzE( Mu1Pt*cos(Mu1Phi),				\
			Mu1Pt*sin(Mu1Phi),				\
			Mu1Pt*sinh(Mu1Eta),				\
			Mu1Pt*cosh(Mu1Eta) );
      
      mu.SetPxPyPzE( Mu2Pt*cos(Mu2Phi),	       \
		     Mu2Pt*sin(Mu2Phi),	       \
		     Mu2Pt*sinh(Mu2Eta),       \
		     Mu2Pt*cosh(Mu2Eta) );
      
      genmubar.SetPxPyPzE( GenMu1Pt*cos(GenMu1Phi),	\
			   GenMu1Pt*sin(GenMu1Phi),	\
			   GenMu1Pt*sinh(GenMu1Eta),	\
			   GenMu1Pt*cosh(GenMu1Eta));
      
      genmu.SetPxPyPzE( GenMu2Pt*cos(GenMu2Phi),	\
			GenMu2Pt*sin(GenMu2Phi),	\
			GenMu2Pt*sinh(GenMu2Eta),	\
			GenMu2Pt*cosh(GenMu2Eta) );
      
      rmcor->momcor_mc(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_mc(mubar, 1., 0, 0); // for positive reconstructed muon
      Mu1Pt_new = mubar.Pt();
      Mu1Eta_new = mubar.Eta();
      Mu1Phi_new = mubar.Phi();
      Mu2Pt_new = mu.Pt();
      Mu2Eta_new = mu.Eta();
      Mu2Phi_new = mu.Phi();
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else{
      std::cout << "[INFO]--> No mu-mu+ pair was found!!, No correction applied" << std::endl;
      mm_new = mm;//No correction applied
      Mu1Pt_new = Mu1Pt;
      Mu1Eta_new = Mu1Eta;
      Mu1Phi_new = Mu1Phi;
      Mu2Pt_new = Mu2Pt;
      Mu2Eta_new = Mu2Eta;
      Mu2Phi_new = Mu2Phi;
    }
    
    //std::cout << "Prev: " << mu.Et()<< std::endl;
    //rmcor->momcor_mc(mu, -1., 0, 0);// for negative reconstructed muon
    
    // rmcor->momcor_mc(mubar, 1., 0, 0); // for positive reconstructed muon 
    //std::cout << "Prev: " << mu.Et()<< std::endl;
    //rmcor->momcor_mc(mu, mubar, 0, 0);
    //std::cout << "Post: " << mu.Et()<< std::endl;
    
    //mmFV = new TLorentzVector(mu+mubar);
    
    //std::cout << "Mass before: " << mm << std::endl;
    //std::cout << "Mass before: " << mmFV->M() << std::endl;
    //mm_new =  mmFV->M();
      
    if(IsFSR == 1 && PhoPt > 10.0  && GenPhoE != -1){// isFSR 
      //PhoPt_new = obj->GetCorrEt(2012, PhoPt, PhoEta, GenPhoE);
      //mmg_new = sqrt( mm*mm + (mmg*mmg - mm*mm)*(obj->ETtoE(PhoPt_new,PhoEta)/obj->ETtoE(PhoPt, PhoEta) ) );//Without Muon Corrections
      PhoPt_new = PhoPt;//Muon Correction Version(No photon correction at all)
      mmg_new = sqrt( mm_new*mm_new + (mmg*mmg - mm*mm) );
    }else{
      //PhoPt_new = obj->GetCorrEt(2012, PhoPt, PhoEta, 0);//Overloading method from data you can indicate data type in last argument mc->0 data->1    
      //mmg_new = sqrt( mm*mm + (mmg*mmg - mm*mm)*(obj->ETtoE(PhoPt_new,PhoEta)/obj->ETtoE(PhoPt, PhoEta) ) );
      PhoPt_new = PhoPt;//Muon Correction Version(No photon correction at all)
      mmg_new = sqrt( mm_new*mm_new + (mmg*mmg - mm*mm) );
    }
    
    std::cout << "Mgg before: " << mmg << std::endl;
    std::cout << "Mgg before: " << mmg_new << std::endl;
    if(PhoPt_new < .0 ){
      std::cout << "blah" << " NewPt: " << PhoPt_new << " less than zero  " <<PhoEta << " " << GenPhoE << std::endl;
    }else{
      newtree->Fill();
    }
    

    
  }
  newtree->Print();
  newtree->AutoSave();
  delete oldfile;
  delete newfile;
  
  
  oldfile = new TFile("/afs/cern.ch/work/s/sixie/public/EnergyScaleAndResolution/ZmumuGammaEvents/WithPhotonRegression/ZmumuGammaNtuple_Run2012C.root");
  oldtree = (TTree*)oldfile->Get("ZmumuGammaEvent");
  nentries = oldtree->GetEntries();

  
  //Create a new file + a clone of old tree in new file
  newfile = new TFile("SIXIE_LAST_VERSION/PhotonRegression/ZmumuGammaNtuple_Run2012C_MuCorr.root","recreate");
  newtree = oldtree->CloneTree(0);
  
  oldtree->SetBranchAddress("Mass", &mmg);  
  oldtree->SetBranchAddress("PhotonPt", &PhoPt);
  oldtree->SetBranchAddress("PhotonEta", &PhoEta);
  oldtree->SetBranchAddress("GenPhoE", &GenPhoE);
  oldtree->SetBranchAddress("Mass", &mmg);
  oldtree->SetBranchAddress("DileptonMass", &mm);
  oldtree->SetBranchAddress("IsFSR", &IsFSR);
  oldtree->SetBranchAddress("Mu1Pt", &Mu1Pt);
  oldtree->SetBranchAddress("Mu1Charge", &Mu1Charge);
  oldtree->SetBranchAddress("Mu1Eta", &Mu1Eta);
  oldtree->SetBranchAddress("Mu1Phi", &Mu1Phi);
  oldtree->SetBranchAddress("Mu2Charge", &Mu2Charge);
  oldtree->SetBranchAddress("Mu2Pt", &Mu2Pt);
  oldtree->SetBranchAddress("Mu2Eta", &Mu2Eta);
  oldtree->SetBranchAddress("Mu2Phi", &Mu2Phi);
  oldtree->SetBranchAddress("GenMu1Pt", &GenMu1Pt);
  oldtree->SetBranchAddress("GenMu1Eta", &GenMu1Eta);
  oldtree->SetBranchAddress("GenMu1Phi", &GenMu1Phi);
  oldtree->SetBranchAddress("GenMu2Pt", &GenMu2Pt);
  oldtree->SetBranchAddress("GenMu2Eta", &GenMu2Eta);
  oldtree->SetBranchAddress("GenMu2Phi", &GenMu2Phi);
  //New Variables Used
  //3-body invariant mass
  newtree->SetBranchAddress("Mass", &mmg_new);
  //Photon Energy or Pt(whatever you like since PhotonEta is not corrected)
  newtree->SetBranchAddress("PhotonPt", &PhoPt_new);
  
  
  //Muon variables and Dimuon Invariant Mass
  newtree->SetBranchAddress("DileptonMass", &mm_new);
  newtree->SetBranchAddress("Mu1Pt", &Mu1Pt_new);
  newtree->SetBranchAddress("Mu1Eta", &Mu1Eta_new);
  newtree->SetBranchAddress("Mu1Phi", &Mu1Phi_new);
  newtree->SetBranchAddress("Mu2Pt", &Mu2Pt_new);
  newtree->SetBranchAddress("Mu2Eta", &Mu2Eta_new);
  newtree->SetBranchAddress("Mu2Phi", &Mu2Phi_new);
  
  
  for (long i = 0; i < nentries; i++) {
    oldtree->GetEntry(i); 
    
    std::cout << "M1:  " <<  Mu1Charge << std::endl;
    std::cout << "M2:  " <<  Mu2Charge << std::endl;
    std::cout << "M1 PT:  " << Mu1Pt << std::endl;
    std::cout << "M2 PT:  " << Mu2Pt << std::endl;
    
    if(Mu1Charge == -1 && Mu2Charge == 1){
      mu.SetPxPyPzE( Mu1Pt*cos(Mu1Phi),				\
		     Mu1Pt*sin(Mu1Phi),				\
		     Mu1Pt*sinh(Mu1Eta),			\
		     Mu1Pt*cosh(Mu1Eta) );
      
      mubar.SetPxPyPzE( Mu2Pt*cos(Mu2Phi),     \
			Mu2Pt*sin(Mu2Phi),     \
			Mu2Pt*sinh(Mu2Eta),    \
			Mu2Pt*cosh(Mu2Eta) );
      
      genmu.SetPxPyPzE( GenMu1Pt*cos(GenMu1Phi),	\
			GenMu1Pt*sin(GenMu1Phi),	\
			GenMu1Pt*sinh(GenMu1Eta),	\
			GenMu1Pt*cosh(GenMu1Eta));
      
      genmubar.SetPxPyPzE( GenMu2Pt*cos(GenMu2Phi),	\
			   GenMu2Pt*sin(GenMu2Phi),	\
			   GenMu2Pt*sinh(GenMu2Eta),	\
			   GenMu2Pt*cosh(GenMu2Eta) );
      
      rmcor->momcor_data(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_data(mubar, 1., 0, 0); // for positive reconstructed muon
      Mu1Pt_new = mu.Pt();
      Mu1Eta_new = mu.Eta();
      Mu1Phi_new = mu.Phi();
      Mu2Pt_new = mubar.Pt();
      Mu2Eta_new = mubar.Eta();
      Mu2Phi_new = mubar.Phi();
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else if(Mu1Charge == 1 && Mu2Charge == -1){
      mubar.SetPxPyPzE( Mu1Pt*cos(Mu1Phi),				\
			Mu1Pt*sin(Mu1Phi),				\
			Mu1Pt*sinh(Mu1Eta),				\
			Mu1Pt*cosh(Mu1Eta) );
      
      mu.SetPxPyPzE( Mu2Pt*cos(Mu2Phi),	       \
		     Mu2Pt*sin(Mu2Phi),	       \
		     Mu2Pt*sinh(Mu2Eta),       \
		     Mu2Pt*cosh(Mu2Eta) );
      
      genmubar.SetPxPyPzE( GenMu1Pt*cos(GenMu1Phi),	\
			   GenMu1Pt*sin(GenMu1Phi),	\
			   GenMu1Pt*sinh(GenMu1Eta),	\
			   GenMu1Pt*cosh(GenMu1Eta));
      
      genmu.SetPxPyPzE( GenMu2Pt*cos(GenMu2Phi),	\
			GenMu2Pt*sin(GenMu2Phi),	\
			GenMu2Pt*sinh(GenMu2Eta),	\
			GenMu2Pt*cosh(GenMu2Eta) );
      
      rmcor->momcor_data(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_data(mubar, 1., 0, 0); // for positive reconstructed muon
      Mu1Pt_new = mubar.Pt();
      Mu1Eta_new = mubar.Eta();
      Mu1Phi_new = mubar.Phi();
      Mu2Pt_new = mu.Pt();
      Mu2Eta_new = mu.Eta();
      Mu2Phi_new = mu.Phi();
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else{
      std::cout << "[INFO]--> No mu-mu+ pair was found!!, No correction applied" << std::endl;
      mm_new = mm;//No correction applied
      Mu1Pt_new = Mu1Pt;
      Mu1Eta_new = Mu1Eta;
      Mu1Phi_new = Mu1Phi;
      Mu2Pt_new = Mu2Pt;
      Mu2Eta_new = Mu2Eta;
      Mu2Phi_new = Mu2Phi;
    }
    //PhoPt_new = obj->GetCorrEt(2012, PhoPt, PhoEta);
    
    //mmg_new = sqrt( mm*mm + (mmg*mmg - mm*mm)*(obj->ETtoE(PhoPt_new,PhoEta)/obj->ETtoE(PhoPt, PhoEta) ) );//Photon Energy Correction
    PhoPt_new = PhoPt;//Muon Correction Version(No photon correction at all)
    mmg_new = sqrt( mm_new*mm_new + (mmg*mmg - mm*mm) );//Muon Correction
    newtree->Fill();
    
  }
  newtree->Print();
  newtree->AutoSave();
  delete oldfile;
  delete newfile;
}
