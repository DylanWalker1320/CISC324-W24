#include "RoundRobinScheduler.h"
#include "iostream"

RoundRobinScheduler::RoundRobinScheduler(const queue<Process>& pass_processes, int pass_quantum)
{
    processes = pass_processes;
    quantum = pass_quantum;
}

void rrProcessInsertionSort(std::vector<Process>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; ++i) {
        Process key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are less than key to one position ahead of their current position
        while (j >= 0 && arr[j].arrivalTime < key.arrivalTime) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

bool allFinished(std::queue<Process> ps) {
    size_t size = ps.size();
    for (int i = 0; i < size; i++) {
        Process p = ps.front();
        if (p.remainingTime > 0) {
            return false;
        }
        ps.push(p);
        ps.pop();
    }
    return true;
}

/// @brief This function schedules the processes in the queue
/// @details This function schedules the processes in the queue using the Round Robin scheduling algorithm
void RoundRobinScheduler::schedule()
{
    // --Sort the queue--
    int size = processes.size();
    vector<Process> temp;
    for (int i = 0; i < size; i++) {
        Process p = processes.front();
        p.remainingTime = p.burstTime;
        p.waitTime = 0;
        temp.push_back(p);
        processes.pop();
    }

    rrProcessInsertionSort(temp);

    for (int i = 0; i < size; i++) {
        Process p = temp[size - i - 1];
        processes.push(p);
    }

    // --Begin the algorithm--
    int time = 0;
    
    while (!allFinished(processes)) {
        Process p = processes.front();

        if (p.remainingTime > 0) { 
            // Ensure remaining time is non-negative
            int b_time = min(p.remainingTime, quantum);

            // Increment segment time if we know we are going to run this process again
            if (p.remainingTime > quantum) { p.segmentTime += quantum; }

            // If the process has not been run yet, set its start time
            if (p.remainingTime == p.burstTime) { p.startTime = time; }

            p.remainingTime -= b_time;

            // If the process is finished, calculate the wait time and set its completion time
            if (p.remainingTime == 0) {
                p.waitTime = time - p.startTime - p.segmentTime;
                p.completionTime = time + b_time;
            }

            // Increment the clock
            time += b_time;
        }

        // Cycle through the queue
        processes.push(p);
        processes.pop();
    }
}

/// @brief This function calculates the average wait time of the processes
/// @details This function calculates the average wait time of the processes in the queue
void RoundRobinScheduler::calculateAverageWaitTime()
{
    // Implementation of calculating average wait time
    float sum = 0;
    float size = static_cast<float>(processes.size()); // FLAG: if this dosent work check this 

    for (int i = 0; i < size; i++) {
        Process p = processes.front();
        sum += p.waitTime;
        processes.pop();
        processes.push(p);
    }

    cout << "Average wait time: " << sum / size << endl;
}

/// @brief This function calculates the average turn around time of the processes
/// @details This function calculates the average turn around time of the processes in the queue
void RoundRobinScheduler::calculateAverageTurnAroundTime()
{
    // Implementation of calculating average turn around time
    float sum = 0;
    float size = static_cast<float>(processes.size()); // Cast to a float for decimal values

    for (int i = 0; i < size; i++) {
        Process p = processes.front();
        sum += p.completionTime - p.arrivalTime;
        processes.pop();
        processes.push(p);
    }

    cout << "Average turn around time: " << sum / size << endl;
}