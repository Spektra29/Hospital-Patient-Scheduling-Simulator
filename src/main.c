#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

int main() {
    int n;
    printf("Enter number of patients: ");
    scanf("%d", &n);

    Patient *patients = malloc(sizeof(Patient) * n);
    Patient *backup = malloc(sizeof(Patient) * n);

    for (int i = 0; i < n; i++) {
        patients[i].id = i + 1;

        printf("\nPatient %d arrival time: ", i + 1);
        scanf("%d", &patients[i].arrival);

        printf("Patient %d burst time: ", i + 1);
        scanf("%d", &patients[i].burst);

        printf("Patient %d priority (lower = more urgent): ", i + 1);
        scanf("%d", &patients[i].priority);

        patients[i].remaining_time = patients[i].burst;
    }

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\n");
    int choice;
    scanf("%d", &choice);

    copy_patients(backup, patients, n);

    switch (choice) {
        case 1:
            fcfs(backup, n);
            print_results(backup, n, "FCFS Scheduling");
            break;

        case 2:
            sjf(backup, n);
            print_results(backup, n, "SJF Scheduling");
            break;

        case 3:
            priority_schedule(backup, n);
            print_results(backup, n, "Priority Scheduling");
            break;

        case 4: {
            int q;
            printf("Enter quantum: ");
            scanf("%d", &q);
            round_robin(backup, n, q);
            print_results(backup, n, "Round Robin Scheduling");
            break;
        }

        default:
            printf("Invalid choice!\n");
    }

    free(patients);
    free(backup);

    return 0;
}
