#include "Job.h"

class CompileJob : public Job 
{
    public: 
        CompileJob(unsigned long jobChannels, int jobType) : Job(jobChannels, jobType) {}; 
        ~CompileJob(){};

        std::string output; 
        int returnCode; 

        void execute(std::string); 
        void jobCompleteCallback();  

};