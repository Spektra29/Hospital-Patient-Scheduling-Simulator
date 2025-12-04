#include <limits.h>
#include "../include/scheduler.h"

void priority_schedule(Patient p[], int n) {
    int completed = 0, time = 0;
    int done[n];

    for (int i = 0; i < n; i++) done[i] = 0;

    while (completed < n) {
        int idx = -1, best_pri = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].priority < best_pri) {
                best_pri = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;

        done[idx] = 1;
        completed++;
    }
}
