#include <iostream> 
#include "JobSystem.h"
#include "CompileJob.h"

int main()
{
    JobSystem* syst = JobSystem::createOrGet();

    syst->createWorkerThread("T1", 0xFFFFFFFF);
    syst->createWorkerThread("T2", 0xFFFFFFFF);
    syst->createWorkerThread("T3", 0xFFFFFFFF);
    syst->createWorkerThread("T4", 0xFFFFFFFF);

    std::vector<Job*> jobs;

    for( int i = 0; i < 6; i++)
    {
        CompileJob* cjb = new CompileJob(0xFFFFFFFF, 1); 
        jobs.push_back(cjb);
    }

    return 0;
   
}