#include <iostream> 
#include <sstream> 
#include "ParseJob.h"

// ParseJob::ParseJob( std::string messageIn)
// {
//     std::cout << "ParseJob Created" << std::endl;  
//     this->unparsedText = messageIn;
// }

void ParseJob::execute()
{
    std::istringstream errorStream(this->unparsedText); 
    char delim = ':';
    std::string lineIn;
    std::regex errorPattern("error: (.+) in (.+) at line (\\d+), column (\\d+)");
    std::regex warningPattern("warning: (.+) in (.+) at line (\\d+), column (\\d+)");

    bool reading = true; 

    // rapidjson::Document doc; 
    // doc.SetArray(); 
    while(reading)
    {
        Error e;
        std::getline(errorStream, e.file, delim); 
        std::string lineNumStr; 
        std::getline(errorStream, lineNumStr, delim); 
        e.lineNum = std::stoi(lineNumStr); 
        std::string colNumStr; 
        std::getline(errorStream, colNumStr, delim); 
        e.colNum = std::stoi(colNumStr); 
        std::getline(errorStream, e.errorMessage); 


        // std::smatch match; 

        // if(std::regex_search(lineIn, match, errorPattern) || std::regex_search(lineIn, match, warningPattern))
        // {
        //     rapidjson::Value errorJson(rapidjson::kObjectType);
        //     Error e; 

        // }

        auto error_itr = this->jobErrors.find(e.file);
        if(error_itr == this->jobErrors.end())
        {
            this->jobErrors.insert({e.file,{}}); 
        }
        error_itr->second.push_back(e); \
        reading = false; 
    }
}
