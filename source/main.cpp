#include "MyHeader.h"

int main(int argc,char* argv[])
{
    std::string inPath(argv[1]);
    std::string outMap,outIsoMap,outDiffMap;
    TTree* dTree = nullptr;
    long npix = nside2npix(nside);     //The number of pixels stored into the maps

    std::vector<ULong64_t> pixelDataMap;    //Stores the pixel content (how many times a pixel has been triggered) of the data map
    std::vector<ULong64_t> pixelIsoMap;     //Stores the pixel content (how many times a pixel has been triggered) of the isotropic data map - obtained through the shuffing technique
    std::vector<ULong64_t> pixelDiffMap;    //Stores the pixel content (how many times a pixel has been triggered) of the differentiate map

    pixelDataMap.resize(npix);
    pixelIsoMap.resize(npix);
    pixelDiffMap.resize(npix);

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
    
    //Creating the data collection object
    rawData dCollect;

    //Extracting the data TTree from the input file
    inFile.GetObject("dataTree",dTree);

    //Linking the data TTree with the data pool variables
    dCollect.link_tree(dTree);

    //Initializing the healpix maps
    initialize_maps(pixelDataMap,pixelIsoMap,npix);

    //Build the data map
    build_data_map(pixelDataMap,dTree,dCollect);





    //Writing down the final maps...

    outMap = getMapAddress(inPath);
    outIsoMap = getMapAddress(inPath,true);
    outDiffMap = getMapAddress(inPath,false,true);

    return 0;
}