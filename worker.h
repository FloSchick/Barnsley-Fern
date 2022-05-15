#include <thread>
#ifndef WORKER_H
#define WORKER_H

class Worker
{

private:
    std::thread m_thread;
    bool m_terminate;
    bool m_running;
    void work()
    //TODO: Diese Funktion muss in einem Thread laufen
    {
        bool status = true;

        while (status && !m_terminate)
        {
            status = step();
        }
    }

public:
    Worker() : m_running(false), m_terminate(false) {}
    ~Worker()
    {
        m_terminate = true;
    }
    void start_thread()
    {
        if (!m_running)
        {
            m_running = true;
            std::cout << "starting worker" << std::endl;
            m_thread = std::thread(&Worker::work, this);
        }
    };
    void join_thread()
    {
        m_thread.join();
    }
    void stop_thread()
    {
        m_running = false;
        m_terminate = true;
    }

protected:
    virtual bool step() = 0;
};

#endif