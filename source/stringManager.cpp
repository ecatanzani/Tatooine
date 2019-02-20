#include "MyHeader.h"

std::string getMapAddress(std::string input_path,bool isomap,bool diffmap,bool binary)
{
    std::string outpath;
    std::string tmpName,tmpRoot;
    
    std::size_t sPosition = input_path.find_last_of("/\\");    
    std::size_t fPosition = input_path.find(".");

    tmpName = input_path.substr(sPosition+1,fPosition-sPosition-1);
    tmpRoot = input_path.substr(0,sPosition);

    if(isomap)
        if(binary)
           tmpName = tmpName.append("_isoMap.dat");
        else 
            tmpName = tmpName.append("_isoMap.fits");
    else if(diffmap)
        if(binary)
            tmpName = tmpName.append("_diffMap.dat");
        else
            tmpName = tmpName.append("_diffMap.fits");
    else
        if(binary)
            tmpName = tmpName.append(".dat");
        else    
            tmpName = tmpName.append(".fits");

    return outpath = tmpRoot + "/" + tmpName;
}