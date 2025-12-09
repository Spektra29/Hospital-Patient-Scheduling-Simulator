#include <stdio.h>
#include <stdlib.h>
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
        printf("%s\t%d\t%d\t%d\t\t%d\t%d\n",
               patients[i].id,     // Changed %d -> %s
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

void output_json(Patient patients[], int n) {
    // Create a copy and sort by completion time for execution order
    Patient* sorted = malloc(sizeof(Patient) * n);
    for (int i = 0; i < n; i++) {
        sorted[i] = patients[i];
    }
    sort_by_completion(sorted, n);

    printf("{\n");
    printf("  \"order\": [");
    for (int i = 0; i < n; i++) {
        printf("\"%s\"%s", sorted[i].id, i < n - 1 ? ", " : "");
    }
    printf("],\n");

    printf("  \"waiting_times\": {");
    for (int i = 0; i < n; i++) {
        printf("\"%s\": %d%s", patients[i].id, patients[i].waiting, i < n - 1 ? ", " : "");
    }
    printf("},\n");

    printf("  \"turnaround_times\": {");
    for (int i = 0; i < n; i++) {
        printf("\"%s\": %d%s", patients[i].id, patients[i].turnaround, i < n - 1 ? ", " : "");
    }
    printf("},\n");

    double total_wait = 0, total_turn = 0;
    for (int i = 0; i < n; i++) {
        total_wait += patients[i].waiting;
        total_turn += patients[i].turnaround;
    }

    printf("  \"avg_waiting\": %.2f,\n", total_wait / n);
    printf("  \"avg_turnaround\": %.2f\n", total_turn / n);
    printf("}\n");
    
    free(sorted);
}
