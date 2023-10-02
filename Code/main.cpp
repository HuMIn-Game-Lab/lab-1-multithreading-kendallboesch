// #include <iostream> 
// #include "JobSystem.h"
// #include "CompileJob.h"
// #include "Job.h"

// int main()
// {
//     JobSystem* syst = JobSystem::createOrGet();
//     // JobSystem& syst = JobSystem::getInstance(); 

//     syst->createWorkerThread("T1", 0xFFFFFFFF);
//     // syst->createWorkerThread("T2", 0xFFFFFFFF);
//     // syst->createWorkerThread("T3", 0xFFFFFFFF);
//     // syst->createWorkerThread("T4", 0xFFFFFFFF);

//     std::vector<Job*> jobs;

//     // for( int i = 0; i < 6; i++)
//     // {
//     //     CompileJob* cjb = new CompileJob(0xFFFFFFFF, 1, ""); 
//     //     jobs.push_back(cjb);
//     // }

//     CompileJob* cjb = new CompileJob(1, 1, "automated");
//     //CompileJob* cjb2 = new CompileJob(0xFFFFFFFF, 1, "none");
//     jobs.push_back(cjb); 
//     // jobs.push_back(cjb2);

//     std::vector<Job*>::iterator itr = jobs.begin(); 

//     // for(; itr != jobs.end(); ++itr)
//     // {
//     //     syst->queueJob(*itr); 
//     //    // std::cout << *itr->jobID;
//     // }

//     syst->queueJob(*itr);
   
//     //syst->getJobStatus(0);
 
//     std::cout << "Job Status: " << syst->getJobStatus(1) << std::endl; 
//    // syst->wait(); 

//     syst->finishJob(1);

//     std::cout << "Job Status: " << syst->getJobStatus(1) << std::endl; 
//    // syst->finishCompletedJobs();

//    //  int numQ = syst->numQueued(); 
  
//    //    int numQ = syst->numQueued();  
//    //    std::cout << numQ << std:: endl; 
    
//     std::cout << "FINISHED MAIN" << std::endl; 

//     return 0;

 
   
// }

#include <iostream>
#include <string> 

#include "JobSystem.h"
#include "RenderJob.h"
#include "CompileJob.h"


int main(void ) {
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

//     // while(running)
//     // {
        
//         std::string command; 
//         std::cout << "Enter stop, destroy, finish, finishjob, status: ";
//         std::cin >> command; 
//         if (loop >= 7)
//         {
//             command = "stop";
//         }

//         std::cout << "INPUT: " << command << std::endl;

//         if(command == "stop")
//         {
//             std::cout << "stopping" << std::endl; 
//             running = 0; 
//         }
//         else if(command == "destroy")
//         {
//             js->FinishCompletedJobs();
//             js->Destory(); 
//             running = 0; 
//         }
//         else if(command == "finish")
//         {
//            js->FinishCompletedJobs(); 
//            std::cout << "Total Jobs Completed: " << js->totalJobs << std::endl; 

//         }
//         else if(command == "finishjob")
//         {


//         }
//         else if (command == "status")
//         {
            JobStatus stat = js->getJobStatus(0); 
            std::cout << "Job status " << stat << std::endl; 
            std:: cout << "Finishing Job 0" << std::endl; 
            js->finishJob(0);
            stat = js->getJobStatus(0);
            std::cout << "STATUS: " << stat << std::endl;
            js->finishJob(0); 
            std::cout << js->getJobStatus(0) << std::endl; 
            
//             switch(stat)
//             {
//                 case JOB_STATUS_NEVER_SEEN : 
//                     std::cout << "Never seen" << std::endl;
//                     break; 
//                 case JOB_STATUS_QUEUED :
//                     std::cout << "Queued" << std::endl;
//                     break; 
//                 case JOB_STATUS_RUNNING : 
//                     std::cout << "Running" << std::endl;
//                     break; 
//                 case JOB_STATUS_COMPLETED : 
//                     std::cout << "Completed" << std::endl; 
//                     break; 
//                 case JOB_STATUS_RETIRED : 
//                     std::cout << "Retired" << std::endl; 
//                     break;
//                 case NUM_JOB_STATUSES : 
//                     std::cout << "Num stats??" << std::endl;
//                     break;


//             }

//         }
//         else 
//         {
//             std::cout <<"Invalid command" << std::endl; 
//         }
//         loop++; 
//    // }


    return 0;
}