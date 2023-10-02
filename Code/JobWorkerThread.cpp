#include "JobWorkerThread.h"
#include "JobSystem.h"

JobWorkerThread::JobWorkerThread(const char * uniqueName, unsigned long workerJobChannel, JobSystem* jobSystem) :
m_uniqueName(uniqueName), 
m_workerJobChannels(workerJobChannel),
m_jobSystem(jobSystem){}

JobWorkerThread::~JobWorkerThread()
{
    shutDown(); 
    m_thread->join(); 
    delete m_thread; 
    m_thread = nullptr;
}

void JobWorkerThread::workerThreadMain(void *workerThreadObject)
{
    JobWorkerThread* thisWorker = (JobWorkerThread*) workerThreadObject; 
    thisWorker->work(); 
}

void JobWorkerThread::startUp()
{
   // m_thread = new std::thread(JobWorkerThread::workerThreadMain, this);
    //m_thread = new std::thread(JobWorkerThread::WorkerThreadMain, this); 
    m_thread = new std::thread(workerThreadMain, this);

}

void JobWorkerThread::work()
{
    while(!isStopping())
    {
        m_workerStatusMutex.lock(); 
        unsigned long workerJobChannels = m_workerJobChannels; 
        m_workerStatusMutex.unlock();

        Job* job = m_jobSystem->claimJob(m_workerJobChannels); 
        if(job)
        {
            job->execute("make automated");
            m_jobSystem->onJobCompleted(job); 
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

void JobWorkerThread::shutDown()
{
    m_workerStatusMutex.lock(); 
    m_isStopping = true; 
    m_workerStatusMutex.unlock();
}

bool JobWorkerThread::isStopping() const
{
    m_workerStatusMutex.lock(); 
    bool shouldClose = m_isStopping;
    m_workerStatusMutex.unlock();

    return shouldClose;
}

void JobWorkerThread::setWorkerJobChannels(unsigned long workerJobChannels)
{
    m_workerStatusMutex.lock();
    m_workerJobChannels = workerJobChannels; 
    m_workerStatusMutex.unlock();
}