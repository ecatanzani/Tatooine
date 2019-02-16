#ifndef MYHEADER_H
#define MYHEADER_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <string>

//HealPiX includes
#include "healpix_base.h"

//ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include "TRandom3.h"

//Class headers
#include "rawData.h"

//Functions

extern std::string getMapAddress(std::string input_path,bool isomap=false,bool diffmap=false);

#endif