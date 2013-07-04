#ifndef DM_1DRATIOS
#define DM_1DRATIOS 1

#include <iostream>
#include <sstream>
#include "TCanvas.h"
#include "TLatex.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TPad.h"
#include "TString.h"
#include "DM_Base.hh"
#include "THStack.h"

int RatioPlots( TH1F*, TH1F*, TString, TString, TString, TString );
int RatioPlotsV2( THStack*, TH1F*, TH1F*, TString, TString, TString, TString, TLegend* );

#endif
