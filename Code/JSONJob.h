
#include "Job.h"
#include "ParseJob.h"
#include <unordered_map>
#include "rapidjson/document.h"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/document.h"
#include "rapidjson/writer.h"

//#include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/include"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
// #include "/Users/kendallboesch/Desktop/CS3341-FoundationsOfModernComputing/Lab-1/lab-1-multithreading-kendallboesch/Code/rapidjson-master/include/rapidjson/stringbuffer.h"

class JSONJob : public Job
{
    public:
    JSONJob(unsigned long jobChannel = 0xFFFFFFFF, int jobType = 3) : Job(jobChannel, jobType) {}; 
    ~JSONJob(){}; 
    void execute() override; 

    std::string filePath; 
    std::vector<Error> errors; 
    std::map<std::string, std::vector<Error>> errorMap; 

}; 