#include "Scheduling.h"
#include <iostream>

/* Scheduling Simulation*/
int main(void) {

    Scheduling scheduling(100, 10000, 7, 50, 23);
    std::cout << "Working..." << std::endl;
    scheduling.Run();
    scheduling.PrintResults();
    std::cout << "Completed" << std::endl;
};