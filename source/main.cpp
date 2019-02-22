#include "MyHeader.h"

int main(int argc,char* argv[])
{
    std::string inPath(argv[1]);
    std::string outMap,outIsoMap,outDiffMap;
    std::string outBinMap,outBinIsoMap,outBinDiffMap;
    TTree* dTree = nullptr;

    std::vector<ULong64_t> pixelDataMap;    //Stores the pixel content (how many times a pixel has been triggered) of the data map
    std::vector<Double_t> pixelIsoMap;     //Stores the pixel content (how many times a pixel has been triggered) of the isotropic data map - obtained through the shuffing technique
    std::vector<Double_t> pixelDiffMap;    //Stores the pixel content (how many times a pixel has been triggered) of the differentiate map

    Int_t nside = 0;                //Healpix nside paramter for the maps       
    bool kRawFilter = true;         //Boolean variable to cut on the particle energy
    bool kVerbose = false;          //Parameter to set the software verbosity
    Int_t shufflePasses = 100;      //Stores the numbe rof times the shuffling procedure should be executed on the real data map
    ULong64_t SEED = 22;            //Stores the seed used in the shuffling technique
    Double_t eLowThreshold = 0;     //Stores the energy low threshold for events cut
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
                    eLowThreshold,
                    SEED
                );

    npix = nside2npix(nside);       //Define the number of pixels into the maps

    //Building final output paths
    outMap = getMapAddress(inPath);
    outIsoMap = getMapAddress(inPath,true);
    outDiffMap = getMapAddress(inPath,false,true);

    outBinMap = getMapAddress(
                                inPath,
                                false,
                                false,
                                true
                            );

    outBinIsoMap = getMapAddress(
                                    inPath,
                                    true,
                                    false,
                                    true
                                );

    outBinDiffMap = getMapAddress(
                                    inPath,
                                    false,
                                    true,
                                    true
                                );


    //Input parameters printout
    if(kVerbose)
    {
        std::cout << "\n****************\n";
        std::cout << "Analysis parameters: \n\n";

        std::cout << "nside: \t" << nside << std::endl;
        std::cout << "npixels: " << npix << std::endl;
        std::cout << "kRawFilter \t" << kRawFilter << std::endl;
        std::cout << "kVerbose \t" << kVerbose << std::endl;
        std::cout << "shufflePasses \t" << shufflePasses << std::endl;
        std::cout << "eLowThreshold \t" << eLowThreshold << std::endl;
        std::cout << "shuffleSeed \t" << SEED << std::endl;

        std::cout << "\n****************\n";
    }

    //Resize maps pixel counters vectors
    pixelDataMap.resize(npix);
    pixelIsoMap.resize(npix);
    pixelDiffMap.resize(npix);

    //Creating the data collection object
    if(kVerbose)
        std::cout << "\n\033[1;36mCreating data collection object...\033[0m";
    rawData dCollect;

    //Extracting the data TTree from the input file
    if(kVerbose)
        std::cout << "\n\033[1;36mExtracting data from TTree input file...\033[0m";
    inFile.GetObject("dataTree",dTree);

    //Linking the data TTree with the data pool variables
    if(kVerbose)
        std::cout << "\n\033[1;36mLinking TTree entries with local variables...\033[0m";
    dCollect.link_tree(dTree);

    //Initializing the healpix maps
    if(kVerbose)
        std::cout << "\n\n\033[1;31mInitializing maps...\033[0m";
    initialize_maps(pixelDataMap,pixelIsoMap,npix);

    //Build the data map
    if(kVerbose)
        std::cout << "\n\033[1;31mBuilding data map...\033[0m";
    build_data_map(pixelDataMap,dTree,dCollect,filteredEv,kVerbose,kRawFilter,nside,eLowThreshold);

    //Shuffle the data map
    if(kVerbose)
        std::cout << "\n\033[1;31mShuffling data map...\033[0m\n\n\t --> Pass (of " << shufflePasses <<"): ";
    for(int sIdx=0; sIdx<shufflePasses; ++sIdx)
    {
        if(kVerbose)
            std::cout << sIdx << "  ";
        shuffle_data_map(pixelIsoMap,pixelDataMap,dTree,dCollect,filteredEv,SEED,eLowThreshold);
    }
    
    //Get mean isotropic map
    if(kVerbose)
        std::cout << "\n\n\033[1;31mBuilding isotropic map...\033[0m";
    get_mean_iso_map(pixelIsoMap,shufflePasses);

    //Get the differentiate map
    if(kVerbose)
        std::cout << "\n\033[1;31mBuilding differential map...\033[0m";
    get_diff_map(pixelDataMap,pixelIsoMap,pixelDiffMap);

    //Writing down the final maps
    if(kVerbose)
        std::cout << "\n\n\033[1;36mWriting final results...\033[0m\n";
    write_floatFinal_maps(
                            outMap,
                            outIsoMap,
                            outDiffMap,
                            pixelDataMap,
                            pixelIsoMap,
                            pixelDiffMap,
                            nside
                        );

    write_ubinary_map(
                        pixelDataMap,
                        outBinMap,
                        npix
                    );

    write_dbinary_map(
                        pixelIsoMap,
                        outBinIsoMap,
                        npix
                    );
    
    write_dbinary_map(
                        pixelDiffMap,
                        outBinDiffMap,
                        npix
                    );

    return 0;
}