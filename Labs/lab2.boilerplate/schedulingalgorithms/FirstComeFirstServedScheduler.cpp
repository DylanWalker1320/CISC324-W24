#include "FirstComeFirstServedScheduler.h"
#include "iostream"

FirstComeFirstServedScheduler::FirstComeFirstServedScheduler(const queue<Process> &pass_processes, int pass_quantum)
{
    std::queue<Process> p_copy;
    std::queue<Process> temp = pass_processes; // Create a temporary queue for iteration

    while (!temp.empty()) {
        p_copy.push(temp.front());  // Copy each element
        temp.pop();
    }

    processes = p_copy;
    quantum = pass_quantum;
}

void FirstComeFirstServedScheduler::schedule()
{
    // Implementation of FCFS scheduling
    
    
}

void FirstComeFirstServedScheduler::calculateAverageWaitTime()
{
    // Implementation of calculating average wait time
    
    float avg_waiting = 0;
    for (int i = 0; i < processes.size(); i++) {
        avg_waiting += processes.front().arrivalTime;
        cout << processes.front().arrivalTime;
        processes.pop();
    }
}

void FirstComeFirstServedScheduler::calculateAverageTurnAroundTime()
{
    // Implementation of calculating average turn around time
    throw "Not implemented"; // Remove this line
}