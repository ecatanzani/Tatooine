#include "MyHeader.h"

void getParameters(
                    Int_t &nside,
                    bool &kRawFilter,
                    bool &kVerbose,
                    Int_t &shufflePasses,
                    ULong64_t &SEED
                )
{

    char* conFile = (char*)"dataAnalysis.conf";
    std::ifstream input_file(conFile);
    if(!input_file.is_open()) {
        std::cerr << "\nERROR 100! File not open. The path is 'dataAnalysis.conf' \n\n";
        exit(100);
    }
    std::string input_string((std::istreambuf_iterator< char >(input_file)), (std::istreambuf_iterator< char >()));
    std::string tmp_str;
    input_file.close();
    std::istringstream input_stream(input_string);
    while(input_stream>>tmp_str)
    {
        if(tmp_str == "nside")
        {
            input_stream>>tmp_str;
            nside = strtoul(tmp_str.c_str(),NULL,10);
        }
        if(tmp_str == "kRawFilter")
        {
            input_stream>>tmp_str;
            kRawFilter = stringToBool(tmp_str); 
        }
        if(tmp_str == "kVerbose")
        {
            input_stream>>tmp_str;
            kVerbose = stringToBool(tmp_str); 
        }
        if(tmp_str == "shufflePass")
        {
            input_stream>>tmp_str;
            shufflePasses = stoi(tmp_str,NULL,10);
        }
        if(tmp_str == "shuffleSeed")
        {
            input_stream>>tmp_str;
            SEED = stoul(tmp_str,NULL,10);
        }
    }

    //// Debug printout

    #if 0

        std::cout << "\n****************\n";
        std::cout << "Analysis parameters: \n\n";

        std::cout << "nside: \t" << nside << std::endl;
        std::cout << "kRawFilter \t" << kRawFilter << std::endl;
        std::cout << "kVerbose \t" << kVerbose << std::endl;
        std::cout << "shufflePasses \t" << shufflePasses << std::endl;
        std::cout << "shuffleSeed \t" << SEED << std::endl;

        std::cout << "\n****************\n";

    #endif
}