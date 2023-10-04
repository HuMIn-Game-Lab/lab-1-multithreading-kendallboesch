
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
    std::string command; 

    //ParseJob* createError(std::string); 
    void execute();
    void jobCompleteCallback();
};