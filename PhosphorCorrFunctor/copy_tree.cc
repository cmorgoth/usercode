#include <iostream>
#include "PhosphorCorrectorFunctor.hh"
#include "muon_corr_2011.hh"
#include <math.h>
#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TRandom3.h"


int main(){
  
 zgamma::PhosphorCorrectionFunctor* obj = \
   new zgamma::PhosphorCorrectionFunctor("PhosphorNumbersMuonCorrections.txt");

  //std::cout << obj->GetScaleCorr(2011, 15.5, 1.23) << std::endl;
  //std::cout << "MC EXAMPLE CORRECTION, Corrected energy:" << obj->GetCorrEnergy(2012, 14., -1.23, 25.6) << std::endl;
  //std::cout << "DATA EXAMPLE CORRECTION, Corrected energy:" << obj->GetCorrEnergy(2012, 14., -1.23) << std::endl;

  //std::cout << "DATA EXAMPLE CORRECTION, Corrected ET:" << obj->GetCorrEt(2012, 14., -1.23) << std::endl;

  //std::cout << "DATA EXAMPLE CORRECTION, Corrected ET:" << obj->GetCorrEt(2012, 14., -1.23, 25.6) << std::endl;
  
  
  TFile *oldfile = new TFile("JanDec13YYV3Trees/testSelectionfsr.v3.dy2mmpowhegpythias6v02bAODSIM.muid2.phtid1.phtcorr96.datapu6.mcpu1.scale0.root");

  //TDirectoryFile* TDFile = (TDirectoryFile*)oldfile->Get("tree");
  //TTree* oldtree = (TTree*)tree->FindObjectAny("pmv");
  
  TTree* oldtree = (TTree*)oldfile->Get("Analysis");
  long nentries = oldtree->GetEntries();

  rochcor* rmcor = new rochcor();
  
  TLorentzVector genmu; //TLorentzVector of the generated muon- : only forMC
  TLorentzVector genmubar; //TLorentzVector of the generated muon+ : only for MC
  TLorentzVector mu; //TLorentzVector of the reconstructed muon-
  TLorentzVector mubar; //TLorentzVector of the reconstructed muon+

  TLorentzVector* mmFV;//FV: Four Vector
  
  //variables to read the trees
  float PhoE, PhoEta, GenPhoE, mmg, mm, gamr9;
  float E_new, mmg_new, mm_new; 
  float mpt[2], meta[2], mphi[2];
  float mpt_new[2], meta_new[2], mphi_new[2];

  int mcha[2], mcha_new[2];
  
  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile("JanDec13YYV3Trees/testSelectionfsr.v3.dy2mmpowhegpythias6v02bAODSIM.muid2.phtid1.phtcorr96.datapu6.mcpu1.scale0.rochcor.root","recreate");
  TTree *newtree = oldtree->CloneTree(0);
  
  
  
  TRandom3* rand = new TRandom3(0);
  float gsmear = 0.03;

  //Old variables used.
  
  ///////////////////////////////////////////////////////////
  //////////////// SMEARING MC /////////////////////////////
  /////////////////////////////////////////////////////////
  oldtree->SetBranchAddress("gamscenergycorr", &PhoE);//Photon corrected energy
  oldtree->SetBranchAddress("gameta", &PhoEta);//Photon reco eta
  oldtree->SetBranchAddress("gametrue", &GenPhoE);//Gen level photon energy
  oldtree->SetBranchAddress("mmgcorr", &mmg);//mu mu gamma corrected invariant mass
  oldtree->SetBranchAddress("mm", &mm);// di muon invariant mass
  oldtree->SetBranchAddress("gamr9", &gamr9);// di muon invariant mass

  //Muon Variables

  oldtree->SetBranchAddress("mpt", &mpt[0]);//muon pt array
  oldtree->SetBranchAddress("mcha", &mcha[0]);//muon charge array
  oldtree->SetBranchAddress("meta", &meta[0]);//muon eta array
  oldtree->SetBranchAddress("mphi", &mphi[0]);//muon phi array
 
  
  //New Variables used
  newtree->SetBranchAddress("gamscenergycorr", &E_new);//Variables modified in the new tree
  newtree->SetBranchAddress("mmgcorr", &mmg_new);
  newtree->SetBranchAddress("mm", &mm_new);
  newtree->SetBranchAddress("mpt", &mpt_new[0]);
  newtree->SetBranchAddress("mcha", &mcha_new[0]);
  newtree->SetBranchAddress("meta", &meta_new[0]);
  newtree->SetBranchAddress("mphi", &mphi_new[0]);

  

  //TH1F* gauss = new TH1F("gauss", "gauss test", 1000, 0, 500);
  
  for (long i = 0; i < nentries; i++) {
    oldtree->GetEntry(i);

    //std::cout << "M1:  " <<  mcha[0] << std::endl;
    //std::cout << "M2:  " <<  mcha[1] << std::endl;
    //std::cout << "M1 PT:  " << mpt[0] << std::endl;
    //std::cout << "M2 PT:  " << mpt[1] << std::endl;

    if(mcha[0] == -1 && mcha[1] == 1){
      mu.SetPxPyPzE( mpt[0]*cos(mphi[0]),				\
		     mpt[0]*sin(mphi[0]),				\
		     mpt[0]*sinh(meta[0]),				\
		     mpt[0]*cosh(meta[0]) );
      
      mubar.SetPxPyPzE(mpt[1]*cos(mphi[1]),				\
		       mpt[1]*sin(mphi[1]),				\
		       mpt[1]*sinh(meta[1]),				\
		       mpt[1]*cosh(meta[1]) );

      rmcor->momcor_mc(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_mc(mubar, 1., 0, 0); // for positive reconstructed muon
      mpt_new[0] = mu.Pt();
      meta_new[0] = mu.Eta();
      mphi_new[0] = mu.Phi();
      mcha_new[0] = mcha[0];
      mcha_new[1] = mcha[1];
      mpt_new[1] = mubar.Pt();
      meta_new[1] = mubar.Eta();
      mphi_new[1] = mubar.Phi();
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else if(mcha[0] == 1 && mcha[1] == -1){
      
      mubar.SetPxPyPzE( mpt[0]*cos(mphi[0]),				\
			mpt[0]*sin(mphi[0]),				\
			mpt[0]*sinh(meta[0]),				\
			mpt[0]*cosh(meta[0]) );
      
      mu.SetPxPyPzE(mpt[1]*cos(mphi[1]),				\
		    mpt[1]*sin(mphi[1]),				\
		    mpt[1]*sinh(meta[1]),				\
		    mpt[1]*cosh(meta[1]) );
      
      rmcor->momcor_mc(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_mc(mubar, 1., 0, 0); // for positive reconstructed muon
      mpt_new[0] = mubar.Pt();
      meta_new[0] = mubar.Eta();
      mphi_new[0] = mubar.Phi();
      mpt_new[1] = mu.Pt();
      meta_new[1] = mu.Eta();
      mphi_new[1] = mu.Phi();
      mcha_new[0] = mcha[0];
      mcha_new[1] = mcha[1];
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else{
      std::cout << "[INFO]--> No mu-mu+ pair was found!!, No correction applied" << std::endl;
      mm_new = mm;//No correction applied
      mpt_new[0] = mpt[0];
      mphi_new[0] = mphi[0];
      meta_new[0] = meta[0];
      mcha_new[0] = mcha[0];
      mcha_new[1] = mcha[1];
      mpt_new[1] = mpt[1];
      mphi_new[1] = mphi[1];
      meta_new[1] = meta[1];
    }
    
    if(GenPhoE > 0 && PhoE/cosh(PhoEta) > 10.0 ){// isFSR 
      
      ////////////////////////////////////////////////////
      ////////////////PHOSPHOR CORRECTION/////////////////
      ///////////////////////////////////////////////////

      //E_new = obj->GetCorrEnergy(2011, PhoE/cosh(PhoEta), PhoEta, GenPhoE);//No photon energy correction when muon correcting
      //mmg_new = sqrt( mm*mm + ( mmg*mmg - mm*mm )*( E_new/PhoE ) );// No mmg correction when muon correcting
      
      
      ///////////////////////////
      //////Muon Correction/////
      /////////////////////////
      E_new = PhoE;//No Correction, just muon correction case
      mmg_new = sqrt( mm_new*mm_new + (mmg*mmg - mm*mm) );//mm_new DI-Muon sytem InvMass after Muon correction(implicitly applying muon correction)
      //std::cout << "mmg: " << mmg << " mmg new: " << mmg_new << std::endl;

      /////////////////////////////////////
      /////////Gaussian Smearing///////////
      /////////////////////////////////////
      
      //E_new = ( 1 + rand->Gaus(0, gsmear ) )*PhoE;
      //mmg_new = sqrt( mm*mm + ( mmg_new*mmg_new - mm*mm )*( E_new/PhoE ) );

      ////////////////////////////////////////////
      //////////////Fabrice Smearing//////////////
      ////////////////////////////////////////////
      
      //E_new = obj->FabSmear(PhoE, PhoEta, gamr9);//Fabrice Smearing for photons
      //mmg_new = sqrt( mm*mm + ( mmg_new*mmg_new - mm*mm )*( E_new/PhoE ) );//mmg mass correction due to photon energy correction after Muon Correction!!
      
    }else{

      
      ////////////////////////////////////////////////////
      ////////////////PHOSPHOR CORRECTION/////////////////
      ///////////////////////////////////////////////////
      
      //E_new = obj->GetCorrEnergy(2011, PhoE/cosh(PhoEta), PhoEta, GenPhoE);//No photon energy correction when muon correcting
      //mmg_new = sqrt( mm*mm + ( mmg*mmg - mm*mm )*( E_new/PhoE ) );// No mmg correction when muon correcting
      
      
      ///////////////////////////
      //////Muon Correction/////
      /////////////////////////
      E_new = PhoE;//No Correction, just muon correction case
      mmg_new = sqrt( mm_new*mm_new + (mmg*mmg - mm*mm) );//mm_new DI-Muon sytem InvMass after Muon correction(implicitly applying muon correction)
      
      /////////////////////////////////////
      /////////Gaussian Smearing///////////
      /////////////////////////////////////
      
      //E_new = ( 1 + rand->Gaus(0, gsmear ) )*PhoE;
      //mmg_new = sqrt( mm*mm + ( mmg_new*mmg_new - mm*mm )*( E_new/PhoE ) );
      
      ////////////////////////////////////////////
      //////////////Fabrice Smearing//////////////
      ////////////////////////////////////////////
      
      //E_new = obj->FabSmear(PhoE, PhoEta, gamr9);//Fabrice Smearing for photons
      //mmg_new = sqrt( mm*mm + ( mmg_new*mmg_new - mm*mm )*( E_new/PhoE ) );//mmg mass correction due to photon energy correction after Muon Correction!!

    }
    
    newtree->Fill();
    
  }
  newtree->Print();
  newtree->AutoSave();
  //gauss->Write();
  delete oldfile;
  delete newfile;
  
  delete rand;
  
  ///////////////////////////////////////////////////////////
  ////////////////SMEARING DATA/////////////////////////////
  /////////////////////////////////////////////////////////
  
  rand = new TRandom3(0);
  
  
  oldfile = new TFile("JanDec13YYV3Trees/testSelectionfsr.v3.Data2011.Jul2012ReReco.muid2.phtid1.phtcorr96.datapu0.mcpu0.scale0.root");
  //TDFile = (TDirectoryFile*)oldfile->Get("tree");//only for v16 files
  //oldtree = (TTree*)tree->FindObjectAny("pmv");//only for v16 files
  
  oldtree = (TTree*)oldfile->Get("Analysis");//For all other files
  nentries = oldtree->GetEntries();
  
  
  //Create a new file + a clone of old tree in new file
  newfile = new TFile("JanDec13YYV3Trees/testSelectionfsr.v3.Data2011.Jul2012ReReco.muid2.phtid1.phtcorr96.datapu0.mcpu0.scale0.rochcor.root","recreate");
  newtree = oldtree->CloneTree(0);
  

  oldtree->SetBranchAddress("gamscenergycorr", &PhoE);
  oldtree->SetBranchAddress("gameta", &PhoEta);
  oldtree->SetBranchAddress("gametrue", &GenPhoE);
  oldtree->SetBranchAddress("mmgcorr", &mmg);
  oldtree->SetBranchAddress("mm", &mm);

  //Muon Variables
  
  oldtree->SetBranchAddress("mpt", &mpt[0]);
  oldtree->SetBranchAddress("mcha", &mcha[0]);
  oldtree->SetBranchAddress("meta", &meta[0]);
  oldtree->SetBranchAddress("mphi", &mphi[0]);
  
  
  //New Variables used
  newtree->SetBranchAddress("gamscenergycorr", &E_new);
  newtree->SetBranchAddress("mmgcorr", &mmg_new);
  newtree->SetBranchAddress("mm", &mm_new);
  newtree->SetBranchAddress("mpt", &mpt_new[0]);
  newtree->SetBranchAddress("mcha", &mcha_new[0]);
  newtree->SetBranchAddress("meta", &meta_new[0]);
  newtree->SetBranchAddress("mphi", &mphi_new[0]);
  
 

  for (long i = 0; i < nentries; i++) {
    oldtree->GetEntry(i);
    
    
    if(mcha[0] == -1 && mcha[1] == 1){
      mu.SetPxPyPzE( mpt[0]*cos(mphi[0]),				\
		     mpt[0]*sin(mphi[0]),				\
		     mpt[0]*sinh(meta[0]),			\
		     mpt[0]*cosh(meta[0]) );
      
      mubar.SetPxPyPzE(mpt[1]*cos(mphi[1]),				\
		       mpt[1]*sin(mphi[1]),				\
		       mpt[1]*sinh(meta[1]),				\
		       mpt[1]*cosh(meta[1]) );
      
      rmcor->momcor_mc(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_mc(mubar, 1., 0, 0); // for positive reconstructed muon
      mpt_new[0] = mu.Pt();
      meta_new[0] = mu.Eta();
      mphi_new[0] = mu.Phi();
      mpt_new[1] = mubar.Pt();
      meta_new[1] = mubar.Eta();
      mphi_new[1] = mubar.Phi();
      mcha_new[0] = mcha[0];
      mcha_new[1] = mcha[1];
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else if(mcha[0] == 1 && mcha[1] == -1){
      
      mubar.SetPxPyPzE( mpt[0]*cos(mphi[0]),				\
			mpt[0]*sin(mphi[0]),				\
			mpt[0]*sinh(meta[0]),				\
			mpt[0]*cosh(meta[0]) );
      
      mu.SetPxPyPzE(mpt[1]*cos(mphi[1]),				\
		    mpt[1]*sin(mphi[1]),				\
		    mpt[1]*sinh(meta[1]),				\
		    mpt[1]*cosh(meta[1]) );
      
      rmcor->momcor_mc(mu, -1., 0, 0);// for negative reconstructed muon
      rmcor->momcor_mc(mubar, 1., 0, 0); // for positive reconstructed muon
      mpt_new[0] = mubar.Pt();
      meta_new[0] = mubar.Eta();
      mphi_new[0] = mubar.Phi();
      mpt_new[1] = mu.Pt();
      meta_new[1] = mu.Eta();
      mphi_new[1] = mu.Phi();
      mcha_new[0] = mcha[0];
      mcha_new[1] = mcha[1];
      mmFV = new TLorentzVector(mu+mubar);
      mm_new =  mmFV->M();
      delete mmFV;
    }else{
      std::cout << "[INFO]--> No mu-mu+ pair was found!!, No correction applied" << std::endl;
      mm_new = mm;//No correction applied
      mpt_new[0] = mpt[0];
      mphi_new[0] = mphi[0];
      meta_new[0] = meta[0];
      mcha_new[0] = mcha[0];
      mcha_new[1] = mcha[1];
      mpt_new[1] = mpt[1];
      mphi_new[1] = mphi[1];
      meta_new[1] = meta[1];
    }
    
    
    ////////////////////////////////////////////////////
    ////////////////PHOSPHOR CORRECTION/////////////////
    ///////////////////////////////////////////////////
    
    //E_new = obj->GetCorrEnergy(2011, PhoE/cosh(PhoEta), PhoEta, GenPhoE);//No photon energy correction when muon correcting
    //mmg_new = sqrt( mm*mm + ( mmg*mmg - mm*mm )*( E_new/PhoE ) );// No mmg correction when muon correcting
    
    
    ///////////////////////////
    //////Muon Correction/////
    /////////////////////////
    E_new = PhoE;//No Correction, just muon correction case
    mmg_new = sqrt( mm_new*mm_new + (mmg*mmg - mm*mm) );//mm_new DI-Muon sytem InvMass after Muon correction(implicitly applying muon correction)
    
    /////////////////////////////////////
    /////////Gaussian Smearing///////////
    /////////////////////////////////////
    
    //E_new = ( 1 + rand->Gaus(0, gsmear ) )*PhoE;
    //mmg_new = sqrt( mm*mm + ( mmg_new*mmg_new - mm*mm )*( E_new/PhoE ) );
    
    ////////////////////////////////////////////
    //////////////Fabrice Smearing//////////////
    ////////////////////////////////////////////
    
    //E_new = obj->FabSmear(PhoE, PhoEta, gamr9);//Fabrice Smearing for photons
    //mmg_new = sqrt( mm*mm + ( mmg_new*mmg_new - mm*mm )*( E_new/PhoE ) );//mmg mass correction due to photon energy correction after Muon Correction!!
    
    
    newtree->Fill();
    
  }
  
  newtree->Print();
  newtree->AutoSave();
  delete oldfile;
  delete newfile;
  
}
