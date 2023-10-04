#include <iostream> 
#include <sstream> 
#include "ParseJob.h"
#include <string> 

std::string ParseJob::showUnparsed()
{
    std::cout << "Unparsed Compile Job Results: " << unparsedText << std::endl; 
    return unparsedText; 
}
void ParseJob::execute()
{
    std::regex errorPattern("(.*):(\\d+):(\\d+): (error:|warning:)+(.*)"); 
 
    std::istringstream errorStream(this->unparsedText); 
    bool reading = true; 
    std::string lineIn; 


    while(getline(errorStream, lineIn))
    {
        std::smatch matcher; 
        if(std::regex_match(lineIn, matcher, errorPattern))
        {
        
            std::string filePath = matcher[1]; 
            std::string lineNum_str = matcher[2]; 
            int line_int = std::stoi(lineNum_str); 
            std::string colNum_str = matcher[3]; 
            int col_int = std::stoi(colNum_str); 
            std::string msg = matcher[4]; 
            msg.append(matcher[5]); 
            
            Error e; 
            e.file = filePath; 
            e.lineNum = line_int;  
            e.colNum = col_int; 
            e.errorMessage = msg; 

            getline(errorStream, lineIn); 
            e.src = lineIn; 

            auto error_itr = this->errorMap.find(e.file); 
            if(error_itr == this->errorMap.end())
            {
                std::vector<Error> errors; 
                this->errorMap.insert({e.file,errors}); 
            }
            error_itr = this->errorMap.find(e.file); 
            error_itr->second.push_back(e); 

        }
    }

}
void ParseJob::jobCompleteCallback()
{
    std::cout << "Job " << this->getUniqueID() << std::endl;
    int numFiles = jobErrors.size(); 
    std::cout << "\tNum File Entries: " << numFiles << std::endl; 

    for(auto itr = jobErrors.begin(); itr != jobErrors.end(); ++itr)
    {
        std::cout << "\t\tFile: " << itr->first << "\n\t\t\tNumErrors: " << itr->second.size() << std::endl; 
    }
  
}
