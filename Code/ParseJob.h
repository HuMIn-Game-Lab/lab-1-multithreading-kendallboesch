#pragma once
#include "Job.h"
#include <unordered_map>
#include <fstream> 
#include <regex> 

class ParseJob : public Job 
{
    public: 
        //ParseJob(std::string unparsedText);  
        ParseJob(unsigned long jobChannel = 0xFFFFFFFF, int jobType = 2) : Job(jobChannel, jobType) {}; 
        ~ParseJob(){}; 
        void execute() override; 
        std::string showUnparsed();
        void jobCompleteCallback() override; 

    
        std::unordered_map<std::string, std::vector<Error>> jobErrors; 
        std::string unparsedText; 
        int jobId; 
    private: 
        

};