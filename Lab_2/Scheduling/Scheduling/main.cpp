#include "Scheduling.h"
#include <iostream>

/* Scheduling Simulation*/
int main(void) {

    Scheduling scheduling(3, 12, 3, 5, 2);
    std::cout << "Working..." << std::endl;
    scheduling.Run();
    scheduling.PrintResults();
    std::cout << "Completed" << std::endl;
}