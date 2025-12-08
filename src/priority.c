#include <limits.h>
#include "../include/scheduler.h"

void priority_schedule(Patient p[], int n) {
    int completed = 0;
    int time = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++)
        p[i].remaining_time = p[i].burst;

    // Aging parameters
    int aging_interval = 5;   // Every 5 units, increase priority of waiting patients
    int aging_amount = 1;     // Reduce priority number by 1 (more urgent)

    while (completed < n) {
        int idx = -1;
        int best_pri = INT_MAX;
        int earliest_arrival = INT_MAX;

        // Find ready patient with highest priority
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining_time > 0) {
                if (p[i].priority < best_pri ||
                    (p[i].priority == best_pri && p[i].arrival < earliest_arrival)) {
                    best_pri = p[i].priority;
                    idx = i;
                    earliest_arrival = p[i].arrival;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        // Run patient for 1 time unit
        p[idx].remaining_time--;
        time++;

        // Aging: increase priority of waiting patients periodically
        if (time % aging_interval == 0) {
            for (int i = 0; i < n; i++) {
                if (p[i].arrival <= time && p[i].remaining_time > 0 && i != idx) {
                    if (p[i].priority > 1)  // Don't go below 1
                        p[i].priority -= aging_amount;
                }
            }
        }

        // Patient finished
        if (p[idx].remaining_time == 0) {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }
    }
}
