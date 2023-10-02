#include "Job.h"

class CompileJob : public Job 
{
    public: 
        CompileJob(unsigned long jobChannels, int jobType, std::string path); // : Job(jobChannels, jobType, path) {}; 
        ~CompileJob(){};

        std::string output; 
        int returnCode; 

        void execute() override; 
        void jobCompleteCallback();  
    
    private: 
        std::string command; 

};