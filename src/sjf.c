#include <limits.h>
#include "../include/scheduler.h"

void run_sjf(Patient p[], int n) {
    int completed = 0, time = 0;
    int done[n];

    for (int i = 0; i < n; i++) done[i] = 0;

    while (completed < n) {
        int idx = -1, min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].burst < min_burst) {
                min_burst = p[i].burst;
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
