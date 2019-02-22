#include "MyHeader.h"

void initialize_maps(std::vector<ULong64_t> &pixelDataMap,std::vector<Double_t> &pixelIsoMap,long nPixels)
{
    for(Int_t p_idx=0; p_idx<nPixels; ++p_idx)
    {
        pixelDataMap[p_idx] = 0;
        pixelIsoMap[p_idx] = 0;
    }
}

void build_data_map(
                        std::vector<ULong64_t> &pixelDataMap,
                        TTree* dTree,rawData &dCollect,
                        ULong64_t &filteredEv,
                        const bool kVerbose,
                        const bool kRawFilter,
                        const Int_t nside,
                        const Double_t eLowThreshold
                    )
{
    ULong64_t evNum = dTree->GetEntries();
    
    for(ULong64_t evIdx=0; evIdx<evNum; ++evIdx)
    {
        dCollect.set_data_entry(dTree,evIdx);
        if(dCollect.maps_filler(pixelDataMap,kRawFilter,nside,eLowThreshold))
            ++filteredEv;
    }

    if(kVerbose)
        std::cout << "\t [Processed " << filteredEv << " events on " << evNum << "]";
}

void shuffle_data_map(
                        std::vector<Double_t> &pixelIsoMap,
                        std::vector<ULong64_t> &pixelDataMap,
                        TTree* dTree,
                        rawData &dCollect,
                        const ULong64_t filteredEv,
                        const UInt_t SEED,
                        const Double_t eLowThreshold
                    )
{
    ULong64_t evNum = dTree->GetEntries();
    std::vector<ULong64_t> linkedEv;
    linkedEv.resize(filteredEv);
    TRandom3 r_gen(SEED);
    ULong64_t tmpLink=0;
    
    for(ULong64_t evIdx=0; evIdx<evNum; ++evIdx)
    {
        dCollect.set_data_entry(dTree,evIdx);
        if(dCollect.eventEnergyCut(eLowThreshold))
        {   
            do
            //for(int i=0; i<100; ++i)
            {
                tmpLink = (ULong64_t)r_gen.Uniform(0,filteredEv);
                if(!evIdx)
                    break;
            }
            while(checkIfUsed(tmpLink,linkedEv));
            linkedEv[evIdx] = tmpLink;
            pixelIsoMap[evIdx] = pixelDataMap[linkedEv[evIdx]];       
        }
    }    
}

void get_mean_iso_map(std::vector<Double_t> &pixelIsoMap,const Int_t shufflePasses)
{
    for(ULong64_t idx=0; idx<pixelIsoMap.size(); ++idx)
        pixelIsoMap[idx] /= shufflePasses;
}

void get_diff_map(std::vector<ULong64_t> &pixelDataMap,std::vector<Double_t> &pixelIsoMap,std::vector<Double_t> &pixelDiffMap)
{
    for(ULong64_t idx=0; idx<pixelIsoMap.size(); ++idx)
        pixelDiffMap[idx] = pixelDataMap[idx]/(Double_t)pixelIsoMap[idx] -1;
}

//Module Transforming Orbital Coord into Galactic Coord based on Coord Rotation
TVector3 Orb2Equ_RM(const TVector3& r_sat, const TVector3& v_sat, const TVector3& r_Track)
{
    //The Direction of Incident Particle is the Inverse of the Direction of the Track Reconstructed
    TVector3 r_Particle = -r_Track;
    
    //Calculate the Matrix for Coordinate Transformation Using Satellite Position and Velocity
    TMatrixD T(3,3);
    
    TVector3 Z_sat = -r_sat.Unit(); //Z_sat is in the Direction of the Inverse Satellite Position
    TVector3 Y_sat =  v_sat.Cross(r_sat).Unit(); //Y_sat is in the Direction of the Inverse Normal of the Orbit Plane
    TVector3 X_sat =  Y_sat.Cross(Z_sat).Unit(); //X = Y Cross Z
    
    
    //The Row Vectors of the Rotation Matrix are X_sat, Y_sat, and Z_sat
    T(0,0) = X_sat.X();
    T(1,0) = X_sat.Y();
    T(2,0) = X_sat.Z();
    
    T(0,1) = Y_sat.X();
    T(1,1) = Y_sat.Y();
    T(2,1) = Y_sat.Z();
    
    T(0,2) = Z_sat.X();
    T(1,2) = Z_sat.Y();
    T(2,2) = Z_sat.Z();
    
    //Transform from Orbit Coord to Equatorial Coord by Applying the Rotation Matrix
    return T * r_Particle;
}

//Module Transforming Equatorial Coord into Galactic Coord based on Coord Rotation
TVector3 Equ2Gal(const TVector3& fk5)
{
    TMatrixD T(3,3);
    
    T(0,0) = -0.054875539726; T(0,1) = -0.873437108010; T(0,2) = -0.483834985808;
    T(1,0) =  0.494109453312; T(1,1) = -0.444829589425; T(1,2) =  0.746982251810;
    T(2,0) = -0.867666135858; T(2,1) = -0.198076386122; T(2,2) =  0.455983795705;
    
    return T * fk5;
}