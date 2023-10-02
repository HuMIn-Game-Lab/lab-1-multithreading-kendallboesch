#include <iostream> 
#include "JobSystem.h"
#include "CompileJob.h"
#include "Job.h"

int main()
{
    JobSystem* syst = JobSystem::createOrGet();
    // JobSystem& syst = JobSystem::getInstance(); 

    syst->createWorkerThread("T1", 0xFFFFFFFF);
    // syst->createWorkerThread("T2", 0xFFFFFFFF);
    // syst->createWorkerThread("T3", 0xFFFFFFFF);
    // syst->createWorkerThread("T4", 0xFFFFFFFF);

    std::vector<Job*> jobs;

    // for( int i = 0; i < 6; i++)
    // {
    //     CompileJob* cjb = new CompileJob(0xFFFFFFFF, 1, ""); 
    //     jobs.push_back(cjb);
    // }

    CompileJob* cjb = new CompileJob(1, 1, "automated");
    //CompileJob* cjb2 = new CompileJob(0xFFFFFFFF, 1, "none");
    jobs.push_back(cjb); 
    // jobs.push_back(cjb2);

    std::vector<Job*>::iterator itr = jobs.begin(); 

    // for(; itr != jobs.end(); ++itr)
    // {
    //     syst->queueJob(*itr); 
    //    // std::cout << *itr->jobID;
    // }

    syst->queueJob(*itr);
   
    //syst->getJobStatus(0);
 
    std::cout << "Job Status: " << syst->getJobStatus(1) << std::endl; 

    syst->finishJob(0);
   // syst->finishCompletedJobs();
    std::cout << "FINISHED MAIN" << std::endl; 

    return 0;
   
}