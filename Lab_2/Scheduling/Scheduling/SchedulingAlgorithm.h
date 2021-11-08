#pragma once
#include "Process.h"
//#include <iostream>
#include <vector>
#include <sstream>

class SchedulingAlgorithm
{
public:
	std::vector<std::shared_ptr<Process>> RoundRobin(std::shared_ptr<Process> head, std::vector<std::shared_ptr<Process>>& result,
													 unsigned int quantum, unsigned int runTime, unsigned int numberOfProcesses, std::stringstream& streamResult);

private:
	std::shared_ptr<Process> CreateCopyOfProcessesForRR(std::shared_ptr<Process> head);
};

