#ifndef MYHEADER_H
#define MYHEADER_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
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

#define D2R 1.7453292519943295769e-2
#define R2D 5.7295779513082320877e+1

//Functions

extern void getParameters(
                            Int_t &nside,
                            bool &kRawFilter,
                            bool &kVerbose,
                            Int_t &shufflePasses,
                            ULong64_t &SEED
                        );

extern std::string getMapAddress(
                                    std::string input_path,
                                    bool isomap=false,
                                    bool diffmap=false,
                                    bool binary=false
                                );

extern void initialize_maps(std::vector<ULong64_t> &pixelDataMap,std::vector<Double_t> &pixelIsoMap,long nPixels);

extern void build_data_map(
                            std::vector<ULong64_t> &pixelDataMap,
                            TTree* dTree,rawData &dCollect,
                            ULong64_t &filteredEv,
                            const bool kVerbose,
                            const bool kRawFilter,
                            const Int_t nside
                        );

extern void shuffle_data_map(
                                std::vector<Double_t> &pixelIsoMap,
                                std::vector<ULong64_t> &pixelDataMap,
                                TTree* dTree,
                                rawData &dCollect,
                                ULong64_t &filteredEv,
                                const UInt_t SEED
                            );

extern bool checkIfUsed(ULong64_t tmpElement,std::vector<ULong64_t> &elements);
extern void get_mean_iso_map(std::vector<Double_t> &pixelIsoMap,const Int_t shufflePasses);
extern void get_diff_map(std::vector<ULong64_t> &pixelDataMap,std::vector<Double_t> &pixelIsoMap,std::vector<Double_t> &pixelDiffMap);
extern TVector3 Orb2Equ_RM(const TVector3& r_sat, const TVector3& v_sat, const TVector3& r_Track);
extern bool stringToBool(std::string tmp_str);

extern void write_floatFinal_maps(
                                    const std::string outMap,
                                    const std::string outIsoMap,
                                    const std::string outDiffMap,
                                    const std::vector<ULong64_t> &pixelDataMap,
                                    const std::vector<Double_t> &pixelIsoMap,
                                    const std::vector<Double_t> &pixelDiffMap,
                                    const Int_t nside
                                );

extern void write_dbinary_map(
                                const std::vector<Double_t> &pixelMap,
                                const std::string outPath,
                                const long npix
                            );

extern void write_ubinary_map(
                                const std::vector<ULong64_t> &pixelMap,
                                const std::string outPath,
                                const long npix
                            );

#endif