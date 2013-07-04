#include <iostream>
#include <sstream>
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "DM_WJets.hh"
#include "DM_ZJetsNuNu.hh"
#include "DM_DYJetsLL.hh"
#include "DM_TTJets.hh"
#include "DM_Data.hh"
#include "THStack.h"
#include "TString.h"

using namespace std;


//const float WJets::RSQ_BinArr[] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, 0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
//const float WJets::MR_BinArr[] = {150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 1100., 1500.};
const float WJets::RSQ_BinArr[] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, \
				   0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
const float WJets::MR_BinArr[] = {200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 800., 1100., 1500.};

//const float TTJets::RSQ_BinArr[] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, 0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
//const float TTJets::MR_BinArr[] = {150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 1100., 1500.};
const float TTJets::RSQ_BinArr[] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, \
				    0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
const float TTJets::MR_BinArr[] = {200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 800., 1100., 1500.};

//const float ZJetsNuNu::RSQ_BinArr[] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, 0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
//const float ZJetsNuNu::MR_BinArr[] = {150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 1100., 1500.};
const float ZJetsNuNu::RSQ_BinArr[] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, \
				       0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
const float ZJetsNuNu::MR_BinArr[] = {200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 800., 1100., 1500.};

//const float DYJets::RSQ_BinArr[] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, 0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
//const float DYJets::MR_BinArr[] = {150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 1100., 1500.};
const float DYJets::RSQ_BinArr[] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, \
				    0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
const float DYJets::MR_BinArr[] = {200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 800., 1100., 1500.};

//const float Data::RSQ_BinArr[] = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, 0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
//const float Data::MR_BinArr[] = {150., 200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 1100., 1500.};
const float Data::RSQ_BinArr[] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.80, \
				  0.85, 0.90, 0.95, 1.0, 1.05, 1.2, 1.5};
const float Data::MR_BinArr[] = {200., 250., 300., 350., 400., 450., 500., 550., 600., 700., 800., 1100., 1500.};

int main(){
  
  //const char* wjets_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/out/WJETS_DM.root";
  const char* wjets_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/out/WJETS_HT_MET_Total_afterBug.root";
  
  
  WJets* W = new WJets(wjets_file);
  
  
  //TH1F h = TH1F();
  //h = W->PlotRSQ_1Box();
  
  ///////////////////////////////////////////
  ///////////////WJETS 1D HISTOS/////////////
  ///////////////////////////////////////////

  
  W->PrintEvents();
  
  TH1F* RSQ_0 = new TH1F( W->PlotRSQ_1Box() );
  //RSQ_0->Sumw2();
  //std::cout << "passssssss0" << std::endl;
  //RSQ_0->Scale(1./RSQ_0->Integral());
  
  TH1F* RSQ_1 = new TH1F( W->PlotRSQ_0Box() );
  //RSQ_1->Sumw2();
  //RSQ_1->Scale(1./RSQ_1->Integral());
  
  TH1F* MR_0 = new TH1F( W->PlotMR_0Box() );
  //MR_0->Sumw2();
  //MR_0->Scale(1./MR_0->Integral());
  
  TH1F* MR_1 = new TH1F( W->PlotMR_1Box() );
  //MR_1->Sumw2();
  //MR_1->Scale(1./MR_1->Integral());
  
  std::cout << "passssssss" << std::endl;

  //RATIO PLOTS
  TH1F*  RSQ_RATIO = new TH1F("RSQ_RATIO", "RSQ RATIO", WJets::RSQ_Bins, WJets::RSQ_BinArr);
  TH1F*  MR_RATIO = new TH1F("MR_RATIO", "MR RATIO", WJets::MR_Bins, WJets::MR_BinArr);
  
  RSQ_RATIO->Divide(RSQ_0, RSQ_1, 1, 1, "");
  MR_RATIO->Divide(MR_0, MR_1, 1, 1, "");
  
  ///////////////////////////////////////////////////////
  /////////////////WJETS 2D HISTOS///////////////////////
  ///////////////////////////////////////////////////////
  TH2F* MR_RSQ_0BOX = new TH2F( W->PlotRSQ_vs_MR_0Box() );
  MR_RSQ_0BOX->Sumw2();
  MR_RSQ_0BOX->Scale(1./MR_RSQ_0BOX->Integral());
  
  TH2F* MR_RSQ_1BOX = new TH2F( W->PlotRSQ_vs_MR_1Box() );
  MR_RSQ_1BOX->Sumw2();
  MR_RSQ_1BOX->Scale(1./MR_RSQ_1BOX->Integral());
  
  //RATIO PLOTS
  
  TH2F* RATIO_WJETS_2D = new TH2F("RATIO_WJETS_2D", "RATIO_WJETS_2D", WJets::MR_Bins, WJets::MR_BinArr, WJets::RSQ_Bins, WJets::RSQ_BinArr);
  RATIO_WJETS_2D->Divide(MR_RSQ_0BOX, MR_RSQ_1BOX, 1, 1, "");



  

  //cout << h.GetBinContent(2) << std::endl;
  TFile* f = new TFile("wjets_test1.root","RECREATE");
  
  RSQ_0->Write();
  RSQ_1->Write();
  MR_0->Write();
  MR_1->Write();
  RSQ_RATIO->Write("RSQ_RATIO");
  MR_RATIO->Write("MR_RATIO");
  
  //2D PLOTS
  MR_RSQ_0BOX->Write("MR_RQS_2D_0BOX");
  MR_RSQ_1BOX->Write("MR_RQS_2D_1BOX");
  RATIO_WJETS_2D->Write("WJETS_RATIO_2D");
  
  TCanvas* C0 = new TCanvas("C0", "C0", 1024, 1024);
  
  C0->cd();

  MR_0->SetLineColor(2);
  MR_0->SetMarkerSize(1.5);
  MR_0->SetMarkerColor(2);
  MR_0->SetMarkerStyle(22);
  
  
  MR_1->SetLineColor(4);
  MR_1->SetMarkerSize(1.5);
  MR_1->SetMarkerColor(4);
  MR_1->SetMarkerStyle(22);
  MR_1->SetFillColor(4);
  
  //MR_0->SetStats(0);
  MR_0->SetTitle("M_{R} Dist. WJets->#mu#nu Bkg.");
  //MR_1->SetStats(0);
  MR_1->SetTitle("M_{R} Dist. WJets->#mu#nu Bkg.");
  MR_0->Draw();
  MR_1->Draw("same");
  MR_1->SetXTitle("M_{R}");
  // MR_0->Draw("same");
  
  TLegend* leg = new TLegend(0.4,0.6,0.69,0.89);
  leg->AddEntry(MR_0,"M_{R} WJets->#mu#nu 0#mu BOX","f");
  leg->AddEntry(MR_1,"M_{R} WJets->#mu#nu 1#mu BOX","f");
  leg->SetHeader("M_{R} Dist. WJets->#mu#nu Bkg.");
  leg->Draw();
  C0->SaveAs("RatioPlots/MR_WJETS_Norm.pdf");
  
  delete leg;
  
  RSQ_0->SetLineColor(2);
  RSQ_1->SetFillColor(4);
  
  //RSQ_0->SetStats(0);
  RSQ_0->SetTitle("R^{2} Dist. WJets->#mu#nu Bkg.");
  //RSQ_1->SetStats(0);
  RSQ_1->SetTitle("R^{2} Dist. WJets->#mu#nu Bkg.");
  RSQ_1->Draw();
  RSQ_1->SetXTitle("R^{2}");
  RSQ_0->Draw("same");
  
  leg = new TLegend(0.4,0.6,0.69,0.89);
  leg->AddEntry(MR_0,"R^{2} WJets->#mu#nu 0#mu BOX","f");
  leg->AddEntry(MR_1,"R^{2} WJets->#mu#nu 1#mu BOX","f");
  leg->SetHeader("R^{2} Dist. WJets->#mu#nu Bkg.");
  leg->Draw();
  C0->SaveAs("RatioPlots/RSQ_WJETS_Norm.pdf");
  delete leg;
  

  RSQ_RATIO->SetLineColor(2);
  RSQ_RATIO->SetStats(0);
  RSQ_RATIO->SetTitle("R^{2} Ratio WJets->#mu#nu Bkg.");
  RSQ_RATIO->Draw();
  
  leg = new TLegend(0.6,0.7,0.89,0.89);
  leg->AddEntry(RSQ_RATIO,"R^{2} (WJets->#mu#nu 0#mu)/(WJets->#mu#nu  1BOX)","f");
  leg->SetHeader("R^{2} Ratio Dist. WJets->#mu#nu Bkg.");
  leg->Draw();
  
  C0->SaveAs("RatioPlots/RSQ_WJETS_RATIO.pdf");


  delete leg;
  

  MR_RATIO->SetLineColor(2);
  MR_RATIO->SetStats(0);
  MR_RATIO->SetTitle("M_{R} Ratio WJets->#mu#nu Bkg.");
  MR_RATIO->Draw();
  
  leg = new TLegend(0.6,0.7,0.89,0.89);
  leg->AddEntry(RSQ_RATIO,"M_{R} (WJets->#mu#nu 0#mu)/(WJets->#mu#nu  1BOX)","f");
  leg->SetHeader("M_{R} Ratio Dist. WJets->#mu#nu Bkg.");
  leg->Draw();
  
  C0->SaveAs("RatioPlots/MR_WJETS_RATIO.pdf");
  delete leg;

  RATIO_WJETS_2D->GetXaxis()->SetRangeUser(0, 600.);
  RATIO_WJETS_2D->SetXTitle("M_{R}");
  RATIO_WJETS_2D->SetYTitle("R^{2}");
  RATIO_WJETS_2D->Draw("colz");
    
  float binV, binErr, Xpos, Ypos;
  TLatex* Lval;
  //TLatex* Lerr;
  char val[50];
  char err[50];
  binV = 666.;
  /////////////////////////////////////////////////////
  ////////////////////2D PLOTS with numbers///////////
  ////////////////////////////////////////////////////
  for(int i = 1; i <= RATIO_WJETS_2D->GetNbinsX(); i++){
    for(int j = 1; j <= RATIO_WJETS_2D->GetNbinsY(); j++){
      binV =  RATIO_WJETS_2D->GetBinContent(i,j);
      binErr = RATIO_WJETS_2D->GetBinError(i,j);
      
      Xpos =  RATIO_WJETS_2D->GetXaxis()->GetBinCenter(i);
      Ypos =  RATIO_WJETS_2D->GetYaxis()->GetBinCenter(j);
      
      sprintf(val,"%.3f", binV);
      sprintf(err," \\pm %.3f", binErr);
      //std::cout << "val: " << val << err << "Ypos: " << Ypos << std::endl;
      if( (binV != 0) || ( binErr != 0) ){
	Lval = new TLatex(Xpos-70,Ypos+0.01, "HELLO!!!" );
	//Lerr = new TLatex(Xpos-70,Ypos-0.03, err );
	Lval->SetTextSize(.025);
	//Lval->Draw("same");
	//Lval->AppendPad();
	Lval->DrawLatex(Xpos -12. ,Ypos+0.01, val );
	Lval->DrawLatex(Xpos -12. ,Ypos-0.013, err );
	//Lerr->Draw("same");
	
	delete Lval;
	//delete Lerr;
	//std::cout << printf( "%.4f", binV ) << std::endl;
      }
     
    }
    
  }

  C0->SaveAs("RatioPlots/Ratio_2D_WJETS.pdf");

  f->Close();

  /////////////////////////////////////////////
  //////////////// MET HT W plots/////////////
  ///////////////////////////////////////////
  
  std::vector<TH1F*> WmetXVec = W->PlotMETx();
  std::vector<TH1F*> WmetYVec = W->PlotMETy();
  std::vector<TH1F*> WmetMagVec =  W->PlotMETmag();
  std::vector<TH1F*> WhtVec = W->PlotHT();
  std::cout << "debug: " << std::endl;
  int ctr = 0;
  TString metpicname;
  
  for( std::vector<TH1F*>::iterator itTT = WmetXVec.begin();	\
       itTT != WmetXVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/W_metXbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/W_metXbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = WmetYVec.begin();	\
       itTT != WmetYVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/W_metYbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/W_metYbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = WmetMagVec.begin();	\
       itTT != WmetMagVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/W_metMAGbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/W_metMAGbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }

  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = WhtVec.begin();	\
       itTT != WhtVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("HTplots/W_htBox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("HTplots/W_htBox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  
  /////////////////////////////////////////////
  ///////////////ZJetsNuNu ANA/////////////////
  /////////////////////////////////////////////
  
 
  
  //DYJets* DY = new DYJets("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/out/DYJETS_DM.root");
  DYJets* DY = new DYJets("/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/out/DYJETS_DM_MET_HT_Total_afterBug.root");
  
  //std::cout << "weight0: " << Z->weight0 << std::endl;
  //std::cout << "weight1: " << Z->weight1 << std::endl;
  //std::cout << "weight2: " << Z->weight2 << std::endl;
  //std::cout << "weight3: " << Z->weight3 << std::endl;
  
  DY->PrintEvents();

  
  ZJetsNuNu* Z = new ZJetsNuNu();
  Z->PrintEvents();
  
  TH1F* MR_11 = new TH1F( Z->PlotMR_1Box() );
  //MR_11->Sumw2();
  //MR_11->Scale( 1./MR_11->Integral() );
  
  TH1F* MR_00 = new TH1F( Z->PlotMR_0Box() );
  //MR_00->Sumw2();
  //MR_00->Scale( 1./MR_00->Integral() );
  
  TH1F* RSQ_11 = new TH1F( Z->PlotRSQ_1Box() );
  //RSQ_11->Sumw2();
  //RSQ_11->Scale( 1./RSQ_11->Integral() );
  
  TH1F* RSQ_00 = new TH1F( Z->PlotRSQ_0Box() );
  //RSQ_00->Sumw2();
  //RSQ_00->Scale( 1./RSQ_00->Integral() );
  
  TH2F*  MR_RSQ_0BOX_Z = new TH2F( Z->PlotRSQ_vs_MR_0Box() );
  MR_RSQ_0BOX_Z->Sumw2();
  MR_RSQ_0BOX_Z->Scale( 1./MR_RSQ_0BOX_Z->Integral() );
  TH2F*  MR_RSQ_1BOX_Z = new TH2F( Z->PlotRSQ_vs_MR_1Box() );
  MR_RSQ_1BOX_Z->Sumw2();
  MR_RSQ_1BOX_Z->Scale( 1./MR_RSQ_1BOX_Z->Integral() );
  
  
  //////////////////////////////////////////////////////
  ///////////////// Drell-Yan///////////////////////////
  /////////////////////////////////////////////////////

  TH1F* MR_22_DY = new TH1F( DY->PlotMR_2Box() );
  //MR_22_DY->Sumw2();
  //MR_22_DY->Scale( 1./MR_22_DY->Integral() );
  
  TH1F* MR_11_DY = new TH1F( DY->PlotMR_1Box() );
  //MR_11_DY->Sumw2();
  //MR_11_DY->Scale( 1./MR_11_DY->Integral() );
  
  TH1F* MR_00_DY = new TH1F( DY->PlotMR_0Box() );
  //MR_00_DY->Sumw2();
  //MR_00_DY->Scale( 1./MR_00_DY->Integral() );
  
  TH1F* RSQ_22_DY = new TH1F( DY->PlotRSQ_2Box() );
  //RSQ_22_DY->Sumw2();
  //RSQ_22_DY->Scale( 1./RSQ_22_DY->Integral() );
  
  TH1F* RSQ_11_DY = new TH1F( DY->PlotRSQ_1Box() );
  //RSQ_11_DY->Sumw2();
  //RSQ_11_DY->Scale( 1./RSQ_11_DY->Integral() );
  
  TH1F* RSQ_00_DY = new TH1F( DY->PlotRSQ_0Box() );
  //RSQ_00_DY->Sumw2();
  //RSQ_00_DY->Scale( 1./RSQ_00_DY->Integral() );
  
  TH2F*  MR_RSQ_0BOX_DY = new TH2F( DY->PlotRSQ_vs_MR_0Box() );
  MR_RSQ_0BOX_DY->Sumw2();
  MR_RSQ_0BOX_DY->Scale( 1./MR_RSQ_0BOX_DY->Integral() );
  TH2F*  MR_RSQ_1BOX_DY = new TH2F( DY->PlotRSQ_vs_MR_1Box() );
  MR_RSQ_1BOX_DY->Sumw2();
  MR_RSQ_1BOX_DY->Scale( 1./MR_RSQ_1BOX_DY->Integral() );
  TH2F*  MR_RSQ_2BOX_DY = new TH2F( DY->PlotRSQ_vs_MR_2Box() );
  MR_RSQ_2BOX_DY->Sumw2();
  MR_RSQ_2BOX_DY->Scale( 1./MR_RSQ_2BOX_DY->Integral() );
  

  //RATIO PLOTS
  TH1F*  ZJ_RSQ_RATIO = new TH1F("ZJ_RSQ_RATIO", "ZJ_RSQ RATIO", ZJetsNuNu::RSQ_Bins, ZJetsNuNu::RSQ_BinArr);
  ZJ_RSQ_RATIO->Divide(RSQ_00, RSQ_22_DY, 1, 1, "");
  TH1F*  ZJ_MR_RATIO = new TH1F("ZJ_MR_RATIO", "ZJ_MR_RATIO", ZJetsNuNu::MR_Bins, ZJetsNuNu::MR_BinArr);
  ZJ_MR_RATIO->Divide(MR_00, MR_22_DY, 1, 1, "");

  //2D Ratios
  
  TH2F* RATIO_ZJETS_2D = new TH2F("ZJ_RATIO_ZJETS_2D", "ZJ_RATIO_ZJETS_2D", ZJetsNuNu::MR_Bins, ZJetsNuNu::MR_BinArr, ZJetsNuNu::RSQ_Bins, ZJetsNuNu::RSQ_BinArr);
  RATIO_ZJETS_2D->Divide(MR_RSQ_0BOX_Z, MR_RSQ_2BOX_DY, 1, 1, "");

  
  TFile* f1 = new TFile("ZJetsNuNu_test.root","RECREATE");

  MR_11->Write();
  MR_00->Write();
  RSQ_11->Write();
  RSQ_00->Write();
  
  MR_RSQ_0BOX_Z->Write();
  MR_RSQ_1BOX_Z->Write();

  MR_22_DY->Write();
  MR_11_DY->Write();
  MR_00_DY->Write();

  RSQ_22_DY->Write();
  RSQ_11_DY->Write();
  RSQ_00_DY->Write();
  
  MR_RSQ_0BOX_DY->Write();
  MR_RSQ_1BOX_DY->Write();
  MR_RSQ_2BOX_DY->Write();

  //delete C;

  //TCanvas* C = new TCanvas("C", "C", 1024, 1024);
  
  //C->cd();
  MR_00->SetLineColor(2);
  MR_22_DY->SetFillColor(4);
    
  MR_00->SetStats(0);
  MR_00->SetTitle("M_{R} Dist. Z->#nu#nu Bkg.");
  MR_22_DY->SetStats(0);
  MR_22_DY->SetTitle("M_{R} Dist. Z->#nu#nu Bkg.");
  MR_22_DY->Draw();
  MR_22_DY->SetXTitle("M_{R}");
  MR_00->Draw("same");
  
  leg = new TLegend(0.6,0.7,0.89,0.89);
  leg->AddEntry(MR_00,"MR ZJets->#nu#nu 0#mu BOX","f");
  leg->AddEntry(MR_22_DY,"MR DYJets->LL 2#mu BOX","f");
  leg->SetHeader("M_{R} Dist. Z->#nu#nu Bkg.");
  leg->Draw();
  C0->SaveAs("RatioPlots/MR_ZJETS_Norm.pdf");

  delete leg;
  
  RSQ_00->SetLineColor(2);
  RSQ_22_DY->SetFillColor(4);
    
  RSQ_00->SetStats(0);
  RSQ_00->SetTitle("R^{2} Dist. Z->#nu#nu Bkg.");
  RSQ_22_DY->SetStats(0);
  RSQ_22_DY->SetTitle("R^{2} Dist. Z->#nu#nu Bkg.");
  RSQ_22_DY->Draw();
  RSQ_22_DY->SetXTitle("R^{2}");
  RSQ_00->Draw("same");

  leg = new TLegend(0.6,0.7,0.89,0.89);
  leg->AddEntry(RSQ_00,"R^{2} ZJets->#nu#nu 0#mu BOX","f");
  leg->AddEntry(RSQ_22_DY,"R^{2} DYJets->LL 2#mu BOX","f");
  leg->SetHeader("R^{2} Dist. Z->#nu#nu Bkg.");
  leg->Draw();
  
  C0->SaveAs("RatioPlots/RSQ_ZJETS_Norm.pdf");
  delete leg;

  ZJ_RSQ_RATIO->SetLineColor(2);
  ZJ_RSQ_RATIO->SetStats(0);
  ZJ_RSQ_RATIO->SetTitle("R^{2} Ratio ZJets->#nu#nu Bkg.");
  ZJ_RSQ_RATIO->Draw();
  
  leg = new TLegend(0.6,0.7,0.89,0.89);
  leg->AddEntry(ZJ_RSQ_RATIO,"R^{2} (ZJets->#nu#nu 0#mu)/(DYJets->LL  2BOX)","f");
  leg->SetHeader("R^{2} Ratio Dist. Z->#nu#nu Bkg.");
  leg->Draw();

  C0->SaveAs("RatioPlots/RSQ_ZJETS_RATIO.pdf");

  delete leg;
  
  ZJ_MR_RATIO->SetLineColor(2);
  ZJ_MR_RATIO->SetStats(0);
  ZJ_MR_RATIO->SetTitle("M_{R} Ratio ZJets->#nu#nu Bkg.");
  ZJ_MR_RATIO->Draw();
  
  leg = new TLegend(0.6,0.7,0.89,0.89);
  leg->AddEntry(ZJ_MR_RATIO,"M_{R} (ZJets->#nu#nu 0#mu)/(DYJets->LL  2BOX)","f");
  leg->SetHeader("M_{R} Ratio Dist. Z->#nu#nu Bkg.");
  leg->Draw();
  
  C0->SaveAs("RatioPlots/MR_ZJETS_RATIO.pdf");

  
  RATIO_ZJETS_2D->GetXaxis()->SetRangeUser(0, 700.);
  RATIO_ZJETS_2D->SetXTitle("M_{R}");
  RATIO_ZJETS_2D->SetYTitle("R^{2}");
  RATIO_ZJETS_2D->Draw("colz");
    
  //float binV, binErr, Xpos, Ypos;
  //TLatex* Lval;
  //TLatex* Lerr;
  //char val[50];
  //char err[50];
  binV = 666.;
  //std::cout << printf( "%.4f", binV ) << std::endl;
  
  for(int i = 1; i <= RATIO_ZJETS_2D->GetNbinsX(); i++){
    for(int j = 1; j <= RATIO_ZJETS_2D->GetNbinsY(); j++){
      binV =  RATIO_ZJETS_2D->GetBinContent(i,j);
      binErr = RATIO_ZJETS_2D->GetBinError(i,j);
      
      Xpos =  RATIO_ZJETS_2D->GetXaxis()->GetBinCenter(i);
      Ypos =  RATIO_ZJETS_2D->GetYaxis()->GetBinCenter(j);
      
      sprintf(val,"%.3f", binV);
      sprintf(err," \\pm %.3f", binErr);
      //std::cout << "val: " << val << err << "Ypos: " << Ypos << std::endl;
      if( (binV != 0) || ( binErr != 0) ){
	Lval = new TLatex(Xpos-70,Ypos+0.01, "HELLO!!!" );
	//Lerr = new TLatex(Xpos-70,Ypos-0.03, err );
	if( i == 1 || i == 2 ){
	  Lval->SetTextSize(.020);
	}else{
	  Lval->SetTextSize(.030);
	}
	
	//Lval->Draw("same");
	//Lval->AppendPad();
	Lval->DrawLatex(Xpos - 12. ,Ypos+0.01, val );
	Lval->DrawLatex(Xpos -12. ,Ypos-0.018, err );
	//Lerr->Draw("same");
	
	delete Lval;
	//delete Lerr;
	//std::cout << printf( "%.4f", binV ) << std::endl;
      }
     
    }
    
  }

  C0->SaveAs("RatioPlots/Ratio_2D_ZJETS.pdf");
  
  f1->Close();

  /////////////////////////////////////////////
  //////////////// MET HT DY plots/////////////
  ///////////////////////////////////////////
  
  std::vector<TH1F*> DYmetXVec = DY->PlotMETx();
  std::vector<TH1F*> DYmetYVec = DY->PlotMETy();
  std::vector<TH1F*> DYhtVec = DY->PlotHT();
 
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = DYmetXVec.begin();	\
       itTT != DYmetXVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/DY_metXbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/DY_metXbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = DYmetYVec.begin();	\
       itTT != DYmetYVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/DY_metYbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/DY_metYbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = DYhtVec.begin();	\
       itTT != DYhtVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("HTplots/DY_htBox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("HTplots/DY_htBox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }

  //////////////////////////////////////////////////
  /////////////////////////////////////////////////
  /////////////////TTbar + Jets////////////////////
  ////////////////////////////////////////////////
  ///////////////////////////////////////////////

  //const char* ttjets_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/out/TTJETS_DM.root";
  const char* ttjets_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/MC/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/out/TTJETS_DM_MET_HT_afterBug.root";
  
  TTJets* TT = new TTJets(ttjets_file);
  TT->PrintEvents();

  
  TH1F* MR_22_TT = new TH1F( TT->PlotMR_2Box() );
  //MR_22_TT->Sumw2();
  //MR_22_TT->Scale( 1./MR_22_TT->Integral() );
  
  TH1F* MR_11_TT = new TH1F( TT->PlotMR_1Box() );
  //MR_11_TT->Sumw2();
  //MR_11_TT->Scale( 1./MR_11_TT->Integral() );
  
  TH1F* MR_00_TT = new TH1F( TT->PlotMR_0Box() );
  //MR_00_TT->Sumw2();
  //MR_00_TT->Scale( 1./MR_00_TT->Integral() );
  
  TH1F* RSQ_22_TT = new TH1F( TT->PlotRSQ_2Box() );
  //RSQ_22_TT->Sumw2();
  //RSQ_22_TT->Scale( 1./RSQ_22_TT->Integral() );
  
  TH1F* RSQ_11_TT = new TH1F( TT->PlotRSQ_1Box() );
  //RSQ_11_TT->Sumw2();
  //RSQ_11_TT->Scale( 1./RSQ_11_TT->Integral() );
  
  TH1F* RSQ_00_TT = new TH1F( TT->PlotRSQ_0Box() );
  //RSQ_00_TT->Sumw2();
  //RSQ_00_TT->Scale( 1./RSQ_00_TT->Integral() );
  

  std::vector<TH1F*> metXVec = TT->PlotMETx();
  std::vector<TH1F*> metYVec = TT->PlotMETy();
  std::vector<TH1F*> htVec = TT->PlotHT();

  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = metXVec.begin();	\
       itTT != metXVec.end(); ++itTT ){
    //std::cout << "TT pics" << std::endl;
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/TT_metXbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/TT_metXbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = metYVec.begin();	\
       itTT != metYVec.end(); ++itTT ){
    //std::cout << "TT pics" << std::endl;
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/TT_metYbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/TT_metYbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = htVec.begin();	\
       itTT != htVec.end(); ++itTT ){
    //std::cout << "TT pics" << std::endl;
    (*itTT)->Draw();
    //std::cout << "Nentries: " << (*itTT)->Integral() << std::endl;
    metpicname = TString(Form("HTplots/TT_htBox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("HTplots/TT_htBox%d.pbg",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  //Cmet->SaveAs("met_test1.pdf");
  

  ////////////////////////////////////////////////////////////////
  //////////////////// DATA//////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  
  //const char* data_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/Data/CombinedFile/DataDMSelection_TOTAL.root";
  //const char* data_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/Data/SingleMu-Run2012AB/out/SINGLE_MU_MET_Total.root";
  const char* data_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/Data/HTMHT_DATA_Run2012AB_Test/out/DataABTot_afterBug.root";
   
  Data* data = new Data(data_file);
  data->PrintEvents();

  TH1F* MR_22_data = new TH1F( data->PlotMR_2Box() );
  MR_22_data->Sumw2();
  //MR_22_data->Scale( 1./MR_22_data->Integral() );
  
  TH1F* MR_11_data = new TH1F( data->PlotMR_1Box() );
  MR_11_data->Sumw2();
  //MR_11_data->Scale( 1./MR_11_data->Integral() );
  
  TH1F* MR_00_data = new TH1F( data->PlotMR_0Box() );
  MR_00_data->Sumw2();
  //MR_00_data->Scale( 1./MR_00_data->Integral() );
  
  TH1F* RSQ_22_data = new TH1F( data->PlotRSQ_2Box() );
  RSQ_22_data->Sumw2();
  //RSQ_22_data->Scale( 1./RSQ_22_data->Integral() );
  
  TH1F* RSQ_11_data = new TH1F( data->PlotRSQ_1Box() );
  RSQ_11_data->Sumw2();
  //RSQ_11_data->Scale( 1./RSQ_11_data->Integral() );
  
  TH1F* RSQ_00_data = new TH1F( data->PlotRSQ_0Box() );
  RSQ_00_data->Sumw2();
  //RSQ_00_data->Scale( 1./RSQ_00_data->Integral() );

   /////////////////////////////////////////////
  //////////////// MET HT DATA plots/////////////
  ///////////////////////////////////////////
  
  std::vector<TH1F*> DatametXVec = data->PlotMETx();
  std::vector<TH1F*> DatametYVec = data->PlotMETy();
  
  std::vector<TH1F*> DatahtVec = data->PlotHT();
 
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = DatametXVec.begin();	\
       itTT != DatametXVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/Data_metXbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/Data_metXbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = DatametYVec.begin();	\
       itTT != DatametYVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("METplots/Data_metYbox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("METplots/Data_metYbox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }
  
  
  ctr = 0;
  for( std::vector<TH1F*>::iterator itTT = DatahtVec.begin();	\
       itTT != DatahtVec.end(); ++itTT ){
    (*itTT)->Draw();
    metpicname = TString(Form("HTplots/Data_htBox%d.pdf",ctr));
    C0->SaveAs(metpicname);
    metpicname = TString(Form("HTplots/Data_htBox%d.png",ctr));
    C0->SaveAs(metpicname);
    ctr++;
  }


  TCanvas* C1 = new TCanvas("C1", "C1", 1024, 1024);
  C1->cd();
  
  ////////////////////////////////////////////////////////
  /////////////////RSQ O muon Box Stacl plots////////////
  //////////////////////////////////////////////////////
  THStack* stack1 = new THStack("stack1", "RSQ_BOX0");
  
  
    
  RSQ_00_data->SetMarkerStyle(20);
  RSQ_00_data->SetLineColor(1);
  RSQ_00_data->SetMarkerSize(1.5);
  
  RSQ_00_TT->SetFillColor(kMagenta-6);
  RSQ_00_DY->SetFillColor(kAzure-4);
  RSQ_0->SetFillColor(kYellow-6);
  RSQ_00->SetFillColor(kSpring+4);

  leg = new TLegend(0.6,0.6,0.75,0.85);
  
  leg->AddEntry(RSQ_0,"WJets","f");
  leg->AddEntry(RSQ_00,"ZJets","f");
  leg->AddEntry(RSQ_00_TT,"TTJets","f");
  leg->AddEntry(RSQ_00_DY,"DYJets","f");
  leg->AddEntry(RSQ_00_data,"Data","p");
  
  leg->SetHeader("R^{2} Signal Region");
  
    
  stack1->Add(RSQ_0);//Wjets
  stack1->Add(RSQ_00);//ZJets
  stack1->Add(RSQ_00_TT);//TTbar
  stack1->Add(RSQ_00_DY);//DY
  
  RSQ_00_data->Draw("");
  stack1->Draw("same");
  //RSQ_00_data->Draw("same");
  leg->Draw();
  C1->SaveAs("StackPlots/RSQ_0BOX_Stack_R2_0.6.pdf");
  C1->SaveAs("StackPlots/RSQ_0BOX_Stack_R2_0.6.png");
  delete leg;
  /////////////////////////////////////////////////////////
  /////////////////MR O muon Box Stacl plots//////////////
  ///////////////////////////////////////////////////////
  THStack* stackMR_0Box = new THStack("stackMR_0Box", "MR_BOX0");
  
  MR_00_data->SetMarkerStyle(20);
  MR_00_data->SetLineColor(1);
  MR_00_data->SetMarkerSize(1.5);
  
  MR_00_TT->SetFillColor(kMagenta-6);
  MR_00_DY->SetFillColor(kAzure-4);
  MR_0->SetFillColor(kYellow-6);
  MR_00->SetFillColor(kSpring+4);
  

  leg = new TLegend(0.7,0.6,0.85,0.85);
  
  leg->AddEntry(MR_0,"WJets","f");
  leg->AddEntry(MR_00,"ZJets","f");
  leg->AddEntry(MR_00_TT,"TTJets","f");
  leg->AddEntry(MR_00_DY,"DYJets","f");
  leg->AddEntry(MR_00_data,"Data","p");
  
  leg->SetHeader("M_{R} Signal Region");

  stackMR_0Box->Add(MR_0);//Wjets
  stackMR_0Box->Add(MR_00);//ZJets
  stackMR_0Box->Add(MR_00_TT);//TTbar
  stackMR_0Box->Add(MR_00_DY);//DY

  MR_00_data->Draw("");
  stackMR_0Box->Draw("same");
  //MR_00_data->Draw("same");
  leg->Draw();
  C1->SaveAs("StackPlots/MR_0BOX_Stack_R2_0.6.pdf");
  C1->SaveAs("StackPlots/MR_0BOX_Stack_R2_0.6.png");
  delete leg;
  
  ////////////////////////////////////////////////////////
  /////////////////RSQ 1 muon Box Stacl plots////////////
  //////////////////////////////////////////////////////
  THStack* stackRSQ_1Box = new THStack("stackRSQ_1Box", "RSQ_BOX1");
  
  
    
  RSQ_11_data->SetMarkerStyle(20);
  RSQ_11_data->SetLineColor(1);
  RSQ_11_data->SetMarkerSize(1.5);
  
  RSQ_11_TT->SetFillColor(kMagenta-6);
  RSQ_11_DY->SetFillColor(kAzure-4);
  RSQ_1->SetFillColor(kYellow-6);
  RSQ_11->SetFillColor(kSpring+4);

  leg = new TLegend(0.7,0.6,0.85,0.89);
  
  leg->AddEntry(RSQ_1,"WJets","f");
  leg->AddEntry(RSQ_11,"ZJets","f");
  leg->AddEntry(RSQ_11_TT,"TTJets","f");
  leg->AddEntry(RSQ_11_DY,"DYJets","f");
  leg->AddEntry(RSQ_11_data,"Data","p");
  
  leg->SetHeader("R^{2} 1 #mu Control Region");
  
  stackRSQ_1Box->Add(RSQ_1);//Wjets
  stackRSQ_1Box->Add(RSQ_11);//ZJets
  stackRSQ_1Box->Add(RSQ_11_TT);//TTbar
  stackRSQ_1Box->Add(RSQ_11_DY);//DY
  
  stackRSQ_1Box->Draw("");
  RSQ_11_data->Draw("same");
  leg->Draw();
  C1->SaveAs("StackPlots/RSQ_1BOX_Stack_R2_0.6.pdf");
  C1->SaveAs("StackPlots/RSQ_1BOX_Stack_R2_0.6.png");
  delete leg;
    
  /////////////////////////////////////////////////////////
  /////////////////MR 1 muon Box Stacl plots//////////////
  ///////////////////////////////////////////////////////
  THStack* stackMR_1Box = new THStack("stackMR_1Box", "MR_BOX0");
  
  MR_11_data->SetMarkerStyle(20);
  MR_11_data->SetLineColor(1);
  MR_11_data->SetMarkerSize(1.5);
  
  MR_11_TT->SetFillColor(kMagenta-6);
  MR_11_DY->SetFillColor(kAzure-4);
  MR_1->SetFillColor(kYellow-6);
  MR_11->SetFillColor(kSpring+4);

  leg = new TLegend(0.6,0.6,0.75,0.89);
  
  leg->AddEntry(MR_1,"WJets","f");
  leg->AddEntry(MR_11,"ZJets","f");
  leg->AddEntry(MR_11_TT,"TTJets","f");
  leg->AddEntry(MR_11_DY,"DYJets","f");
  leg->AddEntry(MR_11_data,"Data","p");
  
  leg->SetHeader("M_{R} 1 #mu Control Region");

  stackMR_1Box->Add(MR_1);//Wjets
  stackMR_1Box->Add(MR_11);//ZJets
  stackMR_1Box->Add(MR_11_TT);//TTbar
  stackMR_1Box->Add(MR_11_DY);//DY
  
  
  stackMR_1Box->Draw("");
  MR_11_data->Draw("same");
  leg->Draw();
  C1->SaveAs("StackPlots/MR_1BOX_Stack_R2_0.6.pdf");
  C1->SaveAs("StackPlots/MR_1BOX_Stack_R2_0.6.png");
  delete leg;
  
  ////////////////////////////////////////////////////////
  /////////////////RSQ 2 muon Box Stack plots////////////
  //////////////////////////////////////////////////////
  THStack* stackRSQ_2Box = new THStack("stackRSQ_2Box", "RSQ_BOX2");
  
  
    
  RSQ_22_data->SetMarkerStyle(20);
  RSQ_22_data->SetLineColor(1);
  RSQ_22_data->SetMarkerSize(1.5);
  
  RSQ_22_TT->SetFillColor(kMagenta-6);
  RSQ_22_DY->SetFillColor(kAzure-4);
  //RSQ_1->SetFillColor(6);
  //RSQ_11->SetFillColor(kRed);
  
  leg = new TLegend(0.4,0.6,0.69,0.89);
  
  leg->AddEntry(RSQ_22_TT,"TTJets","f");
  leg->AddEntry(RSQ_22_DY,"DYJets","f");
  leg->AddEntry(RSQ_22_data,"Data","p");
  
  leg->SetHeader("R^{2} 2 #mu Control Region");
  
  stackRSQ_2Box->Add(RSQ_22_DY);//DY
  stackRSQ_2Box->Add(RSQ_22_TT);//TTbar
  //stackRSQ_2Box->Add(RSQ_11);//ZJets
  //stackRSQ_2Box->Add(RSQ_1);//Wjets
  
  stackRSQ_2Box->Draw("");
  RSQ_22_data->Draw("same");
  leg->Draw();
  C1->SaveAs("StackPlots/RSQ_2BOX_Stack_R2_0.6.pdf");
  C1->SaveAs("StackPlots/RSQ_2BOX_Stack_R2_0.6.png");
  delete leg;
  
  /////////////////////////////////////////////////////////
  /////////////////MR 2 muon Box Stack plots//////////////
  ///////////////////////////////////////////////////////
  THStack* stackMR_2Box = new THStack("stackMR_2Box", "MR_BOX2");
  
  MR_22_data->SetMarkerStyle(20);
  MR_22_data->SetLineColor(1);
  MR_22_data->SetMarkerSize(1.5);
  
  MR_22_TT->SetFillColor(kMagenta-6);
  MR_22_DY->SetFillColor(kAzure-4);
  //MR_1->SetFillColor(6);
  //MR_11->SetFillColor(kRed);

  leg = new TLegend(0.4,0.6,0.69,0.89);
  
  leg->AddEntry(MR_22_TT,"TTJets","f");
  leg->AddEntry(MR_22_DY,"DYJets","f");
  leg->AddEntry(MR_22_data,"Data","p");
  
  leg->SetHeader("M_{R} 2 #mu Control Region");
  
  stackMR_2Box->Add(MR_22_DY);//DY
  stackMR_2Box->Add(MR_22_TT);//TTbar
  //stackMR_1Box->Add(MR_11);//ZJets
  //stackMR_1Box->Add(MR_1);//Wjets
  
  stackMR_2Box->Draw("");
  MR_22_data->Draw("same");
  leg->Draw();
  C1->SaveAs("StackPlots/MR_2BOX_Stack_R2_0.6.pdf");
  C1->SaveAs("StackPlots/MR_2BOX_Stack_R2_0.6.png");
  delete leg;
  
  TFile* f2 = new TFile("stack1.root","RECREATE");
  
  stack1->Write();
  stackMR_0Box->Write();

  stackRSQ_1Box->Write();
  stackMR_1Box->Write();
  stackRSQ_2Box->Write();
  stackMR_2Box->Write();
  
  f2->Close();

  
  
  
  return 0;
}
