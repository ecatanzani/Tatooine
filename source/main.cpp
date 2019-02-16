#include "MyHeader.h"

int main(int argc,char* argv[])
{
    std::string inPath(argv[1]);
    std::string outMap,outIsoMap,outDiffMap;
    TTree* dTree = nullptr;

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











    //Writing down the final maps...h

    outMap = getMapAddress(inPath);
    outIsoMap = getMapAddress(inPath,true);
    outDiffMap = getMapAddress(inPath,false,true);

    return 0;
}