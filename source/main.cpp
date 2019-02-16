#include "MyHeader.h"

int main(int argc,char* argv[])
{
    std::string inPath(argv[1]);
    std::string outMap,outIsoMap,outDiffMap;

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

    outMap = getMapAddress(inPath);
    outIsoMap = getMapAddress(inPath,true);
    outDiffMap = getMapAddress(inPath,false,true);

    return 0;
}