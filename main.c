//
//  Algoritmi e Strutture dati
//
//  algoritmi di ordinamento
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortingAlgorithms.h"
#include <sys/time.h>
#include <string.h>

/* Generates a random array of n elements included between minval and maxval */
void GenRandomArray(int* arr, unsigned int n, int minval, int maxval);
/* Generates an array of n elements in ascending order */
void GenAscendingArray(int* arr, unsigned int n);
/* Generates an array of n elements in descending order */
void GenDescendingArray(int* arr, unsigned int n);
/* Generates a flat array */
void GenFlatArray(int* arr, unsigned int n);

/* Returns TRUE if an array is correctly sorted */
bool CheckSorted(int arr[], int n);
/* Measures the time (in microseconds) used by the sorting algorithm alg */ 
unsigned long MeasureMicroseconds(void (*alg)(int*, int), int v[], int n);
/* Prints the array sequentially */
void PrintArray(int arr[], int n);
/* Performs a full benchmark of every algorithm in different conditions
   Then exports the results into a csv file */
void FullBenchmark(char* filename);

extern int* merge_tmp;  // merge temporary array (see SortingAlgorithms.c)

int main(int argc, const char * argv[]) {
    // Variables
    int n = 100000;                    // Number of elements in the array
    int* arr;                                   // Integer array
    char choice = 0;                            // Used to store the user's choice
    // Flags
    bool print = FALSE;                         // The program outputs sorted array when TRUE
    
    // Handle arguments
    for(int i=0; i<argc; i++){
        if(strcmp("print", argv[i]) == 0){
            print = TRUE;
        }
        else
        if(strcmp("varsize", argv[i]) == 0){
            sscanf(argv[++i], "%d", &n);
        }
        else
        if(strcmp("help", argv[i]) == 0){
            printf("Add argument 'print' to output both unsorted and sorted arrays.\n");
            printf("Add argument 'size' followed by positive integer to manually set array size.\n");
            printf("Default array has size 1e5, and it is initialized with random numbers in range [1,size].\n");
            return 0;
        }
    }
    
    // Main loop
    while (TRUE)
    {
        unsigned long elapsed_time = 0;

        // User chooses sorting algorithm
        printf("Select what algorithm you'd like to use: \r\n");
        printf("\t1 - SelectionSort\t");
        printf("4 - BubbleSort\r\n");
        printf("\t2 - QuickSort\t\t");
        printf("5 - CocktailSort\r\n");
        printf("\t3 - MergeSort\t\t");
        printf("q - Exit\r\n");
        
        scanf("%c", &choice);
        getchar();  // Discard the \n caused by Enter key
        if(choice == 'q') exit(0);
        
        // Fill the array with random numbers
        printf("Generating array of size %d (%.3f MB)...", n, (double)n*sizeof(int)/8.0e6F);
        arr = (int*) malloc(n * sizeof(int));
        GenRandomArray(arr, n, 1, n);
        printf("Done.\r\nExecuting...\r\n");
        
        // Print unsorted array
        if(print){
            printf("Unsorted array:\r\n");
            PrintArray(arr, n);    
        }
        
        switch (choice){
            case '1':
                elapsed_time = MeasureMicroseconds(SelectionSort, arr, n);
                break;
            case '2':
                elapsed_time = MeasureMicroseconds(QuickSort, arr, n);
                break;
            case '3':
                merge_tmp = (int*) malloc(n * sizeof(int));
                elapsed_time = MeasureMicroseconds(MergeSort, arr, n);
                free(merge_tmp);
                break;
            case '4':
                elapsed_time = MeasureMicroseconds(BubbleSort, arr, n);
                break;
            case '5':
                elapsed_time = MeasureMicroseconds(CocktailSort, arr, n);
                break;
             
            default:
                printf("%d", choice);
                break;
        }
        
                    
        // Print sorted array
        if(print){
            printf("Sorted array:\r\n");
            PrintArray(arr, n);    
        }
        
        // Print sort results
        printf("Time elapsed: %lu microseconds (%f seconds)\r\n", elapsed_time, (double)(elapsed_time / 1e6) );
        printf("Array%scorrectly sorted.\r\n", (CheckSorted(arr,n)) ? " " : " not ");
        
        // Free arrays
        free(arr);
        
        // Wait for a key then repeat
        getchar();
        printf("\t##########\t\r\n\n");
    }
    return 0;
}

void FullBenchmark(char* filename){
    FILE* fd = fopen(filename, "w+");
    // Write column titles
    fprintf(fd, "%s;%s;%s;%s;%s\r\n", 
    "Algoritmo", 
    "Dimensione array", 
    "Ordinamento iniziale" , 
    "Tempo esecuzione (us)", 
    "Corretto");
}

void PrintArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d\t", arr[i]);
    
    printf("\r\n");
}

unsigned long MeasureMicroseconds(void (*alg)(int*, int), int v[], int n){
    struct timeval start, stop;
    // Retrieve start time
    gettimeofday(&start, NULL);
    // Run the algorithm
    (*alg)(v, n);
    // Retrieve stop time
    gettimeofday(&stop, NULL);
    // Return delta in microseconds
    return (unsigned long)(1e6 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec));
}

bool CheckSorted(int arr[], int n){
    for(int i=0; i<n-1; i++)
        if(arr[i] > arr[i+1])
            return FALSE;
    return TRUE;
}

void GenRandomArray(int* arr, unsigned int n, int minval, int maxval){
    srand((unsigned) time(NULL));
    for(int i=0; i<n; i++)
    {
        arr[i] = minval + rand()%(maxval-minval + 1);
    }
}

void GenAscendingArray(int* arr, unsigned int n){
    for (int i=0; i<n; i++)
        arr[i] = i;
}

void GenDescendingArray(int* arr, unsigned int n){
    for(int i=0; i<n; i++)
        arr[i] = n-i-1;
}

void GenFlatArray(int* arr, unsigned int n){
    for(int i=0; i<n; i++)
        arr[i] = 1;
}

