#include <iostream>
#include "PhosphorCorrectorFunctor.hh"

int main(){
  
  //Creates Functor object (true, means we are using the r9 categories)
  zgamma::PhosphorCorrectionFunctor* obj = new zgamma::PhosphorCorrectionFunctor("PHOSPHOR_NUMBERS_EXPFIT.txt", true);

  //std::cout << obj->GetScaleCorr(2011, 15.5, 1.23) << std::endl;

  // GetCorrEnergy(float R9, int year, double pt, double eta, double Egen)
  // So this method is only for MC since you a specifying the gen level Energy in the last entry
  std::cout << "MC EXAMPLE CORRECTION Low R9, Corrected energy:" << obj->GetCorrEnergy(0.8, 2012, 14., -1.23, 25.6) << std::endl;
  //GetCorrEnergy(float R9, int year, double pt, double eta)
  // Correction only for Data note the overloding of the previos method( we don't pass Egen)
  std::cout << "DATA EXAMPLE CORRECTION High R9, Corrected energy:" << obj->GetCorrEnergy(0.97, 2012, 14., -1.23) << std::endl;

  //GetCorrEt(float R9, int year, double pt, double eta)
  // Get Corrected Transverse Energy for data (R9 = -666.0 meand using inclusive numbers)
  std::cout << "DATA EXAMPLE CORRECTION Inclusive R9, Corrected ET:" << obj->GetCorrEt(-666., 2012, 14., -1.23) << std::endl;

  //GetCorrEt(float R9, int year, double pt, double eta, double Egen)
  // Get Corrected Transverse Energy for MC (R9 = -666.0 meand using inclusive numbers)
  std::cout << "MC EXAMPLE CORRECTION Inclusive R9, Corrected ET:" << obj->GetCorrEt(-666., 2012, 14., -1.23, 25.6) << std::endl;

}
