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

    Process(unsigned int id = 0, unsigned int cpuTime = 0, unsigned int ioBlocking = 0);
    void IncreaseCPUWorking(unsigned int quantity);
    void SetWaiting(unsigned int quantity);
    unsigned int GetId();
    unsigned int GetCPUTime();
    unsigned int GetIOBlocking();
    unsigned int GetCPUDone();
    unsigned int GetWaiting();
    unsigned int GetNumBlocked();
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
};

