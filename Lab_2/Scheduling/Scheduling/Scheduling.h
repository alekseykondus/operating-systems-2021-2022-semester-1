#pragma once
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include <vector>
//#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

class Scheduling
{
public:
	Scheduling(unsigned int numberOfProcesses, unsigned int runtime, unsigned int quantum, unsigned int average, unsigned int deviation);
	void Run();
	void PrintResults();

private:
	unsigned int m_Runtime;
	unsigned int m_NumberOfProcesses;
	unsigned int m_Quantum;
	unsigned int m_Average;
	unsigned int m_Deviation;
	std::shared_ptr<Process> m_Head;
	SchedulingAlgorithm m_Algorithm;
	std::stringstream m_StreamResult;
	std::vector<Process> m_ProcessesVector;
	std::vector<Process> m_ResultVector;

	void CreateProcesses();
	void CenterAlign(const std::string& s, size_t width_field);
	void OutputOverallResultsByTable(std::vector<Process> resultsVector);
};

