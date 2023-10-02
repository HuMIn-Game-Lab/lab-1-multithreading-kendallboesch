#include <iostream> 
#include "JobSystem.h"
#include "JobWorkerThread.h"

JobSystem* JobSystem::s_jobSystem = nullptr; 

typedef void (*JobCallback)(Job* completedJob); 

JobSystem::JobSystem()
{
    m_jobHistory.reserve(256 * 1024); 
}

JobSystem::~JobSystem()
{
    m_workerThreadsMutex.lock(); 

    int numThreads = (int)m_workerThreads.size(); 

    for(int i = 0; i < numThreads; i++)
    {
        m_workerThreads[i]->shutDown(); 
    }

    while(!m_workerThreads.empty())
    {
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
        //if(strcmp((*it)->m_uniqueName, uniqueName) == 0)
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
}

JobStatus JobSystem::getJobStatus(int jobID) const
{
    m_jobHistoryMutex.lock(); 

    JobStatus status = JOB_STATUS_NEVER_SEEN;
    if(jobID, (int) m_jobHistory.size())
    {
        status = m_jobHistory[jobID].m_jobStatus; 
    }

    m_jobHistoryMutex.unlock(); 

    return status; 
}

int JobSystem::getJobID(Job* job)
{
    return job->m_jobID; 
}

bool JobSystem::isJobComplete(int jobID) const
{
    return JobStatus (jobID) == JOB_STATUS_COMPLETED;
}

void JobSystem::finishCompletedJobs()
{
    std::deque<Job*> jobsCompleted; 

    m_jobsCompletedMutex.lock(); 

    jobsCompleted.swap(m_jobsCompleted);
    m_jobsCompletedMutex.unlock(); 

    for(Job* job : jobsCompleted)
    {
        job->jobsCompleteCallback(); 
        m_jobHistoryMutex.lock(); 
        m_jobHistory[job->m_jobID].m_jobStatus = JOB_STATUS_RETIRED;
        m_jobHistoryMutex.unlock(); 
        delete job;
    }
}

void JobSystem::finishJob(int jobID)
{
    while(!isJobComplete(jobID))
    {
        JobStatus status = getJobStatus(jobID);

        if(status == JOB_STATUS_NEVER_SEEN || status == JOB_STATUS_RETIRED)
        {
            std::cout << "ERROR: Waiting for Job(#" << jobID <<") - no such job in JobSystem" << std::endl; 
            return;
        }

        m_jobsCompletedMutex.lock(); 
        Job* thisCompletedJob = nullptr; 
        for(auto jcItr = m_jobsCompleted.begin(); jcItr != m_jobsCompleted.end(); ++jcItr)
        {
            Job* someCompletedJob = *jcItr; 
            if(someCompletedJob->m_jobID == jobID)
            {
                thisCompletedJob = someCompletedJob; 
                m_jobsCompleted.erase(jcItr); 
                break;
            }
        }

        m_jobsCompletedMutex.unlock(); 

        if(thisCompletedJob == nullptr)
        {
            std::cout << "ERROR: Job #" << jobID << " was status completed but not found in completed lisy" << std::endl;    
        }

        thisCompletedJob->jobsCompleteCallback(); 

        m_jobHistoryMutex.lock(); 
        m_jobHistory[thisCompletedJob->m_jobID].m_jobStatus = JOB_STATUS_RETIRED; 
        m_jobHistoryMutex.unlock(); 

        delete thisCompletedJob;
    }
}

void JobSystem::onJobCompleted(Job* justExecuted)
{
    totalJobs++; 
    m_jobsCompletedMutex.lock(); 
    m_jobsRunningMutex.lock(); 

    std::deque<Job*>::iterator runningJobItr = m_jobsRunning.begin(); 

    for(; runningJobItr != m_jobsRunning.end(); ++runningJobItr)
    {
        if(justExecuted == * runningJobItr)
        {
            m_jobHistoryMutex.lock(); 
            m_jobsRunning.erase(runningJobItr); 
            m_jobsCompleted.push_back(justExecuted); 
            m_jobHistory[justExecuted->m_jobID].m_jobStatus = JOB_STATUS_COMPLETED;
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

            m_jobHistoryMutex.unlock();
            break; 
        }
    }

    m_jobsRunningMutex.unlock(); 
    m_jobsQueuedMutex.unlock();

    return claimedJob;
}