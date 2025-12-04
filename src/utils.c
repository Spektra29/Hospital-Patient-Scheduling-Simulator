#include <stdio.h>
#include "../include/scheduler.h"

void print_results(Patient patients[], int n, const char *title) {
    printf("\n===== %s =====\n", title);
    printf("ID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               patients[i].id,
               patients[i].arrival,
               patients[i].burst,
               patients[i].priority,
               patients[i].waiting,
               patients[i].turnaround);
    }
}

void copy_patients(Patient dst[], Patient src[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
        dst[i].remaining_time = src[i].burst;
    }
}
