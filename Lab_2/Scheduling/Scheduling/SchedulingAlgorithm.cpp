#include "SchedulingAlgorithm.h"

std::vector<Process> SchedulingAlgorithm::RoundRobin(std::vector<Process> processesVector, std::vector<Process>& result, unsigned int quantum, unsigned int runTime, std::stringstream& streamResult)
{
    int countQuantum = 0;
    streamResult << "BEGIN: Round-Robin scheduling simulation (Quantum: " << quantum << ")" << std::endl;

    for (auto currentItem = processesVector.begin(); countQuantum < runTime; ) {

        streamResult << std::endl << "Process: " << currentItem->GetId() << " registered... (" <<
            "CPUTime = " << currentItem->GetCPUTime() << " IOBlocking = " << currentItem->GetIOBlocking() << " CPUDone = " << currentItem->GetCPUDone() << " )" << std::endl;
        currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Working);

        for (int i = 0; i < quantum && countQuantum < runTime; i++) {
            countQuantum += 1;
            currentItem->IncreaseCPUWorking(1);
            currentItem->SetWaiting(countQuantum - currentItem->GetCPUDone());

            streamResult << "Process: " << currentItem->GetId() << " Working : " << currentItem->GetCPUDone() << " Waiting : " << currentItem->GetWaiting() << std::endl;
            if (currentItem->GetCPUDone() == currentItem->GetCPUTime()) {
                currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Finish);
                streamResult << "Process: " << currentItem->GetId() << " done... (" <<
                    "CPUTime = " << currentItem->GetCPUTime() << " IOBlocking = " << currentItem->GetIOBlocking() << " CPUDone = " << currentItem->GetCPUDone() << " )" << std::endl << std::endl;
                result[currentItem->GetId() - 1] = *currentItem;
                break;
            }
            else if (currentItem->GetIOBlocking() && currentItem->GetCPUDone() % currentItem->GetIOBlocking() == 0) {
                currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Blocked);
                streamResult << "Process: " << currentItem->GetId() << "I/O blocked... (" <<
                    "CPUTime = " << currentItem->GetCPUTime() << " IOBlocking = " << currentItem->GetIOBlocking() << " CPUDone = " << currentItem->GetCPUDone() << " )" << std::endl << std::endl;
                break;
            }
        }
        if (currentItem->GetCurrentExecutionMode() == Process::ExecutionMode::Finish) {
            //удаляем елемент с циклического списка
            if (currentItem != processesVector.begin()) {
                auto prevCurrentItem = currentItem - 1;
                processesVector.erase(currentItem);
                currentItem = prevCurrentItem;
                currentItem->GetId();
            }
            else if (processesVector.size() == 1) {
                processesVector.erase(currentItem);
            }
            else {
                processesVector.erase(currentItem);
                currentItem = processesVector.end()-1;
                currentItem->GetId();
            }
        }
        else {
            currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Ready);
        }
        if (processesVector.empty())
            break;
        else if (processesVector.size() == 1 || (currentItem + 1 == processesVector.end()))
            currentItem = processesVector.begin();
        else
            currentItem++;
    }
    if (countQuantum == runTime)
        streamResult << std::endl << "TIMEOUT" << std::endl << std::endl;

    streamResult << "END: Round-Robin scheduling simulation" << std::endl;

    for (auto currentItem = processesVector.begin(); currentItem != processesVector.end(); currentItem++)
        result[currentItem->GetId() - 1] = *currentItem;

    return result;
}
