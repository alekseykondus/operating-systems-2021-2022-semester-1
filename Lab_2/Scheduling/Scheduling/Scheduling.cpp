#include "Scheduling.h"

Scheduling::Scheduling(unsigned int numberOfProcesses, unsigned int runtime, unsigned int quantum, unsigned int average, unsigned int deviation)
    : m_NumberOfProcesses(numberOfProcesses), m_Runtime(runtime), m_Quantum(quantum), m_Average(average), m_Deviation(deviation)
{
    m_ResultVector.resize(numberOfProcesses);
    CreateProcesses();
}

void Scheduling::CreateProcesses()
{
    std::random_device rd;
    std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

    for (int i = 0; i < m_NumberOfProcesses; i++) {
        unsigned int CPUTime = mersenne() % (m_Average - m_Deviation) + 2 * m_Deviation;
        unsigned int IOBlocking = mersenne() % 10;
        Process p(i + 1, CPUTime, IOBlocking);
        m_ProcessesVector.push_back(p);
    }
    /*
    m_ProcessesVector.push_back(Process(1, 50, 7));
    m_ProcessesVector.push_back(Process(2, 40, 5));
    m_ProcessesVector.push_back(Process(3, 30, 0));
    m_ProcessesVector.push_back(Process(4, 20, 3));
   
    m_ProcessesVector.push_back(Process(1, 30, 7));
    m_ProcessesVector.push_back(Process(2, 40, 5));
    m_ProcessesVector.push_back(Process(3, 30, 0));
    m_ProcessesVector.push_back(Process(4, 5, 0));
     */
}

void Scheduling::Run()
{
    m_Algorithm.RoundRobin(m_ProcessesVector, m_ResultVector, m_Quantum, m_Runtime, m_StreamResult);
}

void Scheduling::PrintResults()
{
    //m_StreamResult << m_StreamResult.str();
    std::ofstream outputToFile;
    outputToFile.open("Summary-Processes.txt");
    outputToFile << m_StreamResult.str();
    outputToFile.close(); 

    m_StreamResult.str("");

    int amountOfWaitingTime = 0;
    for (auto element : m_ResultVector)
        amountOfWaitingTime += element.GetWaiting();

    m_StreamResult << "Scheduling Name: Round Robin" << std::endl;
    m_StreamResult << "Average: " << m_Average << std::endl;
    m_StreamResult << "Standard Deviation: " << m_Deviation << std::endl;
    m_StreamResult << "Average waiting time: " << amountOfWaitingTime / m_NumberOfProcesses << std::endl;

    OutputOverallResultsByTable(m_ResultVector);
    outputToFile.open("Summary-Results.txt");
    outputToFile << m_StreamResult.str();
    outputToFile.close();
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
        m_StreamResult << x;
    }
}

void Scheduling::OutputOverallResultsByTable(std::vector<Process> resultsVector)
{
    m_StreamResult << " -------------------------------------------------------------------------------------------" << std::endl;
    m_StreamResult << " | ";
    CenterAlign("Process #", 15);
    m_StreamResult << " | ";
    CenterAlign("CPU Time", 15);
    m_StreamResult << " | ";
    CenterAlign("IO Blocking", 15);
    m_StreamResult << " | ";
    CenterAlign("CPU Completed", 15);
    m_StreamResult << " | ";
    CenterAlign("CPU Blocked", 15);
    m_StreamResult << " | ";


    m_StreamResult << std::endl << " -------------------------------------------------------------------------------------------" << std::endl;
    for (auto currentItem : resultsVector) {
        m_StreamResult << " | ";
        CenterAlign(std::to_string(currentItem.GetId()), 15);
        m_StreamResult << " | ";
        CenterAlign(std::to_string(currentItem.GetCPUTime()), 15);
        m_StreamResult << " | ";
        CenterAlign(std::to_string(currentItem.GetIOBlocking()), 15);
        m_StreamResult << " | ";
        CenterAlign(std::to_string(currentItem.GetCPUDone()), 15);
        m_StreamResult << " | ";
        CenterAlign(std::to_string(currentItem.GetNumBlocked()), 15);
        m_StreamResult << " | " << std::endl << " -------------------------------------------------------------------------------------------" << std::endl;
    }
}
