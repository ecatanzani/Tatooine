#include "MyHeader.h"

std::string getMapAddress(std::string input_path,bool isomap,bool diffmap)
{
    std::string outpath;
    std::string tmpName,tmpRoot;
    
    std::size_t sPosition = input_path.find_last_of("/\\");    
    std::size_t fPosition = input_path.find_last_of(".");
    tmpName = input_path.substr(sPosition+1,fPosition-1);
    tmpRoot = input_path.substr(0,sPosition-1);
    if(isomap)
        tmpName = tmpName.append("_isoMap.fits");
    else if(diffmap)
        tmpName = tmpName.append("_diffMap.fits");
    else
        tmpName = tmpName.append(".fits");

    return outpath = tmpRoot+tmpName;
}