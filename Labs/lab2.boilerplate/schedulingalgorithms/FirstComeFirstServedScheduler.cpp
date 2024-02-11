#include "FirstComeFirstServedScheduler.h"
#include <queue>

FirstComeFirstServedScheduler::FirstComeFirstServedScheduler(const queue<Process> &pass_processes, int pass_quantum)
{
    processes = pass_processes;
    quantum = pass_quantum;
}

void processInsertionSort(std::vector<Process>& arr) {
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

void FirstComeFirstServedScheduler::schedule()
{
    // Implementation of FCFS scheduling

    // Reorder the queue so its in order of arrival time.
    int size = processes.size();
    vector<Process> temp;
    for (int i = 0; i < size; i++) {
        Process p = processes.front();
        temp.push_back(p);
        processes.pop();
    }

    processInsertionSort(temp);

    for (int i = 0; i < size; i++) {
        Process p = temp[size - i - 1];
        processes.push(p);
    }
    
    int time = 0;
    for (int i = 0; i < size; i++) {
        Process p = processes.front();
        //cout << "Processing pid: " << p.id << " - arrival time: " << p.arrivalTime << " burst time: " << p.burstTime << endl;
        p.remainingTime = 0;
        p.completionTime = time + p.burstTime;
        p.waitTime = time - p.arrivalTime;
        time += p.burstTime;
        processes.pop();
        processes.push(p);
    }
    
}

void FirstComeFirstServedScheduler::calculateAverageWaitTime()
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

void FirstComeFirstServedScheduler::calculateAverageTurnAroundTime()
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
