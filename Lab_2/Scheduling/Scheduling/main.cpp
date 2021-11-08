#include "Scheduling.h"
#include <iostream>

/* Scheduling Simulation*/
int main(void) {

    Scheduling scheduling(5, 1000, 10);
    std::cout << "Working..." << std::endl;
    scheduling.Run();
    scheduling.PrintResults();
    std::cout << "Completed" << std::endl;
};