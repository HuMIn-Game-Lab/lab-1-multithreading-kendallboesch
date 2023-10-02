#include "Job.h"


class CompileJob : public Job 
{
    public: 
        CompileJob(int jobID, int jobType, std::string path); // : Job(jobChannels, jobType, path) {}; 
        ~CompileJob(){};

        std::string output; 
        int returnCode; 
        void setID(int IDin);
        void execute() override; 
        //void jobCompleteCallback() override;  
    
    private: 
        std::string command; 

};