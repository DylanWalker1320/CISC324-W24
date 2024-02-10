#ifndef FIRSTCOMEFIRSTSERVEDSCHEDULER_H
#define FIRSTCOMEFIRSTSERVEDSCHEDULER_H

#include <queue>
#include "Process.h"
#include "CPUScheduler.h"
using namespace std;

class FirstComeFirstServedScheduler : public CPUScheduler
{
private:
    int quantum;
    int avg_wait;
    int avg_turnaround;
    queue<Process> processes;

public:
    FirstComeFirstServedScheduler(const queue<Process>& pass_processes, int pass_quantum) {}
    void schedule() override;
    void calculateAverageWaitTime() override;
    void calculateAverageTurnAroundTime() override;
};

#endif
