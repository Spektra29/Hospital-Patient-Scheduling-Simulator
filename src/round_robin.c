#include "../include/scheduler.h"

void run_round_robin(Patient p[], int n, int quantum) {
    int time = 0;
    int remaining = n;

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
            time++;
        }
    }
}
