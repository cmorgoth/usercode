#include "DM_StackPlots.hh"
#include "DM_1DRatio.hh"

void CreateStackPlots(){
 
  
  WJetsHTBins* W = new WJetsHTBins( 2 );
  ///////////////////////////////////////////
  ///////////////WJETS 1D HISTOS/////////////
  ///////////////////////////////////////////

  
  W->PrintEvents();
  
  TH1F* RSQ_0 = new TH1F( W->PlotRSQ_0Box() );
  std::cout << "WJets R2 0BOX: " << RSQ_0->Integral() << std::endl;
  
  TH1F* RSQ_1 = new TH1F( W->PlotRSQ_1Box() );
  std::cout << "WJets R2 1BOX: " << RSQ_1->Integral() << std::endl;
  
  TH1F* MR_0 = new TH1F( W->PlotMR_0Box() );
  std::cout << "WJets MR 0BOX: " << MR_0->Integral() << std::endl;
  
  TH1F* MR_1 = new TH1F( W->PlotMR_1Box() );
  std::cout << "WJets MR 1BOX: " << MR_1->Integral() << std::endl;
  
  TLegend* leg;
  
  std::cout << "pass0" << std::endl;
  
   
  /////////////////////////////////////////////
  ///////////////ZJetsNuNu ANA/////////////////
  /////////////////////////////////////////////
  
  ZJetsNuNu* Z = new ZJetsNuNu( 2 );
  Z->PrintEvents();
  
  
  TH1F* MR_11 = new TH1F( Z->PlotMR_1Box() );
  std::cout << "ZJets MR 1BOX: " << MR_11->Integral() << std::endl;
  
  TH1F* MR_00 = new TH1F( Z->PlotMR_0Box() );
  std::cout << "ZJets MR 0BOX: " << MR_00->Integral() << std::endl;
  
  TH1F* RSQ_11 = new TH1F( Z->PlotRSQ_1Box() );
  std::cout << "ZJets RSQ 1BOX: " << RSQ_11->Integral() << std::endl;
  
  TH1F* RSQ_00 = new TH1F( Z->PlotRSQ_0Box() );
  std::cout << "ZJets RSQ 0BOX: " << RSQ_00->Integral() << std::endl;
  
  //////////////////////////////////////////////////////
  ///////////////// Drell-Yan///////////////////////////
  /////////////////////////////////////////////////////

  DY* dy = new DY( 2 );
  dy->PrintEvents();
  
  TH1F* MR_dy_22 = new TH1F( dy->PlotMR_2Box() );
  std::cout << "dy Jets MR 2BOX: " << MR_dy_22->Integral() << std::endl;
  
  TH1F* MR_dy_11 = new TH1F( dy->PlotMR_1Box() );
  std::cout << "dy Jets MR 1BOX: " << MR_dy_11->Integral() << std::endl;
  
  TH1F* MR_dy_00 = new TH1F( dy->PlotMR_0Box() );
  std::cout << "dy Jets MR 0BOX: " << MR_dy_00->Integral() << std::endl;

  TH1F* RSQ_dy_22 = new TH1F( dy->PlotRSQ_2Box() );
  std::cout << "dy Jets RSQ 2BOX: " << RSQ_dy_22->Integral() << std::endl;

  TH1F* RSQ_dy_11 = new TH1F( dy->PlotRSQ_1Box() );
  std::cout << "dy Jets RSQ 1BOX: " << RSQ_dy_11->Integral() << std::endl;

  TH1F* RSQ_dy_00 = new TH1F( dy->PlotRSQ_0Box() );
  std::cout << "dy Jets RSQ 0BOX: " << RSQ_dy_00->Integral() << std::endl;
  

  /*
  const char* DY_fileName = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/PFJets80/DYJetsToLL_M-50_PT80Total.root";

  //const char* DY_fileName = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/NoTauVeto/DY_NoTauVeto_Total.root";
  
  DYJets* DY = new DYJets( DY_fileName, 2);

  DY->PrintEvents();
  
  std::cout << "debug 0.1" << std::endl;
  TH1F* MR_22_DY = new TH1F( DY->PlotMR_2Box() );
  std::cout << "DYJets MR 2BOX: " << MR_22_DY->Integral() << std::endl;
  
  TH1F* MR_11_DY = new TH1F( DY->PlotMR_1Box() );
  std::cout << "DYJets MR 1BOX: " << MR_11_DY->Integral() << std::endl;
  
  TH1F* MR_00_DY = new TH1F( DY->PlotMR_0Box() );
  std::cout << "DYJets MR 0BOX: " << MR_00_DY->Integral() << std::endl;
  
  TH1F* RSQ_22_DY = new TH1F( DY->PlotRSQ_2Box() );
  std::cout << "DYJets RSQ 2BOX: " << RSQ_22_DY->Integral() << std::endl;
  
  TH1F* RSQ_11_DY = new TH1F( DY->PlotRSQ_1Box() );
  std::cout << "DYJets RSQ 1BOX: " << RSQ_11_DY->Integral() << std::endl;
  
  TH1F* RSQ_00_DY = new TH1F( DY->PlotRSQ_0Box() );
  std::cout << "DYJets RSQ 0BOX: " << RSQ_00_DY->Integral() << std::endl;
  
  */
  
  std::cout << "debug 1" << std::endl;

  //////////////////////////////////////////////////
  /////////////////////////////////////////////////
  /////////////////TTbar + Jets////////////////////
  ////////////////////////////////////////////////
  ///////////////////////////////////////////////

  const char* ttjets_file = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/PFJets80/TTJets80_Tot.root";
  //const char* ttjets_file = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/NoTauVeto/TTJets_NoTauVeto_Total.root";
  
  TTJets* TT = new TTJets(ttjets_file, 2);
  TT->PrintEvents();
  
  TH1F* MR_22_TT = new TH1F( TT->PlotMR_2Box() );
  std::cout << "TTJets MR 2BOX: " << MR_22_TT->Integral() << std::endl;
  
  TH1F* MR_11_TT = new TH1F( TT->PlotMR_1Box() );
  std::cout << "TTJets MR 1BOX: " << MR_11_TT->Integral() << std::endl;

  TH1F* MR_00_TT = new TH1F( TT->PlotMR_0Box() );
  std::cout << "TTJets MR 0BOX: " << MR_00_TT->Integral() << std::endl;

  TH1F* RSQ_22_TT = new TH1F( TT->PlotRSQ_2Box() );
  std::cout << "TTJets RSQ 2BOX: " << RSQ_22_TT->Integral() << std::endl;
  
  TH1F* RSQ_11_TT = new TH1F( TT->PlotRSQ_1Box() );
  std::cout << "TTJets RSQ 1BOX: " << RSQ_11_TT->Integral() << std::endl;
    
  TH1F* RSQ_00_TT = new TH1F( TT->PlotRSQ_0Box() );
  std::cout << "TTJets RSQ 0BOX: " << RSQ_00_TT->Integral() << std::endl;
    
  ////////////////////////////////////////////////////////////////
  //////////////////// DATA//////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  
  const char* data_file = "/afs/cern.ch/work/c/cpena/scratch_DM/CMSSW_5_2_3/src/VecbosApp/V07_5_3_X/HTMHT-Run2012AB/out/HTMHT_AB_PT80Total.root";
  //const char* data_file = "root://eoscms//eos/cms/store/group/phys_susy/razor/Cristian_DM/NoTauVeto/HTMHT_AB_NoTauVeto.root";
  
  Data* data = new Data(data_file, 2);
  data->PrintEvents();
  
  TH1F* MR_22_data = new TH1F( data->PlotMR_2Box() );
  std::cout << "Data MR 2BOX: " << MR_22_data->Integral() << std::endl;
  MR_22_data->Sumw2();
    
  TH1F* MR_11_data = new TH1F( data->PlotMR_1Box() );
  std::cout << "Data MR 1BOX: " << MR_11_data->Integral() << std::endl;
  MR_11_data->Sumw2();
    
  TH1F* MR_00_data = new TH1F( data->PlotMR_0Box() );
  std::cout << "Data MR 0BOX: " << MR_00_data->Integral() << std::endl;
  MR_00_data->Sumw2();
    
  TH1F* RSQ_22_data = new TH1F( data->PlotRSQ_2Box() );
  std::cout << "Data RSQ 2BOX: " << RSQ_22_data->Integral() << std::endl;
  RSQ_22_data->Sumw2();
    
  TH1F* RSQ_11_data = new TH1F( data->PlotRSQ_1Box() );
  std::cout << "Data RSQ 1BOX: " << RSQ_11_data->Integral() << std::endl;
  RSQ_11_data->Sumw2();
  
  TH1F* RSQ_00_data = new TH1F( data->PlotRSQ_0Box() );
  std::cout << "Data RSQ 0BOX: " << RSQ_00_data->Integral() << std::endl;
  RSQ_00_data->Sumw2();
  
  
  TCanvas* C1 = new TCanvas("C1", "C1", 1024, 1024);
  C1->cd();
  
  ////////////////////////////////////////////////////////
  /////////////////RSQ O muon Box Stack plots////////////
  //////////////////////////////////////////////////////
  
  THStack* stack1 = new THStack("stack1", "");
  
  float dataMC_ratio = MR_00_data->GetBinContent(1)/( MR_00->GetBinContent(1) + MR_0->GetBinContent(1) + MR_00_TT->GetBinContent(1) + MR_dy_00->GetBinContent(1) );
  
  std::cout <<  "  data/mc first bin: " <<  dataMC_ratio << std::endl;
  
  //RSQ_00->Scale( dataMC_ratio );
  //RSQ_0->Scale( dataMC_ratio );
  //RSQ_00_TT->Scale( dataMC_ratio );
  //RSQ_dy_00->Scale( dataMC_ratio );
  
  RSQ_00_data->SetMarkerStyle(20);
  RSQ_00_data->SetLineColor(1);
  RSQ_00_data->SetMarkerSize(1.5);
  
  RSQ_00_TT->SetFillColor(kPink+9);
  RSQ_dy_00->SetFillColor(kViolet+9);
  RSQ_0->SetFillColor(kYellow-4);
  RSQ_00->SetFillColor(kSpring+4);

  leg = new TLegend(0.7,0.7,0.9,0.92);
  
  leg->AddEntry(RSQ_0,"W + jets","f");
  leg->AddEntry(RSQ_00,"Z(#nu#bar{#nu}) + jets","f");
  leg->AddEntry(RSQ_00_TT,"t #bar{t} + jets","f");
  leg->AddEntry(RSQ_dy_00,"Z/#gamma^{*}(ll) + jets","f");
  leg->AddEntry(RSQ_00_data,"Data","lep");
  
  //leg->SetHeader("R^{2} Signal Region");
  
  RSQ_0->SetTitle("");
  RSQ_0->SetStats(0);
  RSQ_00->SetTitle("");
  RSQ_00->SetStats(0);
  RSQ_00_TT->SetTitle("");
  RSQ_00_TT->SetStats(0);
  RSQ_dy_00->SetTitle("");
  RSQ_dy_00->SetStats(0);
  RSQ_00_data->SetTitle("");
  RSQ_00_data->SetStats(0);
  
  stack1->Add(RSQ_dy_00);//DY
  stack1->Add(RSQ_00_TT);//TTbar
  stack1->Add(RSQ_0);//Wjets
  stack1->Add(RSQ_00);//ZJets
  
  stack1->Draw();
  ( (TAxis*)( stack1->GetXaxis() ) )->SetLimits(0.5, 1.5);
  ( (TAxis*)( stack1->GetXaxis() ) )->SetTitle("R^{2}");
  stack1->Draw();
  RSQ_00_data->Draw("same");
  
    
  leg->Draw();
  C1->SetLogy();
  C1->SaveAs("StackPlots/RSQ_0BOX_Stack.pdf");
  C1->SaveAs("StackPlots/RSQ_0BOX_Stack.png");
  //delete leg;
  
  TH1F* aux2 = new TH1F( *RSQ_dy_00 );
  aux2->Sumw2();
  aux2->Add( RSQ_00_TT, 1);
  aux2->Add( RSQ_0, 1);
  aux2->Add( RSQ_00, 1);
  RatioPlotsV2(stack1, aux2, RSQ_00_data, "MC 0 #mu BOX", "Data 0 #mu BOX", "StackPlots/Data_MC_RSQ_0BOX", "RSQ", leg);
  delete leg;
  delete aux2;
  
  /////////////////////////////////////////////////////////
  /////////////////MR O muon Box Stacl plots//////////////
  ///////////////////////////////////////////////////////
  THStack* stackMR_0Box = new THStack("stackMR_0Box", "");
  
  std::cout << MR_00->GetBinContent(0)  << "  " << RSQ_00->GetBinContent(1) << std::endl;
  std::cout << MR_00->GetBinContent(2)  << "  " << RSQ_00->GetBinContent(2) << std::endl;
  
  //float dataMC_ratio = MR_00_data->GetBinContent(1)/( MR_00->GetBinContent(1) + MR_0->GetBinContent(1) + MR_00_TT->GetBinContent(1) + MR_dy_00->GetBinContent(1) );
  
  //std::cout <<  "  data/mc first bin: " <<  dataMC_ratio << std::endl;
  
  //MR_00->Scale( dataMC_ratio );
  //MR_0->Scale( dataMC_ratio );
  //MR_00_TT->Scale( dataMC_ratio );
  //MR_dy_00->Scale( dataMC_ratio );
  
  MR_0->SetTitle("");
  MR_0->SetStats(0);
  MR_00->SetTitle("");
  MR_00->SetStats(0);
  MR_00_TT->SetTitle("");
  MR_00_TT->SetStats(0);
  MR_dy_00->SetTitle("");
  MR_dy_00->SetStats(0);
  MR_00_data->SetTitle("");
  MR_00_data->SetStats(0);
  
  MR_00_data->SetMarkerStyle(20);
  MR_00_data->SetLineColor(1);
  MR_00_data->SetMarkerSize(1.5);
  
  MR_00_TT->SetFillColor(kPink+9);
  MR_dy_00->SetFillColor(kViolet+9);
  MR_0->SetFillColor(kYellow-4);
  MR_00->SetFillColor(kSpring+4);
  
  
  leg = new TLegend(0.70,0.7,0.9,0.90);
  
  leg->AddEntry(MR_0,"W + jets","f");
  leg->AddEntry(MR_00,"Z(#nu#nu) + jets","f");
  leg->AddEntry(MR_00_TT,"t #bar{t} + jets","f");
  leg->AddEntry(MR_dy_00,"Z/#gamma^{*}(ll) + jets","f");
  leg->AddEntry(MR_00_data,"Data","lep");
  
  leg->SetHeader("M_{R} Signal Region");
  
  stackMR_0Box->Add(MR_dy_00);//DY
  stackMR_0Box->Add(MR_00_TT);//TTbar
  stackMR_0Box->Add(MR_0);//Wjets
  stackMR_0Box->Add(MR_00);//ZJets
  
  stackMR_0Box->Draw();
  ( (TAxis*)( stackMR_0Box->GetXaxis() ) )->SetTitle("M_{R} (GeV)");
  stackMR_0Box->Draw();
  MR_00_data->Draw("same");
  leg->Draw();
  C1->SetLogy();
  C1->SaveAs("StackPlots/MR_0BOX_Stack.pdf");
  C1->SaveAs("StackPlots/MR_0BOX_Stack.png");

  aux2 = new TH1F( *MR_dy_00 );
  aux2->Sumw2();
  aux2->Add( MR_00_TT, 1);
  aux2->Add( MR_0, 1);
  aux2->Add( MR_00, 1);
  RatioPlotsV2( stackMR_0Box, aux2, MR_00_data, "MC 0 #mu BOX", "Data 0 #mu BOX", "StackPlots/Data_MC_MR_0BOX", "MR", leg);
  delete leg;
  delete aux2; 
  
  ////////////////////////////////////////////////////////
  /////////////////RSQ 1 muon Box Stacl plots////////////
  //////////////////////////////////////////////////////
  THStack* stackRSQ_1Box = new THStack("stackRSQ_1Box", "");
  
  // dataMC_ratio = MR_11_data->GetBinContent(1)/( MR_11->GetBinContent(1) + MR_1->GetBinContent(1) + MR_11_TT->GetBinContent(1) + MR_dy_11->GetBinContent(1) );

  //RSQ_11->Scale( dataMC_ratio );
  //RSQ_1->Scale( dataMC_ratio );
  //RSQ_11_TT->Scale( dataMC_ratio );
  //RSQ_dy_11->Scale( dataMC_ratio );

  RSQ_1->SetTitle("");
  RSQ_1->SetStats(0);
  RSQ_11->SetTitle("");
  RSQ_11->SetStats(0);
  RSQ_11_TT->SetTitle("");
  RSQ_11_TT->SetStats(0);
  RSQ_dy_11->SetTitle("");
  RSQ_dy_11->SetStats(0);
  RSQ_11_data->SetTitle("");
  RSQ_11_data->SetStats(0);
  
  RSQ_11_data->SetMarkerStyle(20);
  RSQ_11_data->SetLineColor(1);
  RSQ_11_data->SetMarkerSize(1.5);
  
  RSQ_11_TT->SetFillColor(kPink+9);
  RSQ_dy_11->SetFillColor(kViolet+9);
  RSQ_1->SetFillColor(kYellow-4);
  RSQ_11->SetFillColor(kSpring+4);

  leg = new TLegend(0.7,0.7,0.9,0.92);
  
  leg->AddEntry(RSQ_1,"W + jets","f");
  leg->AddEntry(RSQ_dy_11,"Z/#gamma^{*}(ll) + jets","f");
  leg->AddEntry(RSQ_11_TT,"t #bar{t} + jets","f");
  leg->AddEntry(RSQ_11_data,"Data","lep");
  leg->SetHeader("R^{2} 1 #mu Control Region");
  
  stackRSQ_1Box->Add(RSQ_dy_11);//DY
  stackRSQ_1Box->Add(RSQ_11_TT);//TTbar
  stackRSQ_1Box->Add(RSQ_1);//Wjets
    
  stackRSQ_1Box->Draw();
  ( (TAxis*)( stackRSQ_1Box->GetXaxis() ) )->SetLimits(0.5, 1.5);
  ( (TAxis*)( stackRSQ_1Box->GetXaxis() ) )->SetTitle("R^{2} ");
  stackRSQ_1Box->Draw();
  RSQ_11_data->Draw("same");
  leg->Draw();
  C1->SetLogy();
  C1->SaveAs("StackPlots/RSQ_1BOX_Stack.pdf");
  C1->SaveAs("StackPlots/RSQ_1BOX_Stack.png");
      
  aux2 = new TH1F( *RSQ_dy_11 );
  aux2->Sumw2();
  aux2->Add( RSQ_11_TT, 1);
  aux2->Add( RSQ_1, 1);
  aux2->Add( RSQ_11, 1);
  RatioPlotsV2( stackRSQ_1Box, aux2, RSQ_11_data, "MC 1 #mu BOX", "Data 1 #mu BOX", "StackPlots/Data_MC_RSQ_1BOX", "RSQ", leg);
  delete leg;
  delete aux2;

  /////////////////////////////////////////////////////////
  /////////////////MR 1 muon Box Stacl plots//////////////
  ///////////////////////////////////////////////////////
  THStack* stackMR_1Box = new THStack("stackMR_1Box", "");
  
  //MR_11->Scale( dataMC_ratio );
  //MR_1->Scale( dataMC_ratio );
  //MR_11_TT->Scale( dataMC_ratio );
  //MR_dy_11->Scale( dataMC_ratio );

  MR_1->SetTitle("");
  MR_1->SetStats(0);
  MR_11->SetTitle("");
  MR_11->SetStats(0);
  MR_11_TT->SetTitle("");
  MR_11_TT->SetStats(0);
  MR_dy_11->SetTitle("");
  MR_dy_11->SetStats(0);
  MR_11_data->SetTitle("");
  MR_11_data->SetStats(0);
  
  MR_11_data->SetMarkerStyle(20);
  MR_11_data->SetLineColor(1);
  MR_11_data->SetMarkerSize(1.5);
  
  MR_11_TT->SetFillColor(kPink+9);
  MR_dy_11->SetFillColor(kViolet+9);
  MR_1->SetFillColor(kYellow-4);
  MR_11->SetFillColor(kSpring+4);

  leg = new TLegend(0.7,0.7,0.9,0.90);
  
  leg->AddEntry(MR_1,"W + jets","f");
  leg->AddEntry(MR_dy_11,"Z/#gamma^{*}(ll) + jets","f");
  leg->AddEntry(MR_11_TT,"t #bar{t} + jets","f");
  leg->AddEntry(MR_11,"Z(#nu#bar{#nu}) + jets","f");
  leg->AddEntry(MR_11_data,"Data","lep");
  
  //leg->SetHeader("M_{R} 1 #mu Control Region");
  
  stackMR_1Box->Add(MR_dy_11);//DY
  stackMR_1Box->Add(MR_11_TT);//TTbar
  stackMR_1Box->Add(MR_1);//Wjets
  stackMR_1Box->Add(MR_11);//ZJets
  
  stackMR_1Box->Draw();
  ( (TAxis*)( stackMR_1Box->GetXaxis() ) )->SetTitle("M_{R} (GeV)");
  stackMR_1Box->Draw();
  MR_11_data->Draw("same");
  leg->Draw();
  C1->SetLogy();
  C1->SaveAs("StackPlots/MR_1BOX_Stack.pdf");
  C1->SaveAs("StackPlots/MR_1BOX_Stack.png");
    
  aux2 = new TH1F( *MR_dy_11 );
  aux2->Sumw2();
  aux2->Add( MR_11_TT, 1);
  aux2->Add( MR_1, 1);
  aux2->Add( MR_11, 1);
  RatioPlotsV2( stackMR_1Box, aux2, MR_11_data, "MC 1 #mu BOX", "Data 1 #mu BOX", "StackPlots/Data_MC_MR_1BOX", "MR", leg);
  delete leg;
  delete aux2;

  ////////////////////////////////////////////////////////
  /////////////////RSQ 2 muon Box Stack plots////////////
  //////////////////////////////////////////////////////
  THStack* stackRSQ_2Box = new THStack("stackRSQ_2Box", "");
  
  //dataMC_ratio = MR_22_data->GetBinContent(1)/(  MR_22_TT->GetBinContent(1) + MR_dy_22->GetBinContent(1) );
  
  //RSQ_22->Scale( dataMC_ratio );
  //RSQ_2->Scale( dataMC_ratio );
  //RSQ_22_TT->Scale( dataMC_ratio );
  //RSQ_dy_22->Scale( dataMC_ratio );
  
  //RSQ_2->SetTitle("");
  //RSQ_2->SetStats(0);
  //RSQ_22->SetTitle("");
  //RSQ_22->SetStats(0);
  RSQ_22_TT->SetTitle("");
  RSQ_22_TT->SetStats(0);
  RSQ_dy_22->SetTitle("");
  RSQ_dy_22->SetStats(0);
  RSQ_22_data->SetTitle("");
  RSQ_22_data->SetStats(0);
  
  RSQ_22_data->SetMarkerStyle(20);
  RSQ_22_data->SetLineColor(1);
  RSQ_22_data->SetMarkerSize(1.5);
  
  RSQ_22_TT->SetFillColor(kPink+9);
  RSQ_dy_22->SetFillColor(kViolet+9);
  
  leg = new TLegend(0.7,0.7,0.9,0.92);
  
  leg->AddEntry(RSQ_22_TT,"t #bar{t} + jets","f");
  leg->AddEntry(RSQ_dy_22,"Z/#gamma^{*}(ll) + jets","f");
  //leg->AddEntry(RSQ_22,"Z(#nu#bar{#nu}) + jets","f");
  //leg->AddEntry(RSQ_2,"W + jets","f");
  leg->AddEntry(RSQ_22_data,"Data","lep");
  
  //leg->SetHeader("R^{2} 2 #mu Control Region");
  
  stackRSQ_2Box->Add(RSQ_22_TT);//TTbar
  stackRSQ_2Box->Add(RSQ_dy_22);//DY
  //stackRSQ_2Box->Add(RSQ_11);//ZJets
  //stackRSQ_2Box->Add(RSQ_1);//Wjets
  
  stackRSQ_2Box->Draw();
  ( (TAxis*)( stackRSQ_2Box->GetXaxis() ) )->SetLimits(0.5, 1.5);
  ( (TAxis*)( stackRSQ_2Box->GetXaxis() ) )->SetTitle("R^{2} ");
  stackRSQ_2Box->Draw();
  RSQ_22_data->Draw("same");
  leg->Draw();
  C1->SetLogy();
  C1->SaveAs("StackPlots/RSQ_2BOX_Stack.pdf");
  C1->SaveAs("StackPlots/RSQ_2BOX_Stack.png");
  

  aux2 = new TH1F( *RSQ_dy_22 );
  aux2->Sumw2();
  aux2->Add( RSQ_22_TT, 1);
  //aux2->Add( RSQ_2, 1);
  //aux2->Add( RSQ_22, 1);                                                                                                        
  RatioPlotsV2( stackRSQ_2Box, aux2, RSQ_22_data, "MC 2 #mu BOX", "Data 2 #mu BOX", "StackPlots/Data_MC_RSQ_2BOX", "RSQ", leg);
  delete leg;
  delete aux2;

  /////////////////////////////////////////////////////////
  /////////////////MR 2 muon Box Stack plots//////////////
  ///////////////////////////////////////////////////////
  THStack* stackMR_2Box = new THStack("stackMR_2Box", "");
  
  //MR_22->Scale( dataMC_ratio );
  //MR_2->Scale( dataMC_ratio );
  //MR_22_TT->Scale( dataMC_ratio );
  //MR_dy_22->Scale( dataMC_ratio );

  //MR_2->SetTitle("");
  //MR_2->SetStats(0);
  //MR_22->SetTitle("");
  //MR_22->SetStats(0);
  MR_22_TT->SetTitle("");
  MR_22_TT->SetStats(0);
  MR_dy_22->SetTitle("");
  MR_dy_22->SetStats(0);
  MR_22_data->SetTitle("");
  MR_22_data->SetStats(0);
  
  MR_22_data->SetMarkerStyle(20);
  MR_22_data->SetLineColor(1);
  MR_22_data->SetMarkerSize(1.5);
  
  MR_22_TT->SetFillColor(kPink+9);
  MR_dy_22->SetFillColor(kViolet+9);
  //MR_1->SetFillColor(6);
  //MR_11->SetFillColor(kRed);

  leg = new TLegend(0.7,0.7,0.9,0.9);
  
  leg->AddEntry(MR_22_TT,"t #bar{t} + jets","f");
  leg->AddEntry(MR_dy_22,"Z/#gamma^{*}(ll) + jets","f");
  //leg->AddEntry(MR_22,"Z(#nu#bar{#nu}) + jets","f");
  //leg->AddEntry(MR_2,"W + jets","f");
  leg->AddEntry(MR_22_data,"Data","lep");
  
  //leg->SetHeader("M_{R} 2 #mu Control Region");
  
  stackMR_2Box->Add(MR_22_TT);//TTbar
  stackMR_2Box->Add(MR_dy_22);//DY
  //stackMR_1Box->Add(MR_22);//ZJets
  //stackMR_1Box->Add(MR_2);//Wjets
  
  stackMR_2Box->Draw();
  ( (TAxis*)( stackMR_2Box->GetXaxis() ) )->SetTitle("R^{2} ");
  
  stackMR_2Box->Draw();
  MR_22_data->Draw("same");
  leg->Draw();
  C1->SetLogy();
  C1->SaveAs("StackPlots/MR_2BOX_Stack.pdf");
  C1->SaveAs("StackPlots/MR_2BOX_Stack.png");
  
  aux2 = new TH1F( *MR_dy_22 );
  aux2->Sumw2();
  aux2->Add( MR_22_TT, 1);
  //aux2->Add( MR_22, 1);
  //aux2->Add( MR_2, 1);
  RatioPlotsV2( stackMR_2Box, aux2, MR_22_data, "MC 2 #mu BOX", "Data 2 #mu BOX", "StackPlots/Data_MC_MR_2BOX", "MR", leg);
  delete leg;
  delete aux2;

  //////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  ////////////////////Saving Histos in File////////////////////////////
  ///////////////////////  Finishing  ////////////////////////////////
  ////////////////////////////////////////////////////////////////////
  
  TFile* f2 = new TFile("stack1.root","RECREATE");
  
  stack1->Write();
  stackMR_0Box->Write();

  stackRSQ_1Box->Write();
  stackMR_1Box->Write();
  stackRSQ_2Box->Write();
  stackMR_2Box->Write();
  
  f2->Close();
  delete C1;
  delete W;
  delete TT;
  delete Z;
  delete dy;
  delete data;



}
