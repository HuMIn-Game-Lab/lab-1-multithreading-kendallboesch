#pragma once 
#include <vector> 
#include <mutex> 
#include <deque> 
#include <thread> 

const int JOB_TYPE_ANY = -1;

class JobWorkerThread; 

enum JobStatus {
    JOB_STATUS_NEVER_SEEN, 
    JOB_STATUS_QUEUED, 
    JOB_STATUS_RUNNING, 
    JOB_STATUS_COMPLETED, 
    JOB_STATUS_RETIRED, 
    NUM_JOB_STATUSES
}; 

struct JobHistoryEntry
{
    JobHistoryEntry(int jobType, JobStatus jobStatus)
        : m_jobType(jobType),
        m_jobStatus(jobStatus){}

        int m_jobType = -1; 
        JobStatus m_jobStatus = JOB_STATUS_NEVER_SEEN; 
};

class Job; 
class JobSystem 
{
    friend class JobWorkerThread; 

    public: 
       // JobSystem(); 
        ~JobSystem(); 
       // static int s_nextID; 

        static JobSystem* createOrGet(); 
        static void destroy(); 
        int totalJobs = 0;

        void createWorkerThread(const char* uniqueName, unsigned long workerJobChannel = 0xFFFFFFFF); 
        void destroyWorkerThread(const char* uniqueName); 
        void queueJob(Job* job); 

        JobStatus getJobStatus(int jobID) const; 
        bool isJobComplete(int jobID) const; 

        void finishCompletedJobs(); 
        void finishJob(int jobID); 
        int getJobID(Job* job); 
        void getAllJobInfo(); 

    private: 
        // Private constructor to prevent external instantiation 
        JobSystem();
       // JobSystem &getInstance();

        Job* claimJob(unsigned long workerJobFlags); 
        void onJobCompleted(Job* jobJustExecuted); 

        static JobSystem* s_jobSystem; 

        std::vector<JobWorkerThread*> m_workerThreads;
        mutable std::mutex              m_workerThreadsMutex; 
        std::deque< Job*>               m_jobsQueued; 
        std::deque<Job*>                m_jobsRunning;
        std::deque<Job*>                m_jobsCompleted; 
        mutable std::mutex              m_jobsQueuedMutex; 
        mutable std::mutex              m_jobsRunningMutex; 
        mutable std::mutex              m_jobsCompletedMutex; 

        std::vector<JobHistoryEntry>    m_jobHistory; 
        mutable int                     m_jobHistoryLowestActiveIndex = 0; 
        mutable std::mutex              m_jobHistoryMutex; 
    };