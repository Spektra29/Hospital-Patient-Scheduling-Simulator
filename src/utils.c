#include <stdio.h>
#include "../include/scheduler.h"

// Simple swap helper
void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Sort patients by completion time (ascending)
void sort_by_completion(Patient patients[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (patients[j].completion > patients[j + 1].completion) {
                swap(&patients[j], &patients[j + 1]);
            }
        }
    }
}

void print_results(Patient patients[], int n, const char *title) {
    sort_by_completion(patients, n);  // Sort before printing

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
