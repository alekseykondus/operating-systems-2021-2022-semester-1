#pragma once
#include "Process.h"
#include "SchedulingAlgorithm.h"
#include <vector>
//#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Scheduling
{
public:
	Scheduling(unsigned int numberOfProcesses, unsigned int runtime, unsigned int quantum);
	void Run();
	void PrintResults();

private:
	unsigned int m_Runtime;
	unsigned int m_NumberOfProcesses;
	unsigned int m_Quantum;
	std::shared_ptr<Process> m_Head;
	std::vector < std::shared_ptr <Process >> m_ResultVector;
	SchedulingAlgorithm m_Algorithm;
	std::stringstream m_StreamResult;

	void CreateProcesses();
	void CenterAlign(const std::string& s, size_t width_field);
	void OutputByTable(std::vector<std::shared_ptr<Process>> resultsVector);

};

