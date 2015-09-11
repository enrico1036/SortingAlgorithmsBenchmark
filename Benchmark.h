
#ifndef Benchmark_h
#define Benchmark_h

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "SortingAlgorithms.h"

typedef enum {
    RANDOM = 0,
    ASCENDING = 1,
    DESCENDING = 2,
    FLAT = 3
} ArrayType;

typedef struct{
    void (*fun)(int*, int);
    char name[20];
} SortingAlgorithm;

// Populates the array based on ArrayType
void GenArray(int arr[], int n, ArrayType type);

// Returns TRUE if an array is correctly sorted
bool CheckSorted(int arr[], int n);

// Measures the time (in microseconds) used by the sorting algorithm alg
unsigned long MeasureMicroseconds(SortingAlgorithm alg, int v[], int n);

void FullBenchmarkCSV(char* filename, int max_size, int slow_max_size, int start_size, int size_mult);

void PrintArray(int arr[], int n);

#endif 
