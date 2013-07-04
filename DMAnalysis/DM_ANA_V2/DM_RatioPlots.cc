#include "DM_RatioPlots.hh"
#include "DM_1DRatio.hh"
#include "DM_2DRatio.hh"

void CreateRatioPlots(){

  TCanvas* C0 = new TCanvas("C0", "C0", 1024, 1024);
  C0->cd();  
  TLegend* leg;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////// W + Jets //////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  //WJets* W = new WJets(wjets_file, 2);
  
  WJetsHTBins* W = new WJetsHTBins( 2 );
  
  //////////////////////////////////////////////////////
  ///////////////WJETS 1D HISTOS////////////////////////
  //////////////////////////////////////////////////////
  
  
  TH1F* RSQ_W00 = new TH1F( W->PlotRSQ_0Box() );
  RSQ_W00->Sumw2();
  RSQ_W00->Scale(1./RSQ_W00->Integral());
  
  TH1F* RSQ_W11 = new TH1F( W->PlotRSQ_1Box() );
  RSQ_W11->Sumw2();
  RSQ_W11->Scale(1./RSQ_W11->Integral());
  
  TH1F* MR_W00 = new TH1F( W->PlotMR_0Box() );
  MR_W00->Sumw2();
  MR_W00->Scale(1./MR_W00->Integral());
  
  TH1F* MR_W11 = new TH1F( W->PlotMR_1Box() );
  MR_W11->Sumw2();
  MR_W11->Scale(1./MR_W11->Integral());
  
  ////////
  ////////
  RatioPlots( MR_W00, MR_W11, "W + Jets (l#nu) 0 #mu BOX", "W + Jets (l#nu) 1 #mu BOX", "RatioPlots/WJetsMR_TauVeto", "MR");
  RatioPlots( RSQ_W00, RSQ_W11, "W + Jets (l#nu) 0 #mu BOX", "W + Jets (l#nu) 1 #mu BOX", "RatioPlots/WJetsRSQ_TauVeto", "RSQ");
  
  std::cout << " W+Jets +++++ 1D RATIOS are Done +++++++" << std::endl;
  
  ///////////////////////////////////////////////////////
  /////////////////WJETS 2D HISTOS///////////////////////
  ///////////////////////////////////////////////////////
  TH2F*  MR_R2_1BOX = new TH2F( W->PlotRSQ_vs_MR_1Box() );
  MR_R2_1BOX->Sumw2();
  
  TH2F*  MR_RSQ_0BOX = new TH2F( W->PlotRSQ_vs_MR_0Box() );
  MR_RSQ_0BOX->Sumw2();
  
  //TH2F* MR_R2_1BOX = new TH2F();
  //W->PlotRSQ_vs_MR_1Box( MR_R2_1BOX );  
  
  //TH2F* MR_RSQ_0BOX = new TH2F( );
  //W->PlotRSQ_vs_MR_0Box( MR_RSQ_0BOX );
  
  TH2F* wjRatio = (TH2F*)RatioPlotsTwoD( MR_RSQ_0BOX, MR_R2_1BOX, "RatioPlots/Wjets2D", "Wjets2dRatio");

  std::cout << " W+Jets +++++ 1D RATIOS are Done +++++++" << std::endl;  

  std::cout << "Number of Entries: " << wjRatio->Integral() << std::endl;
	
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////// Z(NuNu) + Jets ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

  

  ZJetsNuNu* Z = new ZJetsNuNu( 2 );
  
  ///////////////////////////////////////////
  ///////////////ZJETS(NuNu) 1D HISTOS///////
  ///////////////////////////////////////////
  
  
  
  TH1F* MR_Z11 = new TH1F( Z->PlotMR_1Box() );
  MR_Z11->Sumw2();
  MR_Z11->Scale( 1./MR_Z11->Integral() );
  
  TH1F* MR_Z00 = new TH1F( Z->PlotMR_0Box() );
  MR_Z00->Sumw2();
  MR_Z00->Scale( 1./MR_Z00->Integral() );
  
  TH1F* RSQ_Z11 = new TH1F( Z->PlotRSQ_1Box() );
  RSQ_Z11->Sumw2();
  RSQ_Z11->Scale( 1./RSQ_Z11->Integral() );
  
  TH1F* RSQ_Z00 = new TH1F( Z->PlotRSQ_0Box() );
  RSQ_Z00->Sumw2();
  RSQ_Z00->Scale( 1./RSQ_Z00->Integral() );
  
  ///////////////////////////////////////////
  //////////////////2D///////////////////////
  //////////////////////////////////////////
  
  TH2F*  MR_RSQ_0BOX_Z = new TH2F( Z->PlotRSQ_vs_MR_0Box() );
  MR_RSQ_0BOX_Z->Sumw2();
  //MR_RSQ_0BOX_Z->Scale( 1./MR_RSQ_0BOX_Z->Integral() );
  
  TH2F*  MR_RSQ_1BOX_Z = new TH2F( Z->PlotRSQ_vs_MR_1Box() );
  MR_RSQ_1BOX_Z->Sumw2();
  //MR_RSQ_1BOX_Z->Scale( 1./MR_RSQ_1BOX_Z->Integral() );
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////// ZGamma(ll) + Jets /////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  DY* dy = new DY(2);
  
  ////////////////////////////////////////////////
  /////////////Zgamma*(ll)////////////////////////
  ////////////////////////////////////////////////
  
  
  TH1F* MR_DY22 = new TH1F( dy->PlotMR_2Box() );
  MR_DY22->Sumw2();
  MR_DY22->Scale( 1./MR_DY22->Integral() );
  
  TH1F* MR_DY11 = new TH1F( dy->PlotMR_1Box() );
  MR_DY11->Sumw2();
  MR_DY11->Scale( 1./MR_DY11->Integral() );
  
  TH1F* MR_DY00 = new TH1F( dy->PlotMR_0Box() );
  MR_DY00->Sumw2();
  MR_DY00->Scale( 1./MR_DY00->Integral() );
  
  TH1F* RSQ_DY22 = new TH1F( dy->PlotRSQ_2Box() );
  RSQ_DY22->Sumw2();
  RSQ_DY22->Scale( 1./RSQ_DY22->Integral() );
  
  TH1F* RSQ_DY11 = new TH1F( dy->PlotRSQ_1Box() );
  RSQ_DY11->Sumw2();
  RSQ_DY11->Scale( 1./RSQ_DY11->Integral() );
  
  TH1F* RSQ_DY00 = new TH1F( dy->PlotRSQ_0Box() );
  RSQ_DY00->Sumw2();
  RSQ_DY00->Scale( 1./RSQ_DY00->Integral() );
  
  ///////////////////////////////////////////
  //////////////////2D///////////////////////
  //////////////////////////////////////////
  
  TH2F*  MR_RSQ_0BOX_DY = new TH2F( dy->PlotRSQ_vs_MR_0Box() );
  
  TH2F*  MR_RSQ_1BOX_DY = new TH2F( dy->PlotRSQ_vs_MR_1Box() );
    
  TH2F*  MR_RSQ_2BOX_DY = new TH2F( dy->PlotRSQ_vs_MR_2Box() );
  
  std::cout << "DY0mu: " << MR_RSQ_0BOX_DY->Integral() << std::endl;
  std::cout << "DY1mu: " << MR_RSQ_1BOX_DY->Integral() << std::endl;
  std::cout << "DY2mu: " << MR_RSQ_2BOX_DY->Integral() << std::endl;
  
  //////////////////////////////////////
  ///////////DY 1mu/2mu BOX////////////
  /////////////////////////////////////
  
  RatioPlots( MR_DY11, MR_DY22, "Z/#gamma^{*}(ll) + Jets 1 #mu BOX", "Z/#gamma^{*}(ll) + Jets 2 #mu BOX", "RatioPlots/DYJets_MR_1to2box", "MR");
  RatioPlots( RSQ_DY11, RSQ_DY22, "Z/#gamma^{*}(ll) + Jets 1 #mu BOX", "Z/#gamma^{*}(ll) + Jets 2 #mu BOX", "RatioPlots/DYJets_RSQ_1to2box", "RSQ");
  
  TH2F* DY_1to2 = (TH2F*)RatioPlotsTwoD( MR_RSQ_1BOX_DY, MR_RSQ_2BOX_DY, "RatioPlots/DY2dRatio_1to2box", "DY2dRatio_1to2box");
  
  //////////////////////////////////////
  ///////////DY 0mu/2mu BOX////////////
  /////////////////////////////////////
  
  RatioPlots( MR_DY00, MR_DY22, "Z/#gamma^{*}(ll) + Jets 0 #mu BOX", "Z/#gamma^{*}(ll) + Jets 2 #mu BOX", "RatioPlots/DYJets_MR_0to2box", "MR");
  RatioPlots( RSQ_DY00, RSQ_DY22, "Z/#gamma^{*}(ll) + Jets 0 #mu BOX", "Z/#gamma^{*}(ll) + Jets 2 #mu BOX", "RatioPlots/DYJets_RSQ_0to2box", "RSQ");
  
  TH2F* DY_0to2 = (TH2F*)RatioPlotsTwoD( MR_RSQ_0BOX_DY, MR_RSQ_2BOX_DY, "RatioPlots/DY2dRatio_0to2box", "DY2dRatio_0to2box");
  
  //////////////////////////////////////
  ///////////DY-Znunu 0mu/2mu BOX///////
  /////////////////////////////////////
  
  RatioPlots( MR_Z00, MR_DY22, "Z(#nu #bar{#nu}) + Jets 0 #mu BOX", "Z/#gamma^{*}(ll) + Jets 2 #mu BOX", "RatioPlots/Znunu_DYJets_MR_0to2box", "MR");
  RatioPlots( RSQ_Z00, RSQ_DY22, "Z(#nu #bar{#nu}) + Jets 0 #mu BOX", "Z/#gamma^{*}(ll) + Jets 2 #mu BOX", "RatioPlots/Znunu_DYJets_RSQ_0to2box", "RSQ");
  
  TH2F* Z_DY_0to2 = (TH2F*)RatioPlotsTwoD( MR_RSQ_0BOX_Z, MR_RSQ_2BOX_DY, "RatioPlots/Znunu_DYJets_2dRatio_1to2box", "Znunu_DYJets_2dRatio_0to2box");
  
  std::cout << "DY 0mu/2mu --> " << DY_0to2->Integral() << std::endl;
  std::cout << "Z DY 0mu/2mu --> " << Z_DY_0to2->Integral() << std::endl;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////// TTbar + Jets //////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  const char* ttjets_file = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/PFJets80/TTJets80_Tot.root";
  //const char* ttjets_file = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/NoTauVeto/TTJets_NoTauVeto_Total.root";
  
  TTJets* TT = new TTJets(ttjets_file, 2);
  
  /////////////////////////////////////////////////
  /////////////////TTbar + Jets 1D/////////////////
  ////////////////////////////////////////////////
  
  TH1F* MR_22_TT = new TH1F( TT->PlotMR_2Box() );
  MR_22_TT->Sumw2();
  MR_22_TT->Scale( 1./MR_22_TT->Integral() );
  
  TH1F* MR_11_TT = new TH1F( TT->PlotMR_1Box() );
  MR_11_TT->Sumw2();
  MR_11_TT->Scale( 1./MR_11_TT->Integral() );
  
  TH1F* MR_00_TT = new TH1F( TT->PlotMR_0Box() );
  MR_00_TT->Sumw2();
  MR_00_TT->Scale( 1./MR_00_TT->Integral() );
  
  TH1F* RSQ_22_TT = new TH1F( TT->PlotRSQ_2Box() );
  RSQ_22_TT->Sumw2();
  RSQ_22_TT->Scale( 1./RSQ_22_TT->Integral() );
  
  TH1F* RSQ_11_TT = new TH1F( TT->PlotRSQ_1Box() );
  RSQ_11_TT->Sumw2();
  RSQ_11_TT->Scale( 1./RSQ_11_TT->Integral() );
  
  TH1F* RSQ_00_TT = new TH1F( TT->PlotRSQ_0Box() );
  RSQ_00_TT->Sumw2();
  RSQ_00_TT->Scale( 1./RSQ_00_TT->Integral() );

  ////////////////////////////////////////
  //////////////////2D TT+jets////////////
  ////////////////////////////////////////
  
  TH2F*  MR_RSQ_1BOX_TT = new TH2F( );
  TT->PlotRSQ_vs_MR_1Box( MR_RSQ_1BOX_TT );
  
  TH2F*  MR_RSQ_0BOX_TT = new TH2F( );
  TT->PlotRSQ_vs_MR_0Box( MR_RSQ_0BOX_TT ); 
  
  ////////////////////////////////////////////////////////////////
  //////////////////// DATA//////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  
  const char* data_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/V07_5_3_X/HTMHT-Run2012AB/out/HTMHT_AB_PT80Total.root";

  //const char* data_file = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/NoTauVeto/HTMHT_AB_NoTauVeto.root";

  Data* data = new Data(data_file, 2);
  //data->PrintEvents();
  
  TH1F* MR_22_data = new TH1F( data->PlotMR_2Box() );
  MR_22_data->Sumw2();
  MR_22_data->Scale ( 1./MR_22_data->Integral() );
  
  TH1F* MR_11_data = new TH1F( data->PlotMR_1Box() );
  MR_11_data->Sumw2();
  MR_11_data->Scale ( 1./MR_11_data->Integral() );
  
  TH1F* MR_00_data = new TH1F( data->PlotMR_0Box() );
  MR_00_data->Sumw2();
  MR_00_data->Scale ( 1./MR_00_data->Integral() );
  
  TH1F* RSQ_22_data = new TH1F( data->PlotRSQ_2Box() );
  RSQ_22_data->Sumw2();
  RSQ_22_data->Scale ( 1./RSQ_22_data->Integral() );  
  
  TH1F* RSQ_11_data = new TH1F( data->PlotRSQ_1Box() );
  RSQ_11_data->Sumw2();
  RSQ_11_data->Scale ( 1./RSQ_11_data->Integral() );  
  
  TH1F* RSQ_00_data = new TH1F( data->PlotRSQ_0Box() );
  RSQ_00_data->Sumw2();
  RSQ_00_data->Scale ( 1./RSQ_00_data->Integral() );
  
  ///////////////////////////////////////////
  //////////////////2D///////////////////////
  //////////////////////////////////////////
  
  TH2F*  data0 = new TH2F( );
  data->PlotRSQ_vs_MR_0Box( data0 );
  
  TH2F*  data1 = new TH2F( );
  data->PlotRSQ_vs_MR_1Box( data1 );
    
  TH2F*  data2 = new TH2F( );
  data->PlotRSQ_vs_MR_2Box( data2 );
    
  ///////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  //////////////////// Predicting BKG///////////////////////////////
  //////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////


  TH2F* data_dy1mu = new TH2F( *data2 );
  //data_dy1mu->Sumw2();
  std::cout << "Total Data 2muon Box: " << data_dy1mu->Integral() << std::endl;
  data_dy1mu->Multiply( DY_1to2 );
  std::cout << "Bkg prediction for DY in the 1 muon box: " << data_dy1mu->Integral() << std::endl;
  
  TH2F* data_wj1mu = new TH2F( *data1 );
  std::cout << "Total Data 1 muon Box: " << data_wj1mu->Integral() << std::endl;
  //data_wj1mu->Sumw2();
  data_wj1mu->Add(data_dy1mu, -1.0);
  data_wj1mu->Add(MR_RSQ_1BOX_TT, -1.0);
  
  std::cout << "Bkg prediction for W+jets in the 1 muon box: " << data_wj1mu->Integral() << std::endl;

  std::cout << "==========TOTAL Bkg prediction 1 muon box: " << data_wj1mu->Integral() + data_dy1mu->Integral() + MR_RSQ_1BOX_TT->Integral()  << std::endl;
  
  TH2F* bkg_wj_0mu = new TH2F( *data_wj1mu );
  bkg_wj_0mu->Multiply( wjRatio );//wjRatio is W + jest 0mu/1mu
 
  std::cout << "Bkg Prediction for W+jets in the 0 muon box: " << bkg_wj_0mu->Integral() << std::endl;
  
  TH2F* bkg_ZDY = new TH2F( *data2 );
  //std::cout << "data2 : " << bkg_ZDY->Integral() << std::endl;
  
  TH2F* zero_2muon = new TH2F( *Z_DY_0to2 );
  Z_DY_0to2->Multiply(data2);
  std::cout << "Z(nunu) Prediction 0Muon box : " << Z_DY_0to2->Integral() << std::endl;
  
  zero_2muon->Add( DY_0to2, 1.0);
  //std::cout << "Z DY 0to2 MC (2): " << zero_2muon->Integral() << std::endl;
  DY_0to2->Multiply(data2);
  std::cout << "DY Prediction 0Muon box " << DY_0to2->Integral() << std::endl;
  
  zero_2muon->Multiply( bkg_ZDY );
  
  std::cout << "Total(DY+Z(nunu)) Bkg contribution 0 muon box: " << zero_2muon->Integral() << std::endl;

  TH2F* tot_bkg_0mu = new TH2F( *zero_2muon );
  tot_bkg_0mu->Add(bkg_wj_0mu,1.0);
  tot_bkg_0mu->Add(MR_RSQ_0BOX_TT,1.0);
  
  std::cout << "Total Bkg contribution 0 muon box: " << tot_bkg_0mu->Integral() << std::endl;
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////// FINALIZING //////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  delete C0;
  delete W;
  delete TT;
  delete Z;
  delete dy;
  
  
  
  
};
