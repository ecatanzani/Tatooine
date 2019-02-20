#include "MyHeader.h"

int main(int argc,char* argv[])
{
    std::string inPath(argv[1]);
    std::string outMap,outIsoMap,outDiffMap;
    TTree* dTree = nullptr;

    std::vector<ULong64_t> pixelDataMap;    //Stores the pixel content (how many times a pixel has been triggered) of the data map
    std::vector<Double_t> pixelIsoMap;     //Stores the pixel content (how many times a pixel has been triggered) of the isotropic data map - obtained through the shuffing technique
    std::vector<Double_t> pixelDiffMap;    //Stores the pixel content (how many times a pixel has been triggered) of the differentiate map

    Int_t nside = 0;                //Healpix nside paramter for the maps       
    bool kRawFilter = true;         //Boolean variable to cut on the particle energy
    bool kVerbose = false;          //Parameter to set the software verbosity
    Int_t shufflePasses = 100;      //Stores the numbe rof times the shuffling procedure should be executed on the real data map
    ULong64_t SEED = 22;            //Stores the seed used in the shuffling technique
    long npix = 0;                  //The number of pixels stored into the maps
    ULong64_t filteredEv = 0;       //Counter for the events above a certain energy threshold

    //////// Here comes the main

    if(argc<2)
    {
        std::cerr << "\n\nUsage: ./Tatooine path_to_input_ROOT_file\n\n";
        exit(-3);
    }   
    TFile inFile(inPath.c_str(),"READ");
    
    if(inFile.IsZombie())
    {
        std::cerr << "\n\nERRROR reading the input path: " << inPath;
        exit(100);
    }
    
    getParameters(
                    nside,
                    kRawFilter,
                    kVerbose,
                    shufflePasses,
                    SEED
                );

    npix = nside2npix(nside);       //Define the number of pixels into the maps

    //Resize maps pixel counters vectors
    pixelDataMap.resize(npix);
    pixelIsoMap.resize(npix);
    pixelDiffMap.resize(npix);

    //Creating the data collection object
    rawData dCollect;

    //Extracting the data TTree from the input file
    inFile.GetObject("dataTree",dTree);

    //Linking the data TTree with the data pool variables
    dCollect.link_tree(dTree);

    //Initializing the healpix maps
    initialize_maps(pixelDataMap,pixelIsoMap,npix);

    //Build the data map
    build_data_map(pixelDataMap,dTree,dCollect,filteredEv,kVerbose,kRawFilter,nside);

    //Shuffle the data map
    for(int sIdx=0; sIdx<shufflePasses; ++sIdx)
        shuffle_data_map(pixelIsoMap,pixelDataMap,dTree,dCollect,filteredEv,SEED);

    //Get mean isotropic map
    get_mean_iso_map(pixelIsoMap,shufflePasses);

    //Get the differentiate map
    get_diff_map(pixelDataMap,pixelIsoMap,pixelDiffMap);

    //Writing down the final maps...
    outMap = getMapAddress(inPath);
    outIsoMap = getMapAddress(inPath,true);
    outDiffMap = getMapAddress(inPath,false,true);

    //write_healpix_map(&pixelDataMap[0],nside,outMap.c_str(),0,"G");
    //write_healpix_map(&(float)pixelIsoMap[0],nside,outIsoMap.c_str(),0,"G");
    //write_healpix_map(&(float)pixelDiffMap[0],nside,outDiffMap.c_str(),0,"G");

    return 0;
}