
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

    //ParseJob* createError(std::string); 
    void execute();
    void jobCompleteCallback();
};