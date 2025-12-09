#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdio.h>

typedef struct {
    char id[20];
    int arrival;
    int burst;
    int priority;
    int remaining_time;

    int completion;
    int waiting;
    int turnaround;
} Patient;

/* Algorithm functions */
void fcfs(Patient patients[], int n);
void sjf(Patient patients[], int n);
void priority_schedule(Patient patients[], int n);
void round_robin(Patient patients[], int n, int quantum);

/* Utilities */
void print_results(Patient patients[], int n, const char *title);
void copy_patients(Patient dst[], Patient src[], int n);

// Add prototypes for all scheduling algorithms
void run_fcfs(Patient* patients, int n);
void run_sjf(Patient* patients, int n);
void run_priority(Patient* patients, int n);
void run_round_robin(Patient* patients, int n, int quantum);

#endif
