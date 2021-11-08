#include "Process.h"

Process::Process(unsigned int id, unsigned int cpuTime, unsigned int ioBlocking) 
    : m_Id(id), m_CPUTime(cpuTime), m_IOBlocking(ioBlocking), m_Waiting(0), m_CPUDone(0), m_NumBlocked(0), m_CurrentExecutionMode(ExecutionMode::Ready) {
}

unsigned int Process::GetId()
{
    return m_Id;
}

void Process::IncreaseCPUWorking(unsigned int quantity)
{
    m_CPUDone += quantity;
}

void Process::SetWaiting(unsigned int quantity)
{
    m_Waiting = quantity;
}

unsigned int Process::GetCPUTime()
{
    return m_CPUTime;
}

unsigned int Process::GetIOBlocking()
{
    return m_IOBlocking;
}

unsigned int Process::GetCPUDone()
{
    return m_CPUDone;
}

unsigned int Process::GetWaiting()
{
    return m_Waiting;
}

unsigned int Process::GetNumBlocked()
{
    return m_NumBlocked;
}

void Process::SetCurrentExecutionMode(ExecutionMode executionMode)
{
    m_CurrentExecutionMode = executionMode;
    if (executionMode == ExecutionMode::Blocked)
        m_NumBlocked++;
}

Process::ExecutionMode Process::GetCurrentExecutionMode()
{
    return m_CurrentExecutionMode;
}
