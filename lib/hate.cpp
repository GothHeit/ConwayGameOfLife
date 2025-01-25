#include "hate.h"


std::vector<std::string> hate::split(std::string input, std::string delimiters)
{
    std::vector<std::string> out{};
        std::string calma{};
        int size = input.size();
        for(int i=0; i<size; ++i){
        
            if(delimiters.find(input[i])==std::string::npos){
                calma+=input[i];        
            if(i==size-1) out.push_back(calma);
            }
            else{
                out.push_back(calma);
                calma.clear();
            }
        }
        

        return out;    
}


std::string hate::strtolower(std::string orig)
{
    int n = orig.size();
    for(int i=0; i<n; ++i){
        orig[i] = tolower(orig[i]);
    }
    return orig;
}