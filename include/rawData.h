#ifndef RAWDATA_H
#define RAWDATA_H

#include "MyHeader.h"

class rawData
{

    public:

        rawData();
    
        rawData(
                    ULong64_t evTime,
                    Double_t bgoEnergy,
                    Double_t recEnergy,
                    Double_t thetaTrack,
                    Double_t phiTrack,
                    Double_t pX,
                    Double_t pY,
                    Double_t pZ,
                    Double_t vX,
                    Double_t vY,
                    Double_t vZ          
                );

        void set_data_entry(
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
                            );

        void getDataEvent();

        void link_tree(TTree* tree);

        ~rawData() {};

    private:

        /////// Event variables ...

        ULong64_t evTime;
        Double_t bgoEnergy;
        Double_t recEnergy;
        Double_t thetaTrack;
        Double_t phiTrack;
        Double_t pX,pY,pZ;
        Double_t vX,vY,vZ;

};


#endif