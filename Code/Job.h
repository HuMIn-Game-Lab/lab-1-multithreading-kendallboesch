#pragma once 
#include <mutex>
#include <map>
#include <deque>
#include <vector>
#include <thread>
class Job 
{
    friend class JobSystem; 
    friend class JobWorkerThread;
    public: 
        Job(unsigned long jobChannels = 0xFFFFFFFF, int jobType = -1) : m_jobChannels(jobChannels), m_jobType(jobType)
        {
            static int s_nextJobID = 0; 
            m_jobID = s_nextJobID; 
        }
        virtual ~Job() {}
        virtual void execute(std::string command) = 0; 
        virtual void jobsCompleteCallback() {}
        int getUniqueID() const {return m_jobID;}

    private: 
        int m_jobID; 
        int m_jobType; 

        unsigned long m_jobChannels; 
};