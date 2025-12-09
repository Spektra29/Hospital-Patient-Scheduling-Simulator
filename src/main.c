#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "utils.h"

// Helper: Load entire file into memory
char* load_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("ERROR: Cannot open file: %s\n", filename);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = (char*)malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    return buffer;
}

// Very simple parser for the GUI-generated JSON file
// Expects format: { "algorithm": "...", "quantum": 0, "patients": [...] }
int parse_input_file(const char* filename, char* algorithm, int* quantum, Patient** patients_out, int* n_out) {
    char* text = load_file(filename);
    *quantum = 0;
    *n_out = 0;

    // Get algorithm
    char* alg_ptr = strstr(text, "\"algorithm\"");
    if (!alg_ptr) { free(text); return 0; }
    sscanf(alg_ptr, "\"algorithm\": \"%[^\"]\"", algorithm);

    // Get quantum
    char* q_ptr = strstr(text, "\"quantum\"");
    if (q_ptr) {
        // `quantum` is an int* parameter; pass it directly to sscanf so the
        // parsed integer is written into the caller-provided location.
        sscanf(q_ptr, "\"quantum\": %d", quantum);
    }

    // Count patients
    int count = 0;
    char* p_ptr = strstr(text, "\"patients\"");
    if (!p_ptr) { free(text); return 0; }

    char* arr_ptr = strchr(p_ptr, '[');
    while (arr_ptr && *arr_ptr != ']') {
        if (strstr(arr_ptr, "{")) count++;
        arr_ptr++;
    }

    Patient* patients = malloc(sizeof(Patient) * count);

    // Parse patient entries
    arr_ptr = strchr(p_ptr, '[');
    int i = 0;
    while (arr_ptr && *arr_ptr != ']' && i < count) {
        char id[32];
        int arrival, burst, priority;

        char* brace = strstr(arr_ptr, "{");
        if (!brace) break;
        
        // Try to extract the values - be flexible with JSON format
        char* id_ptr = strstr(brace, "\"id\"");
        char* arrival_ptr = strstr(brace, "\"arrival\"");
        char* burst_ptr = strstr(brace, "\"burst\"");
        char* priority_ptr = strstr(brace, "\"priority\"");
        
        if (id_ptr && arrival_ptr && burst_ptr && priority_ptr) {
            sscanf(id_ptr, "\"id\": \"%[^\"]\"", id);
            sscanf(arrival_ptr, "\"arrival\": %d", &arrival);
            sscanf(burst_ptr, "\"burst\": %d", &burst);
            sscanf(priority_ptr, "\"priority\": %d", &priority);
            
            strcpy(patients[i].id, id);
            patients[i].arrival = arrival;
            patients[i].burst = burst;
            patients[i].priority = priority;
            patients[i].remaining_time = burst;
            i++;
        }
        arr_ptr = brace + 1;
    }

    *patients_out = patients;
    *n_out = i;
    free(text);
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  scheduler <input.json>\n");
        return 1;
    }

    char algorithm[32];
    int quantum;
    Patient* patients = NULL;
    int n = 0;

    if (!parse_input_file(argv[1], algorithm, &quantum, &patients, &n)) {
        printf("ERROR: Failed to parse input JSON.\n");
        return 1;
    }

    // Initialize all patients with zero values
    for (int i = 0; i < n; i++) {
        patients[i].completion = 0;
        patients[i].waiting = 0;
        patients[i].turnaround = 0;
        patients[i].remaining_time = patients[i].burst;
    }

    // Run the chosen algorithm
    if (strcmp(algorithm, "FCFS") == 0) {
        run_fcfs(patients, n);
    } else if (strcmp(algorithm, "SJF") == 0) {
        run_sjf(patients, n);
    } else if (strcmp(algorithm, "Priority") == 0) {
        run_priority(patients, n);
    } else if (strcmp(algorithm, "Round Robin") == 0) {
        run_round_robin(patients, n, quantum);
    } else {
        printf("ERROR: Unknown algorithm '%s'\n", algorithm);
        free(patients);
        return 1;
    }

    // Output JSON for Streamlit GUI
    output_json(patients, n);

    free(patients);
    return 0;
}
