#include <limits.h>
#include "../include/scheduler.h"

void priority_schedule(Patient p[], int n) {
    int completed = 0;
    int time = 0;
    int current_idx = -1;

    // Initialize remaining times
    for (int i = 0; i < n; i++)
        p[i].remaining_time = p[i].burst;

    // Aging parameters
    int aging_interval = 5;   // Every 5 units, increase priority of waiting patients
    int aging_amount = 1;     // Reduce priority number by 1 (more urgent)
    int last_aging_time = 0;

    while (completed < n) {
        int idx = -1;
        int best_pri = INT_MAX;
        int earliest_arrival = INT_MAX;

        // First pass: find minimum priority among ready patients
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining_time > 0) {
                if (p[i].priority < best_pri) {
                    best_pri = p[i].priority;
                }
            }
        }

        if (best_pri == INT_MAX) {
            // no ready patients
            time++;
            continue;
        }

        // If current running patient is among the best priority, keep it
        if (current_idx != -1 && p[current_idx].arrival <= time && p[current_idx].remaining_time > 0 && p[current_idx].priority == best_pri) {
            idx = current_idx;
        } else {
            // otherwise pick earliest-arrived patient with best_pri
            for (int i = 0; i < n; i++) {
                if (p[i].arrival <= time && p[i].remaining_time > 0 && p[i].priority == best_pri) {
                    if (idx == -1 || p[i].arrival < earliest_arrival) {
                        idx = i;
                        earliest_arrival = p[i].arrival;
                    }
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        // Execute selected patient for 1 time unit (preemptive)
        p[idx].remaining_time--;
        time++;
        current_idx = idx;

        // Aging: increase priority of waiting patients periodically (exclude current)
        if (time - last_aging_time >= aging_interval) {
            for (int i = 0; i < n; i++) {
                if (i == current_idx) continue;
                if (p[i].arrival <= time && p[i].remaining_time > 0) {
                    if (p[i].priority > 1)
                        p[i].priority -= aging_amount;
                }
            }
            last_aging_time = time;
        }

        // Patient finished
        if (p[idx].remaining_time == 0) {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
            current_idx = -1;
        }
    }
}

// Keep compatibility with callers using run_priority
void run_priority(Patient p[], int n) {
    priority_schedule(p, n);
}
