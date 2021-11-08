#pragma once
#include "Process.h"
//#include <iostream>
#include <vector>
#include <sstream>

class SchedulingAlgorithm
{
public:
	std::vector<Process> RoundRobin(std::vector<Process> processesVector, std::vector<Process>& result,
													 unsigned int quantum, unsigned int runTime, std::stringstream& streamResult);
};

