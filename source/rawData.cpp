#include "MyHeader.h"
#include "rawData.h"

rawData::rawData()
{
    evTime = 0;
    bgoEnergy = -999;
    recEnergy = -999;
    thetaTrack = -999;
    phiTrack = -999;
    pX = -999;
    pY = -999;
    pZ = -999;
    vX = -999;
    vY = -999;
    vZ = -999;
}

rawData::rawData(
                    ULong64_t time,
                    Double_t BGOe,
                    Double_t RECe,
                    Double_t tTrack,
                    Double_t pTrack,
                    Double_t rX,
                    Double_t rY,
                    Double_t rZ,
                    Double_t spdX,
                    Double_t spdY,
                    Double_t spdZ          
                )
{
    evTime = time;
    bgoEnergy = BGOe;
    recEnergy = RECe;
    thetaTrack = tTrack;
    phiTrack = pTrack;
    pX = rX;
    pY = rY;
    pY = rZ;
    vX = spdX;
    vY = spdY;
    vZ = spdZ;
}

void rawData::set_data_entry(TTree* tree,ULong64_t evIdx) { tree->GetEntry(evIdx); }

bool rawData::maps_filler(std::vector<ULong64_t> &pixelVector,const bool kRawFilter,const Int_t nside)
{   
    bool fStatus=false;
    if(kRawFilter)
    {
        if(eventEnergyCut())
        {
            TVector3 StkDirection;
            TVector3 SatPosition;
            TVector3 SatVelocity;
            TVector3 eDir;
            long pixIdx;

            StkDirection.SetMagThetaPhi(1.,thetaTrack*D2R,phiTrack*D2R);
            SatPosition.SetXYZ(pX,pY,pY);
            SatVelocity.SetXYZ(vX,vY,vY);
            eDir=Orb2Equ_RM(SatPosition,SatVelocity,StkDirection);
            ang2pix_ring(nside,eDir.Theta(),eDir.Phi(),&pixIdx);
            ++pixelVector[(ULong64_t)pixIdx];
        }
        fStatus=true;
    }
    return fStatus;
}

bool rawData::eventEnergyCut(Double_t eCut)
{
    bool ECut=false;

    if(recEnergy>eCut)
        ECut=true;
    
    return ECut;
}

void rawData::getDataEvent()
{
    std::cout << "\n****************\n";
    std::cout << "Data event sumup: \n\n";
    
    std::cout << "EventTime: \t" << evTime << std::endl;
    std::cout << "BGO Energy (GeV)\t" << bgoEnergy << std::endl;
    std::cout << "REC Energy (GeV) \t" << recEnergy << std::endl;
    std::cout << "STK theta \t" << thetaTrack << std::endl;
    std::cout << "STK phi \t" << phiTrack << std::endl;
    std::cout << "Satellite Position X (GeoCenter coord.) \t" << pX << std::endl;
    std::cout << "Satellite Position Y (GeoCenter coord.) \t" << pY << std::endl;
    std::cout << "Satellite Position Z (GeoCenter coord.) \t" << pZ << std::endl;
    std::cout << "Satellite Velocity X (GeoCenter coord.) \t" << vX << std::endl;
    std::cout << "Satellite Velocity Y (GeoCenter coord.) \t" << vY << std::endl;
    std::cout << "Satellite Velocity Z (GeoCenter coord.) \t" << vZ << std::endl;

    std::cout << "\n****************\n";
}

void rawData::link_tree(TTree* tree)
{
    tree->SetBranchAddress("DAMPE_timestamp",&evTime);
    tree->SetBranchAddress("BGO_energy",&bgoEnergy);
    tree->SetBranchAddress("REC_energy",&recEnergy);
    tree->SetBranchAddress("STK_theta",&thetaTrack);
    tree->SetBranchAddress("STK_phi",&phiTrack);

    tree->SetBranchAddress("SatGeo_P_X",&pX);
    tree->SetBranchAddress("SatGeo_P_Y",&pY);
    tree->SetBranchAddress("SatGeo_P_Z",&pZ);

    tree->SetBranchAddress("SatGeo_V_X",&vX);
    tree->SetBranchAddress("SatGeo_V_Y",&vY);
    tree->SetBranchAddress("SatGeo_V_Z",&vZ);
}