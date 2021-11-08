#include "Scheduling.h"

Scheduling::Scheduling(unsigned int numberOfProcesses, unsigned int runtime, unsigned int quantum) 
    : m_NumberOfProcesses(numberOfProcesses), m_Runtime(runtime), m_Quantum(quantum)
{
    m_ResultVector.resize(numberOfProcesses);
    CreateProcesses();
}

void Scheduling::CreateProcesses()
{
    std::shared_ptr<Process> head(std::make_shared<Process>(1, 50, 7));
    std::shared_ptr<Process> item = head, previousItem;

    item->SetNext(std::make_shared<Process>(2, 40, 5));
    previousItem = item;
    item = item->GetNext();
    item->SetPrevious(previousItem);

    item->SetNext(std::make_shared<Process>(3, 30, 0));
    previousItem = item;
    item = item->GetNext();
    item->SetPrevious(previousItem);

    item->SetNext(std::make_shared<Process>(4, 20, 3));
    previousItem = item;
    item = item->GetNext();
    item->SetPrevious(previousItem);

//    item->SetNext(head);
//    head->SetPrevious(item);

    m_Head = head;
}

void Scheduling::Run()
{
   m_ResultVector = m_Algorithm.RoundRobin(m_Head, m_ResultVector, m_Quantum, m_Runtime, m_NumberOfProcesses, m_StreamResult);
}

void Scheduling::PrintResults()
{
    std::cout << m_StreamResult.str();
    std::ofstream outputToFile;
    outputToFile.open("Summary-Processes.txt");
    outputToFile << m_StreamResult.str();
    outputToFile.close(); 

    OutputByTable(m_ResultVector);
}

void Scheduling::CenterAlign(const std::string& s, size_t width_field)
{
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

void Scheduling::OutputByTable(std::vector<std::shared_ptr<Process>> resultsVector)
{

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
