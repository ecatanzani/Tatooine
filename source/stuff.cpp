#include "MyHeader.h"

bool checkIfUsed(ULong64_t tmpElement,std::vector<ULong64_t> &elements)
{   
    bool status=false;
    
    //Raw search function... substitute with a better one
    for(ULong64_t idx=0; idx<elements.size(); ++idx)
        if(elements[idx]==tmpElement)
        {
            status=true;
            break;
        }

    return status; 
}

bool stringToBool(std::string tmp_str)
{
    bool kStat = true;
    if(tmp_str=="false")
        kStat = false;

    return kStat;
}