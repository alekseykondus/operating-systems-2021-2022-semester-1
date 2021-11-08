#include "SchedulingAlgorithm.h"

std::vector<std::shared_ptr<Process>> SchedulingAlgorithm::RoundRobin(std::shared_ptr<Process> head, std::vector<std::shared_ptr<Process>> &result,
                                     unsigned int quantum, unsigned int runTime, unsigned int numberOfProcesses, std::stringstream& streamResult)
{
    std::shared_ptr<Process> currentItem = CreateCopyOfProcessesForRR(head);
    int countQuantum = 0;

    streamResult << "BEGIN: Round-Robin scheduling simulation (Quantum: " << quantum << ")" << std::endl;
    while (countQuantum < runTime && (currentItem != currentItem->GetNext() || currentItem->GetCurrentExecutionMode() != Process::ExecutionMode::Finish)) {

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
                result[currentItem->GetId() - 1] = currentItem;
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
            std::shared_ptr<Process> currentItemNext = currentItem->GetNext();
            currentItem->GetPrevious()->SetNext(currentItem->GetNext());
            currentItem->GetNext()->SetPrevious(currentItem->GetPrevious());
            currentItem = currentItemNext;
        }
        else {
            currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Ready);
            currentItem = currentItem->GetNext();
        }
    }
    if (countQuantum == runTime)
        streamResult << std::endl << "TIMEOUT" << std::endl << std::endl;

    streamResult << "END: Round-Robin scheduling simulation" << std::endl;

    for (int i = 0; i < numberOfProcesses; i++) {
        result[currentItem->GetId() - 1] = currentItem;
        currentItem = currentItem->GetNext();
    }
    return result;
}

std::shared_ptr<Process> SchedulingAlgorithm::CreateCopyOfProcessesForRR(std::shared_ptr<Process> head)
{
    std::shared_ptr<Process> item = head;
    std::shared_ptr<Process> copyHead(std::make_shared<Process>(item->GetId(), item->GetCPUTime(), item->GetIOBlocking()));
    std::shared_ptr<Process> copyCurrentItem = copyHead;

    std::shared_ptr<Process> previousItem = copyCurrentItem;

    while (item->GetNext()) {
        std::shared_ptr<Process> nextItem = item->GetNext();
        copyCurrentItem->SetNext(std::make_shared<Process>(nextItem->GetId(), nextItem->GetCPUTime(), nextItem->GetIOBlocking()));
        previousItem = copyCurrentItem;
        copyCurrentItem = copyCurrentItem->GetNext();
        copyCurrentItem->SetPrevious(previousItem);
        item = item->GetNext();
    }
    copyCurrentItem->SetNext(copyHead);
    copyHead->SetPrevious(copyCurrentItem);

    return copyHead;
}
