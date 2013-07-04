#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "PhosphorCorrectorFunctor.hh"


zgamma::PhosphorCorrectionFunctor::PhosphorCorrectionFunctor(){

};//default constructor
zgamma::PhosphorCorrectionFunctor::PhosphorCorrectionFunctor(const char* filename){

  rand = new TRandom3(0);
  //this->MapFile.ifstream(filename);
  if( !SetMapFileName(filename) ){
    std::cout << "[INFO]--> Problems openning the file" << std::endl;
  }else{
    if( !CreateMap() ){
      std::cout << "[INFO]--> Some Problem Filling the MAP Was Found, please check your MAP FILE" << std::endl;
    }
  }
};



zgamma::PhosphorCorrectionFunctor::PhosphorCorrectionFunctor(const char* filename, bool R9Cat){
  
  rand = new TRandom3(0);
  //this->MapFile.ifstream(filename);
  if( !SetMapFileName(filename) ){
    std::cout << "[INFO]--> Problems openning the file" << std::endl;
  }else{
    if( !CreateMap( true ) ){
      std::cout << "[INFO]--> Some Problem Filling the MAP Was Found, please check your MAP FILE" << std::endl;
    }
  }
};



zgamma::PhosphorCorrectionFunctor::~PhosphorCorrectionFunctor(){
  delete rand;
};

double zgamma::PhosphorCorrectionFunctor::FabSmear(double E, double eta, double r9){

  float r9_bad_eb[]  = { 8.91085e-03, 6.60522e-03, -2.86797e-02, 4.73330e-02, -1.95607e-02 };
  float r9_gold_eb[] = { 7.62684e-03, 1.13788e-02, -4.14171e-02, 5.57636e-02, -1.93949e-02 };
  
  float r9_gold_ee[] = { -4.64302e-01, 9.20859e-01, -5.54852e-01, 1.07274e-01, 0 };
  float r9_bad_ee[]  = { -1.47432e-01, 2.22487e-01, -1.26847e-02,-6.83499e-02, 1.99454e-02 };
  
  
  float *par = 0;
  if( fabs(eta) <  1.5 && r9 >  0.94 ) par = r9_gold_eb;
  if( fabs(eta) <  1.5 && r9 <= 0.94 ) par = r9_bad_eb;
  if( fabs(eta) >= 1.5 && r9 >  0.94 ) par = r9_gold_ee;
  if( fabs(eta) >= 1.5 && r9 <= 0.94 ) par = r9_bad_ee;
  
  float res = 0;
  for( int ip = 4 ; ip >= 0; ip-- ) res = par[ip] + fabs(eta)*res; 

  return ( 1 + rand->Gaus(0, res ) )*E;

};

bool zgamma::PhosphorCorrectionFunctor::SetMapFileName(const char* filename){
this->filename = filename;

 return true;
};

bool zgamma::PhosphorCorrectionFunctor::CreateMap(){
  int year, dataType, detType, corrType, ptBin;
  double corrNumber;
  MapFile.open(filename);
  std::string line;
  std::string KeyMap;
  if(  MapFile.is_open() ){
    getline (MapFile, line);
    //getline (MapFile, line);
    //std::cout << line << std::endl;
    while( MapFile.good() ){
     
      if( MapFile.eof() )break;
      MapFile >> year >> dataType >> detType >> ptBin >> corrType >> corrNumber;
      
      KeyMap =  CreateMapKey( year, dataType, detType, corrType, ptBin);
      //std::cout << "debug: " << KeyMap << std::endl;
      CorrMap[KeyMap] = corrNumber;
    }

  }else{
    std::cout << "[INFO]--> Unable to open MAP FILE" << std::endl;
    return false;
  }
  
  if( CorrMap.size() == 64) { 
    return true;
  }else{
    return false;
  }

};



bool zgamma::PhosphorCorrectionFunctor::CreateMap(bool R9Cat){
  int year, dataType, detType, r9Cat,corrType, ptBin;
  double corrNumber;
  MapFile.open(filename);
  std::string line;
  std::string KeyMap;
  if(  MapFile.is_open() ){
    getline (MapFile, line);
    //getline (MapFile, line);
    //std::cout << line << std::endl;
    while( MapFile.good() ){
     
      if( MapFile.eof() )break;
      MapFile >> year >> dataType >> detType >> r9Cat >> ptBin >> corrType >> corrNumber;
      
      KeyMap =  CreateMapKey( year, dataType, detType, r9Cat, corrType, ptBin);
      //std::cout << "debug: " << KeyMap << std::endl;
      CorrMap[KeyMap] = corrNumber;
    }

  }else{
    std::cout << "[INFO]--> Unable to open MAP FILE" << std::endl;
    return false;
  }
  
  std::cout << "[INFO]--> MAP SIZE: " << CorrMap.size() << std::endl;
  if( CorrMap.size() == 192) { 
    return true;
  }else{
    return false;
  }

};



std::string zgamma::PhosphorCorrectionFunctor:: CreateMapKey(int Year, int DataType, int DetType, int CorrType, int PtBin){
  
  stringstream ss;
  
  ss << Year << DataType << DetType  << CorrType << PtBin;

  return ss.str();
  
  
};

std::string zgamma::PhosphorCorrectionFunctor:: CreateMapKey(int Year, int DataType, int DetType, int R9Cat, int CorrType, int PtBin){
  
  stringstream ss;
  
  ss << Year << DataType << DetType  << R9Cat << CorrType << PtBin;

  return ss.str();
  
  
};


double zgamma::PhosphorCorrectionFunctor::GetScaleCorr(int year, double pt, double eta){
  year == 2011 ? year = XX_XI : year = XX_XII;
  int dataType = Data;
  int corrType = Scale;
  int ptBin = -1;
  int detType = -1;
  
  if( fabs(eta) < 1.479){
    detType = EB;
  }else{
    detType = EE;
  }

  if(pt > 10 && pt <= 12){
    ptBin = Pt0;
  }else if(pt > 12 && pt <= 15){
    ptBin = Pt1;
  }else if(pt > 15 && pt <= 20){
    ptBin = Pt2;
  }else if(pt > 20 && pt <= 999){
    ptBin = Pt3;
  }
  
  //std::cout << "debug2: " << year << " " << dataType  << " " << detType  << " " << corrType << " " << ptBin <<  std::endl;
  string KeyMap =  CreateMapKey( year, dataType, detType, corrType, ptBin);
  //std::cout << "debug2: " << KeyMap << std::endl;

  if( CorrMap.find(KeyMap) == CorrMap.end() )return -999.;
  
  return CorrMap[KeyMap];

};




double zgamma::PhosphorCorrectionFunctor::GetCorrEnergy(int year, double pt, double etaReco, double Egen){
  
  int dataType = Data;
  int corrType = Scale;
  int ptBin = -1;
  int detType = -1;
  
  if( year == 2011){
    year = XX_XI; 
  }else if( year == 2012){
    year = XX_XII;
  }else std::cout << "[INFO]--> Unknown YEAR, please check, inputs are 2011 or 2012 only" << std::endl;
  
  if( fabs(etaReco) < 1.5){
    detType = EB;
  }else{
    detType = EE;
  }
  
  if(pt > 10 && pt <= 12){
    ptBin = Pt0;
  }else if(pt > 12 && pt <= 15){
    ptBin = Pt1;
  }else if(pt > 15 && pt <= 20){
    ptBin = Pt2;
  }else if(pt > 20 && pt <= 999){
    ptBin = Pt3;
  }
  //if(pt>10 && pt <12)std::cout << "blah" << year << std::endl;
  string KeyMap_Smc =  CreateMapKey( year, 0, detType, 0, ptBin);// CreateMapKey( year, dataType, detType, corrType, ptBin);MC=0 && Scale==0
  string KeyMap_Rmc =  CreateMapKey( year, 0, detType, 1, ptBin);//MC=0 && Resolution==1
  string KeyMap_Rdata =  CreateMapKey( year, 1, detType, 1, ptBin);//Data=1 && Resolution==1
  std::map<std::string, double>::iterator it_Smc = CorrMap.find(KeyMap_Smc);
  std::map<std::string, double>::iterator it_Rmc = CorrMap.find(KeyMap_Rmc);
  std::map<std::string, double>::iterator it_Rdata = CorrMap.find(KeyMap_Rdata);

  if( it_Smc == CorrMap.end() ){
    std::cout << "[INFO]-->Scale MC NOT found on the MAP, correction not applied" << "Pt = "  << pt << " eta = " << etaReco << std::endl;
    return ETtoE( pt, etaReco);
    
  }else if( it_Rmc == CorrMap.end() ){
    std::cout << "[INFO]-->Resolution MC NOT found on the MAP, correction not applied" << std::endl;
    return ETtoE( pt, etaReco);
    
  }else if( it_Rdata == CorrMap.end() ){
    std::cout << "[INFO]-->Resolution data NOT found on the MAP, correction not applied" << std::endl;
    return ETtoE( pt, etaReco);
  }else{
    //Actually now we apply the correction
    double Smc = 0.01*((*it_Smc).second) ;//Converting into number from %
    double Rmc = (*it_Rmc).second;
    double Rdata = (*it_Rdata).second;
    double E = ETtoE( pt, etaReco);
    double X_mc = E/Egen -1.0;
    double X_corr = (Rdata/Rmc)*( X_mc - Smc );

    
    return (1.0 + X_corr)*Egen;
      


  }
};


double zgamma::PhosphorCorrectionFunctor::GetCorrEnergy(float R9, int year, double pt, double etaReco, double Egen){
  
  int dataType = Data;
  int corrType = Scale;
  int ptBin = -1;
  int detType = -1;
  int r9Cat = -1;
  
  if( year == 2011){
    year = XX_XI; 
  }else if( year == 2012){
    year = XX_XII;
  }else std::cout << "[INFO]--> Unknown YEAR, please check, inputs are 2011 or 2012 only" << std::endl;
  
  if( fabs(etaReco) < 1.5){
    detType = EB;
  }else{
    detType = EE;
  }
  
  if(pt > 10 && pt <= 12){
    ptBin = Pt0;
  }else if(pt > 12 && pt <= 15){
    ptBin = Pt1;
  }else if(pt > 15 && pt <= 20){
    ptBin = Pt2;
  }else if(pt > 20 && pt <= 999){
    ptBin = Pt3;
  }

  if ( R9 > 0.94 ){
    r9Cat = 1;//
  }else if ( R9 <= 0.94 && R9 > -10. ){
    r9Cat = 2;//Low R9
  }else if ( R9 == -666. ){
    r9Cat = 0;//Inclusive Category
  }
  //if(pt>10 && pt <12)std::cout << "blah" << year << std::endl;
  string KeyMap_Smc =  CreateMapKey( year, 0, detType, r9Cat, 0, ptBin);// CreateMapKey( year, dataType, detType, corrType, ptBin);MC=0 && Scale==0
  string KeyMap_Rmc =  CreateMapKey( year, 0, detType, r9Cat, 1, ptBin);//MC=0 && Resolution==1
  string KeyMap_Rdata =  CreateMapKey( year, 1, detType, r9Cat, 1, ptBin);//Data=1 && Resolution==1
  std::map<std::string, double>::iterator it_Smc = CorrMap.find(KeyMap_Smc);
  std::map<std::string, double>::iterator it_Rmc = CorrMap.find(KeyMap_Rmc);
  std::map<std::string, double>::iterator it_Rdata = CorrMap.find(KeyMap_Rdata);
  
  if( it_Smc == CorrMap.end() ){
    std::cout << "[INFO]-->Scale MC NOT found on the MAP, correction not applied" << "Pt = "  << pt << " eta = " << etaReco << std::endl;
    return ETtoE( pt, etaReco);
    
  }else if( it_Rmc == CorrMap.end() ){
    std::cout << "[INFO]-->Resolution MC NOT found on the MAP, correction not applied" << std::endl;
    return ETtoE( pt, etaReco);
    
  }else if( it_Rdata == CorrMap.end() ){
    std::cout << "[INFO]-->Resolution data NOT found on the MAP, correction not applied" << std::endl;
    return ETtoE( pt, etaReco);
  }else{
    //Actually now we apply the correction
    double Smc = 0.01*((*it_Smc).second) ;//Converting into number from %
    double Rmc = (*it_Rmc).second;
    double Rdata = (*it_Rdata).second;
    double E = ETtoE( pt, etaReco);
    double X_mc = E/Egen -1.0;
    double X_corr = (Rdata/Rmc)*( X_mc - Smc );

    
    return (1.0 + X_corr)*Egen;
      


  }
};

double zgamma::PhosphorCorrectionFunctor::GetCorrEnergy(int year, double pt, double etaReco){

  int dataType = Data;
  int corrType = Scale;
  int ptBin = -1;
  int detType = -1;
  
  if( year == 2011){
    year = XX_XI; 
  }else if( year == 2012){
    year = XX_XII;
  }else std::cout << "[INFO]--> Unknown YEAR, please check, inputs are 2011 or 2012 only" << std::endl;
  
  if( fabs(etaReco) < 1.5){
    detType = EB;
  }else{
    detType = EE;
  }
  
  if(pt > 10 && pt <= 12){
    ptBin = Pt0;
  }else if(pt > 12 && pt <= 15){
    ptBin = Pt1;
  }else if(pt > 15 && pt <= 20){
    ptBin = Pt2;
  }else if(pt > 20 && pt <= 999){
    ptBin = Pt3;
  }
  

  // std::cout << "debug2: " << year << " " << dataType  << " " << detType  << " " << corrType << " " << ptBin <<  std::endl;
  string KeyMap =  CreateMapKey( year, dataType, detType, corrType, ptBin);
  //std::cout << "debug2: " << KeyMap << std::endl;
  
  if( CorrMap.find(KeyMap) == CorrMap.end() ){
    std::cout << "[INFO]-->Scale Data Not found, No correction applied. PT:  " << pt <<std::endl;
    return ETtoE( pt, etaReco);
  }else{
    double Sdata = 0.01*CorrMap[KeyMap];//Converting into number from %
    if(Sdata != -1.0){//avoid division by zero
      //std::cout << "Sdata: " << Sdata << std::endl;
      return  ETtoE( pt, etaReco)/(1.0 + Sdata);
    }else{
      std::cout << "[INFO]-->Scale equal to -1, Avoiding division by zero, No correction applied" << std::endl;
      return ETtoE( pt, etaReco);
    }
  }
  
};


double zgamma::PhosphorCorrectionFunctor::GetCorrEnergy(float R9, int year, double pt, double etaReco){

  int dataType = Data;
  int corrType = Scale;
  int ptBin = -1;
  int detType = -1;
  int r9Cat = -1;
   
  if( year == 2011){
    year = XX_XI; 
  }else if( year == 2012){
    year = XX_XII;
  }else std::cout << "[INFO]--> Unknown YEAR, please check, inputs are 2011 or 2012 only" << std::endl;
  
  if( fabs(etaReco) < 1.5){
    detType = EB;
  }else{
    detType = EE;
  }
  
  if(pt > 10 && pt <= 12){
    ptBin = Pt0;
  }else if(pt > 12 && pt <= 15){
    ptBin = Pt1;
  }else if(pt > 15 && pt <= 20){
    ptBin = Pt2;
  }else if(pt > 20 && pt <= 999){
    ptBin = Pt3;
  }
  
  if ( R9 > 0.94 ){
    r9Cat = 1;//
  }else if ( R9 <= 0.94 && R9 > -10. ){
    r9Cat = 2;//Low R9
  }else if ( R9 == -666 ){
    r9Cat = 0;//Inclusive Category
  }

  // std::cout << "debug2: " << year << " " << dataType  << " " << detType  << " " << corrType << " " << ptBin <<  std::endl;
  string KeyMap =  CreateMapKey( year, dataType, detType, r9Cat, corrType, ptBin);
  //std::cout << "debug2: " << KeyMap << std::endl;
  
  if( CorrMap.find(KeyMap) == CorrMap.end() ){
    std::cout << "[INFO]-->Scale Data Not found, No correction applied. PT:  " << pt <<std::endl;
    return ETtoE( pt, etaReco);
  }else{
    double Sdata = 0.01*CorrMap[KeyMap];//Converting into number from %
    if(Sdata != -1.0){//avoid division by zero
      //std::cout << "Sdata: " << Sdata << std::endl;
      return  ETtoE( pt, etaReco)/(1.0 + Sdata);
    }else{
      std::cout << "[INFO]-->Scale equal to -1, Avoiding division by zero, No correction applied" << std::endl;
      return ETtoE( pt, etaReco);
    }
  }
  
};



double zgamma::PhosphorCorrectionFunctor::GetCorrEnergy(int year, double pt, double etaReco, int datType){

  int dataType = datType;
  int corrType = Scale;
  int ptBin = -1;
  int detType = -1;
  
  if( year == 2011){
    year = XX_XI; 
  }else if( year == 2012){
    year = XX_XII;
  }else std::cout << "[INFO]--> Unknown YEAR, please check, inputs are 2011 or 2012 only" << std::endl;
  
  if( fabs(etaReco) < 1.5){
    detType = EB;
  }else{
    detType = EE;
  }
  
  if(pt > 10 && pt <= 12){
    ptBin = Pt0;
  }else if(pt > 12 && pt <= 15){
    ptBin = Pt1;
  }else if(pt > 15 && pt <= 20){
    ptBin = Pt2;
  }else if(pt > 20 && pt <= 999){
    ptBin = Pt3;
  }
  
  // std::cout << "debug2: " << year << " " << dataType  << " " << detType  << " " << corrType << " " << ptBin <<  std::endl;
  string KeyMap =  CreateMapKey( year, dataType, detType, corrType, ptBin);
  //std::cout << "debug2: " << KeyMap << std::endl;
  
  if( CorrMap.find(KeyMap) == CorrMap.end() ){
    std::cout << "[INFO]-->Scale Data Not found, No correction applied. PT:  " << pt << std::endl;
    return ETtoE( pt, etaReco);
  }else{
    double Sdata = 0.01*CorrMap[KeyMap];//Converting into number from %
    if(Sdata != -1.0){//avoid division by zero
      //std::cout << "Sdata: " << Sdata << std::endl;
      return  ETtoE( pt, etaReco)/(1.0 + Sdata);
    }else{
      std::cout << "[INFO]-->Scale equal to -1, Avoiding division by zero, No correction applied" << std::endl;
      return ETtoE( pt, etaReco);
    }
  }
  
};

double zgamma::PhosphorCorrectionFunctor::GetCorrEt(int year, double pt, double etaReco, double Egen){

  double E = GetCorrEnergy(year, pt, etaReco, Egen);
  
  return EtoET(E, etaReco);
  
};

double zgamma::PhosphorCorrectionFunctor::GetCorrEt(float R9, int year, double pt, double etaReco, double Egen){

  double E = GetCorrEnergy(R9, year, pt, etaReco, Egen);
  
  return EtoET(E, etaReco);
  
};



double zgamma::PhosphorCorrectionFunctor::GetCorrEt(int year, double pt, double etaReco){

  double E = GetCorrEnergy(year, pt, etaReco);
  
  return EtoET(E, etaReco);
  
};


double zgamma::PhosphorCorrectionFunctor::GetCorrEt(float R9, int year, double pt, double etaReco){

  double E = GetCorrEnergy(R9, year, pt, etaReco);
  
  return EtoET(E, etaReco);
  
};




double zgamma::PhosphorCorrectionFunctor::GetCorrEt(int year, double pt, double etaReco, int datType){

  double E = GetCorrEnergy(year, pt, etaReco, datType);
  
  return EtoET(E, etaReco);
  
};
