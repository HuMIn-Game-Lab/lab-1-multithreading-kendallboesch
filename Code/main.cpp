
#include <iostream>
#include <string> 
#include <regex>
#include "JobSystem.h"
#include "RenderJob.h"
#include "ParseJob.h"
#include "CompileJob.h"


int main(int argc, char *argv[] ) 
{
    std::cout << argc << std::endl; 
    std::cout << "Creating Job System" << std::endl;

    JobSystem* js = JobSystem::createOrGet(); 

    std::cout << "Creating worker threads" << std::endl; 
   // js->CreateWorkerThread("Thread0", 0xFFFFFFFF);
    js->createWorkerThread("Thread1", 0xFFFFFFFF);
    js->createWorkerThread("Thread2", 0xFFFFFFFF);
    js->createWorkerThread("Thread3", 0xFFFFFFFF);
    js->createWorkerThread("Thread4", 0xFFFFFFFF);
    js->createWorkerThread("Thread5", 0xFFFFFFFF);
    js->createWorkerThread("Thread6", 0xFFFFFFFF);
    js->createWorkerThread("Thread7", 0xFFFFFFFF);
    js->createWorkerThread("Thread8", 0xFFFFFFFF);
    js->createWorkerThread("Thread9", 0xFFFFFFFF);

    std::cout << "Create jobs" << std::endl; 

    std::vector<Job*> jobs; 

    CompileJob* cjb = new CompileJob(0xFFFFFFFF, 1); 
    jobs.push_back(cjb); 


    for(int j = 0; j < 10; j++)
    {
        RenderJob* rjb = new RenderJob(0xFFFFFFFF, 1); 
        for(int i = 0; i < 1000; i++)
        {
            rjb->data.push_back(i+j); 
        }
        jobs.push_back(rjb);
    }


    std::cout << "Queueing Jobs" << std::endl; 

    std::vector<Job*>::iterator it = jobs.begin(); 

    for(; it != jobs.end(); ++it)
    {
        js->queueJob(*it); 
    }
    int loop = 0; 
    int running = 1; 

            JobStatus stat = js->getJobStatus(0); 
           // std::cout << "Job status Job 0: " << stat << std::endl; 
            //std:: cout << "Finishing Job 0" << std::endl; 
            js->finishJob(0);
            //stat = js->getJobStatus(0);
            //std::cout << "Status post finishJob call #0: " << stat << std::endl;
            //std::cout << "JOB #11 -- Parse Job Status: " << js->getJobStatus(11) << std::endl; 
            js->finishJob(11);
            //js->finishJob(11);

    // std::regex commandPattern("^clang\\+\\+.*"); // Matches clang++ -g followed by any char
    // std::regex errorPattern("(.*):(\\d+):(\\d+): (error:)+(.*)"); 


    // std::string line1 = "clang++ -g -std=c++14 ./toCompile/demoError.cpp -o error_out";
    // std::string line2 ="./toCompile/demoError.cpp:3:5: error: use of undeclared identifier 'cout'";
    // if(std::regex_match(line2, errorPattern))
    // {
    //     std::cout << "match" << std::endl; 
    // }
    // else{
    //     std::cout << "no match" << std::endl; 
    // }

     return 0;
}