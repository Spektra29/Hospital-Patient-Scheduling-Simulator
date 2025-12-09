#ifndef UTILS_H
#define UTILS_H

#include "scheduler.h"

// Function to output results in JSON for GUI
void output_json(Patient patients[], int n);

// Optional helpers
void swap(Patient *a, Patient *b);
void sort_by_completion(Patient patients[], int n);
void print_results(Patient patients[], int n, const char *title);
void copy_patients(Patient dst[], Patient src[], int n);

#endif
