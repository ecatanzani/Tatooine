#include "MyHeader.h"

void write_floatFinal_maps(
                            const std::string outMap,
                            const std::string outIsoMap,
                            const std::string outDiffMap,
                            const std::vector<ULong64_t> &pixelDataMap,
                            const std::vector<Double_t> &pixelIsoMap,                                
                            const std::vector<Double_t> &pixelDiffMap,
                            const Int_t nside
                        )
{

    //Creating float final arrays for the pixels
    float fpixelDataMap[pixelDataMap.size()];
    float fpixelIsoMap[pixelIsoMap.size()];
    float fpixelDiffMap[pixelDiffMap.size()];

    //Filling float pixel arrays
    for(ULong64_t idx=0; idx<pixelDataMap.size(); ++idx)
    {
        fpixelDataMap[idx] = (float)pixelDataMap[idx];
        fpixelIsoMap[idx] = (float)pixelIsoMap[idx];
        fpixelDiffMap[idx] = (float)pixelDiffMap[idx];
    }

    //Writing down final maps to file
    write_healpix_map(fpixelDataMap,nside,outMap.c_str(),0,"G");
    write_healpix_map(fpixelIsoMap,nside,outIsoMap.c_str(),0,"G");
    write_healpix_map(fpixelDiffMap,nside,outDiffMap.c_str(),0,"G");

}

void write_ubinary_map(
                        const std::vector<ULong64_t> &pixelMap,
                        const std::string outPath,
                        const long npix
                    )
{
    //Open the binary output file
    std::ofstream OutFile;
    OutFile.open(outPath.c_str(),std::ios::binary);
    OutFile.write((const char *)&pixelMap[0],(sizeof(pixelMap[0]))*npix);
    OutFile.close();
}

void write_dbinary_map(
                        const std::vector<Double_t> &pixelMap,
                        const std::string outPath,
                        const long npix
                    )
{
    //Open the binary output file
    std::ofstream OutFile;
    OutFile.open(outPath.c_str(),std::ios::binary);
    OutFile.write((const char *)&pixelMap[0],(sizeof(pixelMap[0]))*npix);
    OutFile.close();
}