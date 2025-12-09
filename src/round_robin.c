#include <limits.h>
#include "../include/scheduler.h"

void run_round_robin(Patient p[], int n, int quantum) {
    int time = 0;
    int remaining = n;

    // quantum must be at least 1 to make progress. If GUI or
    // input provided 0 (or negative), fall back to 1 to avoid infinite loops.
    if (quantum <= 0) {
        quantum = 1;
    }

    while (remaining > 0) {
        int progressed = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining_time > 0) {
                progressed = 1;

                if (p[i].remaining_time > quantum) {
                    time += quantum;
                    p[i].remaining_time -= quantum;
                } else {
                    time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    p[i].completion = time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    remaining--;
                }
            }
        }

        if (!progressed) {
            // No patient is ready yet. Jump to the next arrival time to avoid busy-wait.
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining_time > 0 && p[i].arrival > time) {
                    if (p[i].arrival < next_arrival) {
                        next_arrival = p[i].arrival;
                    }
                }
            }
            // Only jump if found a future arrival; otherwise increment by 1 (shouldn't happen)
            if (next_arrival != INT_MAX) {
                time = next_arrival;
            } else {
                time++;
            }
        }
    }
}
