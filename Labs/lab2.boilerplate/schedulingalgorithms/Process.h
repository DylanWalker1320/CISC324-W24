#ifndef PROCESS_H
#define PROCESS_H

struct Process
{
    int id;        // Process ID
    int burstTime; // CPU Burst Time
    int arrivalTime;
    int waitTime;
    int remainingTime;

    int completionTime; // For turnaround time calculation
    int startTime; // Used for RR: The time when the process is first executed
    int segmentTime = 0 ; // Used for RR: The total time the process has been executed, before the lastStartTime

    Process(int id, int burstTime) : id(id), burstTime(burstTime) {}
    Process(int id, int burstTime, int arrivalTime) : id(id), burstTime(burstTime), arrivalTime(arrivalTime) {}
};

#endif // PROCESS_H