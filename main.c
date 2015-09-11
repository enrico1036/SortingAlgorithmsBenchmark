//
//  Algoritmi e Strutture dati
//
//  algoritmi di ordinamento
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
#include "SortingAlgorithms.h"
#include "Benchmark.h"

extern SortingAlgorithm algorithms[ALG_NUM];
extern char arrtypes[3][20];

int main(int argc, const char * argv[]) {
    // This array contains the list of algorithms in exam
    // Made this to make benchmarking procedure more readable
    algorithms[SELECTION_SORT] =    (SortingAlgorithm){SelectionSort, "Selection Sort"};
    algorithms[QUICK_SORT] =        (SortingAlgorithm){QuickSort, "Quick Sort"};
    algorithms[MERGE_SORT] =        (SortingAlgorithm){MergeSort, "Merge Sort"};
    algorithms[BUBBLE_SORT] =       (SortingAlgorithm){BubbleSort, "Bubble Sort"};
    algorithms[SHAKER_SORT] =       (SortingAlgorithm){ShakerSort, "Shaker Sort"};
    
    // The same for initial array types
    strcpy(arrtypes[RANDOM], "Random");
    strcpy(arrtypes[ASCENDING], "Ascending");
    strcpy(arrtypes[DESCENDING], "Descending");
    
    // Variables
    unsigned int size = 10000;                  // Number of elements in the array
    unsigned int slowsize = 10000;              // Max number of elements for slower algorithms (only benchmark)
    int* arr;                                   // Integer array
    // Flags
    char choice = 0;                            // Used to store the user's choice
    bool print = false;                         // The program outputs sorted array when true 
    bool benchmark = false;                     // Start full benchmark
    ArrayType arr_type = RANDOM;                // Default initial array type
    
    // Handle arguments
    for(int i=0; i<argc; i++){
        if(strcmp("print", argv[i]) == 0){
            print = true;
        }
        else
        if(strcmp("size", argv[i]) == 0){
            sscanf(argv[++i], "%d", &size);
        }
        else
        if(strcmp("benchmark", argv[i]) == 0){
            benchmark = true;
        }
        else
        if(strcmp("slowsize", argv[i]) == 0){
             sscanf(argv[++i], "%d", &slowsize);
        }
        else
        if(strcmp("arrtype", argv[i]) == 0){
             i++;
             if(strcmp("random", argv[i]) == 0)
                 arr_type = RANDOM;
             else
             if(strcmp("ascending", argv[i]) == 0)
                 arr_type = ASCENDING;
             else
             if(strcmp("descending", argv[i]) == 0)
                 arr_type = DESCENDING;
        }
        else
        if(strcmp("help", argv[i]) == 0){
            printf("Add argument 'print' to output both unsorted and sorted arrays.\n");
            printf("Add argument 'size <number>' to manually set array size.\n");
            printf("Add argument 'benchmark' to start automatic benchmark.\n");
            printf("Add argument 'slowsize <number>' to specify max size for slower algorithms (only for benchmark).\n");
            printf("Default array has size 1e5, and it is initialized with random numbers in range [1,size].\n");
            exit(0);
        }
    }
    
    // Enter benchmark
    if(benchmark){
        if(size < 2) exit(0);
        
        FullBenchmarkCSV("benchmark.csv", size, slowsize, 10, 10);
        exit(0);
    }
    
    // Main loop
    while (true)
    {
        unsigned long elapsed_time = 0;
        
        // Fill the array with random numbers
        printf("Generating array of size %d...\r\n", size);
        arr = (int*) malloc(sizeof(int) * size);
        GenArray(arr, size, arr_type);
        
        // Print unsorted array
        if(print){
            printf("Unsorted array:\r\n");
            PrintArray(arr, size);    
        }
        
        // User chooses sorting algorithm
        printf("Select algorithm:\n");
        for(int i = 0; i < ALG_NUM; i++){
            printf("    %d - %s\n", i, algorithms[i].name);
        }
        printf("    q - Exit\n");
        scanf("%c", &choice);
        getchar();  // Discard the \n caused by Enter key
        
        if(choice == 'q'){
            break;
        } 
        else {
            enum SortingAlgorithmID id;
            sscanf(&choice, "%d", &id);
            elapsed_time = MeasureMicroseconds(algorithms[id], arr, size);
        }
                    
        // Print sorted array
        if(print){
            printf("Sorted array:\r\n");
            PrintArray(arr, size);    
        }
        
        // Print sort results
        printf("Time elapsed: %lu microseconds (%f seconds)\r\n", elapsed_time, (double)(elapsed_time / 1e6) );
        printf("Array%scorrectly sorted.\r\n", (CheckSorted(arr, size)) ? " " : " not ");

        printf("    ###############    \r\n\n");
    }
    
    free(arr);
    return 0;
}
