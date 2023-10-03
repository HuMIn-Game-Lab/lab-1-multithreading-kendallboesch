#pragma once 
#include "Job.h"
#include "ParseJob.h"



class JSONJob : public Job
{
    JSONJob(unsigned long jobChannel = 0xFFFFFFFF, int jobType = -1) : Job(jobChannel, jobType) {}; 
    ~JSONJob(){}; 
    void execute() override; 

    std::string filePath; 
    std::vector<Error> errors; 

}; 