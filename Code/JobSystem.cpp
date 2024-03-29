
// {
//     return m_jobsCompleted;    
// }
#include <iostream> 
#include "JobSystem.h" 
#include "JobWorkerThread.h"
#include "ParseJob.h"
#include "JSONJob.h"
JobSystem* JobSystem::s_jobSystem = nullptr; 

typedef void (*JobCallback)(Job* completedJob);    
//new type called JObCallBack --> can use that to make all the code i write with function pointers way simpler; 

JobSystem::JobSystem()
{
    m_jobHistory.reserve(256 * 1024); 
}
JobSystem::~JobSystem()
{
    m_workerThreadsMutex.lock(); 
    int numWorkerThreads = (int)m_workerThreads.size(); 

    //First, tell each worker thread to stop picking up jobs 
    for(int i = 0; i < numWorkerThreads; ++i)
    {
        m_workerThreads[i]->shutDown(); 
    }

    while( !m_workerThreads.empty()){
        delete m_workerThreads.back(); 
        m_workerThreads.pop_back(); 
    }
    m_workerThreadsMutex.unlock(); 
}

JobSystem* JobSystem::createOrGet()
{

    if(!s_jobSystem)
    {
        s_jobSystem = new JobSystem(); 
    }
    return s_jobSystem; 
}

void JobSystem::destroy()
{
    if(s_jobSystem)
    {
        delete s_jobSystem; 
        s_jobSystem = nullptr; 
    }
}

void JobSystem::createWorkerThread(const char* uniqueName, unsigned long workerJobChannel)
{
    JobWorkerThread* newWorker = new JobWorkerThread(uniqueName, workerJobChannel, this); 
    m_workerThreadsMutex.lock(); 
    m_workerThreads.push_back(newWorker);
    m_workerThreadsMutex.unlock(); 

    m_workerThreads.back()->startUp(); 
}

void JobSystem::destroyWorkerThread(const char *uniqueName)
{
    m_workerThreadsMutex.lock(); 
    JobWorkerThread *worker = nullptr; 
    std::vector<JobWorkerThread*>::iterator it = m_workerThreads.begin(); 

    for(; it != m_workerThreads.end(); ++it)
    {
        if((*it)->m_uniqueName == uniqueName)
       // if(strcmp((*it)->m_uniqueName, uniqueName) == 0)
        {
            worker = *it; 
            m_workerThreads.erase(it); 
            break;
        }
    }   
    m_workerThreadsMutex.unlock(); 

    if(worker)
    {
        worker->shutDown(); 
        delete worker;
    }
}

void JobSystem::queueJob(Job* job)
{
    m_jobHistoryMutex.lock(); 
     m_jobsQueuedMutex.lock(); 

    m_jobHistory.emplace_back(JobHistoryEntry(job->m_jobType, JOB_STATUS_QUEUED)); 

    m_jobHistoryMutex.unlock(); 
    m_jobsQueued.push_back(job); 
    m_jobsQueuedMutex.unlock(); 

   // std::cout << "Queued: " << GetJobID(job) << std::endl;
}
JobStatus JobSystem::getJobStatus(int jobID) const{
    m_jobHistoryMutex.lock();

    JobStatus jobStatus = JOB_STATUS_NEVER_SEEN;
    if (jobID < (int) m_jobHistory.size()){
        jobStatus = (JobStatus)(m_jobHistory[jobID].m_jobStatus);
    }

    m_jobHistoryMutex.unlock();
    return jobStatus;
}
int JobSystem::getJobID(Job* job) 
{
    return job->m_jobID;
}

// bool JobSystem::isJobComplete(int jobID) const
// {
//     return GetJobStatus(jobID) == JOB_STATUS_COMPLETED; 
// }
bool JobSystem::isJobComplete(int jobID) const{
    return (getJobStatus(jobID)) == (JOB_STATUS_COMPLETED);
}
void JobSystem::finishCompletedJobs()
{
    std::deque<Job*> jobsCompleted; 

    m_jobsCompletedMutex.lock(); 

    jobsCompleted.swap(m_jobsCompleted); 
    m_jobsCompletedMutex.unlock(); 

    for(Job* job : jobsCompleted)
    {
        job->jobCompleteCallback(); 
        m_jobHistoryMutex.lock();
        m_jobHistory[job->m_jobID].m_jobStatus = JOB_STATUS_RETIRED; 
        m_jobHistoryMutex.unlock(); 
        delete job; 
    }
}
void JobSystem::finishJob(int jobID){

    // The code after the while loop was within the body of the loop
    while(!isJobComplete(jobID)){
        JobStatus jobStatus = getJobStatus(jobID);
        if((jobStatus == JOB_STATUS_NEVER_SEEN) || (jobStatus == JOB_STATUS_RETIRED)){
            std::cout << "Error: Waiting for job (# " << jobID << ") - no such job in JobSystem" << std::endl;
            return; 
        }
    }
    m_jobsCompletedMutex.lock();
    Job* thisCompletedJob = nullptr;
    for(auto jcIter = m_jobsCompleted.begin(); jcIter != m_jobsCompleted.end(); ++jcIter){
        Job* someCompletedJob = *jcIter;
        if(someCompletedJob->m_jobID == jobID){
            thisCompletedJob = someCompletedJob;
            m_jobsCompleted.erase(jcIter);
            break;
        }
    }
    m_jobsCompletedMutex.unlock(); 
    if(thisCompletedJob == nullptr)
    {
        std::cout << "ERROR: Job # " << jobID << " was status completed but not found" << std::endl;
    }

    if(thisCompletedJob->m_jobType == 1 && thisCompletedJob->compResults != "")    // JobType 1 = compile job 
    {
        std::cout << "getting unparsed compilation results" << std::endl;
        ParseJob* pjb = new ParseJob(0xFFFFFFFF, 2); 
        pjb->unparsedText = thisCompletedJob->compResults; 
        this->queueJob(pjb); 
        thisCompletedJob->childJob=pjb; 
    }
    else if (thisCompletedJob->m_jobType == 2)      // JobType 2 = parse job
    {
        std::cout << "Generating JSONJob for parsed output" << std::endl; 
        JSONJob* jsjb = new JSONJob(0xFFFFFFFF, 3); 
        jsjb->errorMap = thisCompletedJob->errorMap;
        this->queueJob(jsjb); 
        thisCompletedJob->childJob = jsjb; 
    }

    
    thisCompletedJob->jobCompleteCallback();

    m_jobHistoryMutex.lock();
    m_jobHistory[thisCompletedJob->m_jobID].m_jobStatus = JOB_STATUS_RETIRED;
    m_jobHistoryMutex.unlock();

    if(thisCompletedJob->childJob != nullptr)
    {
        this->finishJob(thisCompletedJob->childJob->m_jobID); 
    }

    delete thisCompletedJob;
}
// Rest of the code
void JobSystem::onJobCompleted(Job* jobJustExecuted )
{
    totalJobs++;
    m_jobsCompletedMutex.lock(); 
    m_jobsRunningMutex.lock(); 

    std::deque<Job*>::iterator runningJobItr = m_jobsRunning.begin(); 
    for(; runningJobItr!= m_jobsRunning.end(); ++runningJobItr)
    {
        if(jobJustExecuted == * runningJobItr)
        {
            m_jobHistoryMutex.lock(); 
            m_jobsRunning.erase(runningJobItr); 
            m_jobsCompleted.push_back(jobJustExecuted); 
            m_jobHistory[jobJustExecuted->m_jobID].m_jobStatus = JOB_STATUS_COMPLETED; 
            m_jobHistoryMutex.unlock(); 

            break; 
        }
    }
    m_jobsRunningMutex.unlock(); 
    m_jobsCompletedMutex.unlock(); 
}

Job* JobSystem::claimJob(unsigned long workerJobChannels)
{
    m_jobsQueuedMutex.lock(); 
    m_jobsRunningMutex.lock(); 

    Job* claimedJob = nullptr; 
    std::deque<Job *>::iterator queuedJobItr = m_jobsQueued.begin(); 

    for(; queuedJobItr != m_jobsQueued.end(); ++queuedJobItr)
    {
        Job* queuedJob = *queuedJobItr; 

        if((queuedJob->m_jobChannels & workerJobChannels) != 0)
        {
            claimedJob = queuedJob; 

            m_jobHistoryMutex.lock(); 

            m_jobsQueued.erase(queuedJobItr); 
            m_jobsRunning.push_back(claimedJob);
            m_jobHistory[claimedJob->m_jobID].m_jobStatus = JOB_STATUS_RUNNING;

            //TODO: Check 
            m_jobHistoryMutex.unlock(); 
            break; 
        }
    }
    m_jobsRunningMutex.unlock(); 
    m_jobsQueuedMutex.unlock(); 

    return claimedJob;
}