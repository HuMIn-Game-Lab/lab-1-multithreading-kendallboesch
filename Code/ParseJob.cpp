#include <iostream> 
#include <sstream> 
#include "ParseJob.h"

ParseJob::ParseJob(int id, std::string messageIn)
{
    this->jobId = id; 
    this->unparsedText = messageIn;
}

void ParseJob::execute()
{
    std::istringstream errorStream(this->unparsedText); 
    std::string lineIn;
    std::regex errorPattern("error: (.+) in (.+) at line (\\d+), column (\\d+)");
    std::regex warningPattern("warning: (.+) in (.+) at line (\\d+), column (\\d+)");

    bool reading = true; 

    while(reading)
    {
        std::getline(errorStream, lineIn); 
        std::smatch match; 

        if(std::regex_search(lineIn, match, errorPattern) || std::regex_search(lineIn, match, warningPattern))
        {
            Error e; 
            e.errorMessage = match[1]; 
            e.file = match[2];
            e.lineNum = std::stoi(match[3]); 
            e.colNum = std::stoi(match[4]); 
        }
    }
}
