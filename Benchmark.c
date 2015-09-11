#include "Benchmark.h"

SortingAlgorithm algorithms[ALG_NUM];
char arrtypes[3][20];

void GenArray(int arr[], int n, ArrayType type){
    switch(type)
    {
        case RANDOM:
            srand((unsigned ) time(NULL));
            for(int i=0; i<n; i++)
                arr[i] = 1 + rand()%(n + 1);
            break;
        case ASCENDING:
            for(int i=0; i<n; i++)
                arr[i] = i;
            break;            
        case DESCENDING:
            for(int i=0; i<n; i++)
                arr[i] = n-i-1;
            break;
        case FLAT:
            for(int i=0; i<n; i++)
                arr[i] = 1;
            break;
        default:
            break;
    }
}

unsigned long MeasureMicroseconds(SortingAlgorithm alg, int v[], int n){
    struct timeval start, stop;
    // Retrieve start time
    gettimeofday(&start, NULL);
    // Run the algorithm
    (*alg.fun)(v, n);
    // Retrieve stop time
    gettimeofday(&stop, NULL);
    // Return delta in microseconds
    return (unsigned long)(1e6 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec));
}

bool CheckSorted(int arr[], int n){
    for(int i=0; i<n-1; i++)
        if(arr[i] > arr[i+1])
            return false;
    return true;
}

void FullBenchmarkCSV(char* filename, int max_size, int slow_max_size, int start_size, int size_mult){
    // Write column titles
    FILE* fd = fopen(filename, "w+");
    fprintf(fd, "%s;%s;%s;%s;%s\n", 
    "Ordinamento iniziale" , 
    "Algoritmo", 
    "Dimensione array", 
    "Tempo esecuzione (us)", 
    "Corretto");
    
    int* ref_arr = (int*) malloc(sizeof(int) * max_size);
    int* sort_arr;
    
    for(int arr_type=0; arr_type<3; arr_type++){
        GenArray(ref_arr, max_size, arr_type);
        printf("%s\n", arrtypes[arr_type]);
        
        for(int sort_alg=0; sort_alg < ALG_NUM; sort_alg++){
            printf("   %s\n", algorithms[sort_alg].name);
            
            for(int i=start_size; i<=max_size; i *= size_mult){
                printf("        %d...", i);
                
                sort_arr = (int*) malloc(sizeof(int) * i);
                memcpy(sort_arr, ref_arr, sizeof(int) * i);
                
                unsigned long elapsed_time = MeasureMicroseconds(algorithms[sort_alg], sort_arr, i);
                
                bool correct = CheckSorted(sort_arr, i);
                free(sort_arr);
                
                // Write record
                fprintf(fd, "%s;%s;%d;%lu;%s\n", 
                arrtypes[arr_type], 
                algorithms[sort_alg].name, 
                i, 
                elapsed_time, 
                (correct) ? "Si" : "No");
                
                printf("Done.\n");
            }
        }
    }
    
    free(ref_arr);
    fclose(fd);
}

void PrintArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d\t", arr[i]);
    
    printf("\r\n");
}