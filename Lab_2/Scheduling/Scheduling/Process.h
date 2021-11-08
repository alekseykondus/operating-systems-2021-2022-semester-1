#pragma once
#include <memory>

class Process
{
public:
    enum ExecutionMode {
        Ready,
        Working,
        Blocked,
        Finish,
    };

    Process(unsigned int id, unsigned int cpuTime, unsigned int ioBlocking = 0);
    void IncreaseCPUWorking(unsigned int quantity);
    void SetWaiting(unsigned int quantity);
    unsigned int GetId();
    unsigned int GetCPUTime();
    unsigned int GetIOBlocking();
    unsigned int GetCPUDone();
    unsigned int GetWaiting();
    unsigned int GetNumBlocked();
    std::shared_ptr<Process> GetNext();
    void SetNext(std::shared_ptr<Process> next);
    std::shared_ptr<Process> GetPrevious();
    void SetPrevious(std::shared_ptr<Process> previous);

    void SetCurrentExecutionMode(ExecutionMode executionMode);
    ExecutionMode GetCurrentExecutionMode();

private:
    unsigned int m_Id;                 /* Process ID */
    unsigned int m_CPUTime;            /* CPU Time */
    unsigned int m_CPUDone;            /* Working time, for round-robin scheduling */
    unsigned int m_IOBlocking;         /* Process blocking interval */
    unsigned int m_NumBlocked;         /* Process blocking interval */
    unsigned int m_Waiting;            /* Waiting time, for round-robin scheduling */
    ExecutionMode m_CurrentExecutionMode;

    std::shared_ptr<Process> m_Next;
    std::shared_ptr<Process> m_Previous;
};

