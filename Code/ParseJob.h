#pragma once
#include "Job.h"
#include <unordered_map>
#include <fstream> 
#include <regex> 
struct Error
{
    std::string file; 
    std::string errorMessage; 
    int lineNum;
    int colNum;//
};
class ParseJob : public Job 
{
    public: 
        //ParseJob(std::string unparsedText);  
        ParseJob(unsigned long jobChannel = 0xFFFFFFFF, int jobType = -1) : Job(jobChannel, jobType) {}; 
        ~ParseJob(){}; 
        void execute() override; 
        std::string showUnparsed();

    
        std::unordered_map<std::string, std::vector<Error>> jobErrors; 
        std::string unparsedText; 
        int jobId; 
    private: 
        

};