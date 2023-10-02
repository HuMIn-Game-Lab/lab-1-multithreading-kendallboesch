// #include "Job.h"


// class CompileJob : public Job 
// {
//     public: 
//         CompileJob(int jobID, int jobType, std::string path); // : Job(jobChannels, jobType, path) {}; 
//         ~CompileJob(){};

//         std::string output; 
//         int returnCode; 
//         void setID(int IDin);
//         void jobCompleteCallback() override;
//         void execute() override;
//         //void jobCompleteCallback() override;  
    
//     private: 
//         std::string command; 

// };
#include "Job.h"
#include "ParseJob.h"
/*********
 *
 *
 *
 */

class CompileJob : public Job{
public:
    CompileJob(unsigned long jobChannels, int jobType ) : Job(jobChannels, jobType) {};
    ~CompileJob() {};

    std::string output;
    int returnCode;

    ParseJob* createError(std::string); 
    void execute();
    void jobCompleteCallback();
};