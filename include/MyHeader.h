#ifndef MYHEADER_H
#define MYHEADER_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <string>

//Healpix includes
#include "healpix_base.h"
#include "chealpix.h"

//ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include "TMatrixD.h"
#include "TRandom3.h"

//Class headers
#include "rawData.h"

//Healpix maps characteristics
#define nside 64

//Analysis parameters
#define kRawFilter true     //Boolean value to filter raw data
#define kVerbose true       //Software verbosity
#define eLowThreshold 60    //Low energy threshold (expressed in GeV)
#define D2R 1.7453292519943295769e-2
#define R2D 5.7295779513082320877e+1

//Functions

extern std::string getMapAddress(std::string input_path,bool isomap=false,bool diffmap=false);
extern void initialize_maps(std::vector<ULong64_t> &pixelDataMap,std::vector<ULong64_t> &pixelIsoMap,long nPixels);
extern void build_data_map(std::vector<ULong64_t> &pixelDataMap,TTree* dTree,rawData &dCollect);
extern TVector3 Orb2Equ_RM(const TVector3& r_sat, const TVector3& v_sat, const TVector3& r_Track);

#endif