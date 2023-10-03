#pragma once 
#include "Job.h"
#include "ParseJob.h"

//#include "rapidjson/document.h"
#include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/document.h"
// #include "rapidjson/writer.h"
#include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/writer.h"
// #include "rapidjson/stringbuffer.h"
#include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/stringbuffer.h"

class JSONJob : public Job
{
    JSONJob(unsigned long jobChannel = 0xFFFFFFFF, int jobType = -1) : Job(jobChannel, jobType) {}; 
    ~JSONJob(){}; 
    void execute() override; 

    std::string filePath; 
    std::vector<Error> errors; 

}; 