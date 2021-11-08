/* Scheduling Simulation*/

#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include <iostream>
#include <vector>
#include <string>

#include "Scheduling.h"

#include <sstream>
/*
void CenterAlign(const std::string& s, size_t width_field) {
    std::string v(width_field, ' ');
    std::string v1;

    int l_word = s.size();
    int l_field = v.size();
    int step = (l_field - l_word) / 2;

    for (int i = 0; i < l_word; i++) {
        v1.push_back(s[i]);
    }
    copy(v1.begin(), v1.end(), v.begin() + step);
    for (auto x : v) {
        std::cout << x;
    }
}
void OutputByTable(std::vector<std::shared_ptr<Process>> resultsVector) {

    std::cout << " -------------------------------------------------------------------------------------------" << std::endl;
    std::cout << " | ";
    CenterAlign("Process #", 15);
    std::cout << " | ";
    CenterAlign("CPU Time", 15);
    std::cout << " | ";
    CenterAlign("IO Blocking", 15);
    std::cout << " | ";
    CenterAlign("CPU Completed", 15);
    std::cout << " | ";
    CenterAlign("CPU Blocked", 15);
    std::cout << " | ";


    std::cout << std::endl << " -------------------------------------------------------------------------------------------" << std::endl;
    for (auto currentItem : resultsVector) {
        if (currentItem) {
            std::cout << " | ";
            CenterAlign(std::to_string(currentItem->GetId()), 15);
            std::cout << " | ";
            CenterAlign(std::to_string(currentItem->GetCPUTime()), 15);
            std::cout << " | ";
            CenterAlign(std::to_string(currentItem->GetIOBlocking()), 15);
            std::cout << " | ";
            CenterAlign(std::to_string(currentItem->GetCPUDone()), 15);
            std::cout << " | ";
            CenterAlign(std::to_string(currentItem->GetNumBlocked()), 15);
            std::cout << " | " << std::endl << " -------------------------------------------------------------------------------------------" << std::endl;
        }
    }
}

std::vector<std::shared_ptr<Process>> RoundRobin(std::shared_ptr<Process> head, unsigned int quantum, unsigned int runTime);

void CreateNextProcess(std::shared_ptr<Process> item, unsigned int processId, unsigned int CPUBurstTime) {
}*/

/* Main Program Segment */
int main(void) {
/*    std::shared_ptr<Process> head(new Process(1, 20, 7));
    std::shared_ptr<Process> item = head, previousItem;

    item->SetNext(std::make_shared<Process>(2, 20, 5));
    previousItem = item;
    item = item->GetNext();
    item->SetPrevious(previousItem);

    item->SetNext(std::make_shared<Process>(3, 17, 0));
    previousItem = item;
    item = item->GetNext();
    item->SetPrevious(previousItem);

    item->SetNext(std::make_shared<Process>(4, 12, 3));
    previousItem = item;
    item = item->GetNext();
    item->SetPrevious(previousItem);

    item->SetNext(head);
    head->SetPrevious(item);

    std::vector<std::shared_ptr<Process>> result = RoundRobin(head, 3, 50);

    /*    for (auto currentItem : result) {
            if (currentItem) {
                std::cout << std::endl << "Process: " << currentItem->GetId() << " registered... (" <<
                    "CPUTime = " << currentItem->GetCPUTime() << " IOBlocking = " << currentItem->GetIOBlocking() << " CPUDone = " << currentItem->GetCPUDone() << " )" << std::endl;
            }
        }

    OutputByTable(result);
    return 0;
*/

    Scheduling scheduling(5, 1000, 10);
    scheduling.Run();
    scheduling.PrintResults();

    std::stringstream out;
    std::stringstream out2;
    out << "afsdfadfadfadfadga" << std::endl;

    char sum;
    while (out >> sum)
        out2 << sum;

    while (out2 >> sum)
        std::cout << sum;

};


/* Round-Robin scheduling simulation 
std::vector<std::shared_ptr<Process>> RoundRobin(std::shared_ptr<Process> head, unsigned int quantum, unsigned int runTime) {
    std::vector<std::shared_ptr<Process>> result;
    result.resize(5);

    std::shared_ptr<Process> currentItem = head;
    int countQuantum = 0;

    std::cout << "BEGIN:\tRound-Robin scheduling simulation (Quantum: " << quantum << ")" << std::endl;
    while (countQuantum < runTime && (currentItem != currentItem->GetNext() || currentItem->GetCurrentExecutionMode() != Process::ExecutionMode::Finish)) {

        std::cout << std::endl << "Process: " << currentItem->GetId() << " registered... (" <<
            "CPUTime = " << currentItem->GetCPUTime() << " IOBlocking = " << currentItem->GetIOBlocking() << " CPUDone = " << currentItem->GetCPUDone() << " )" << std::endl;
        currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Working);

        for (int i = 0; i < quantum; i++) {
            countQuantum += 1;
            currentItem->IncreaseCPUWorking(1);
            currentItem->SetWaiting(countQuantum - currentItem->GetCPUDone());

            std::cout << "Process: " << currentItem->GetId() << " Working : " << currentItem->GetCPUDone() << " Waiting : " << currentItem->GetWaiting() << std::endl;
            if (currentItem->GetCPUDone() == currentItem->GetCPUTime()) {
                currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Finish);
                std::cout << "Process: " << currentItem->GetId() << " done... (" <<
                    "CPUTime = " << currentItem->GetCPUTime() << " IOBlocking = " << currentItem->GetIOBlocking() << " CPUDone = " << currentItem->GetCPUDone() << " )" << std::endl << std::endl;
                result[currentItem->GetId() - 1] = currentItem;
                break;
            }
            else if (currentItem->GetIOBlocking() && currentItem->GetCPUDone() % currentItem->GetIOBlocking() == 0) {
                currentItem->SetCurrentExecutionMode(Process::ExecutionMode::Blocked);
                std::cout << "Process: " << currentItem->GetId() << "I/O blocked... (" <<
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
    std::cout << "END:\tRR scheduling simulation" << std::endl;

    currentItem = head;
    for (int i = 0; !i || currentItem->GetId() != head->GetId(); i++) {
        result[currentItem->GetId() - 1] = currentItem;
        currentItem = currentItem->GetNext();
    }
    return result;
}
*/