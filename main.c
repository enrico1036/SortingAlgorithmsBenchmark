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

/* Prints the array sequentially */
void PrintArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d\t", arr[i]);
    
    printf("\r\n");
}

/* Measures the time (in microseconds) used by the sorting algorithm alg */ 
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

/* Returns TRUE if an array is correctly sorted */
bool CheckSorted(int arr[], int n){
    for(int i=0; i<n-1; i++)
        if(arr[i] > arr[i+1])
            return FALSE;
    return TRUE;
}

/* Automatically generates a random array of n elements included between minval and maxval */
void GenRandomArray(int* arr, unsigned int n, int minval, int maxval){
    srand((unsigned) time(NULL));
    for(int i=0; i<n; i++)
    {
        arr[i] = minval + rand()%(maxval-minval);
    }
}

int main(int argc, const char * argv[]) {
    // Variables
    unsigned int n = 100000;                    // Number of elements in the array
    int* arr = (int*) malloc(n * sizeof(int));  // Integer array
    char choice = 0;                            // Used to store the user's choice
    // Flags
    bool print = FALSE;                         // The program outputs sorted array when TRUE    
    bool varsize = FALSE;                       // The user has to manually input array size
    
    // Handle arguments
    for(int i=0; i<argc; i++){
        if(strcmp("print", argv[i]) == 0){
            print = TRUE;
        }
        else
        if(strcmp("varsize", argv[i]) == 0){
            varsize = TRUE;
        }
        else
        if(strcmp("help", argv[i]) == 0){
            printf("Add argument 'print' to output both unsorted and sorted arrays.\n");
            printf("Add argument 'varsize' to manually input array size.\n");
            printf("Default array size is 1e6, and it is randomly generated with numbers in range [1,size].\n");
            return 0;
        }
    }
    
    // Main loop
    while (TRUE)
    {
        unsigned long elapsed_time = 0;
        
        // Fill the array with random numbers
        printf("Generating array of size %d...\r\n", n);
        GenRandomArray(arr, n, 1, n);
        
        // Print unsorted array
        if(print){
            printf("Unsorted array:\r\n");
            PrintArray(arr, n);    
        }
        
        // User chooses sorting algorithm
        printf("Select what algorithm you'd like to use: \r\n1 - SelectionSort\r\n2 - QuickSort\r\n3 - MergeSort\r\n4 - Bubblesort\r\n");
        scanf("%c", &choice);
        getchar();  // Discard the \n caused by Enter key
        
        // User inputs array size
        if(varsize){
            printf("Insert array size (positive integer): ");
            scanf("%du", &n);
            getchar();
        }
        
        switch (choice){
            case '1':
                elapsed_time = MeasureMicroseconds(SelectionSort, arr, n);
                break;
            case '2':
                elapsed_time = MeasureMicroseconds(QuickSort, arr, n);
                break;
            case '3':
                elapsed_time = MeasureMicroseconds(MergeSort, arr, n);
                break;
            case '4':
                elapsed_time = MeasureMicroseconds(BubbleSort, arr, n);
                break;
            case 'q':
                printf("Exit\r\n");
                return 0;
                
            default:
                printf("%d", choice);
                continue;
        }
        
                    
        // Print sorted array
        if(print){
            printf("Sorted array:\r\n");
            PrintArray(arr, n);    
        }
        
        // Print sort results
        printf("Time elapsed: %lu microseconds (%f seconds)\r\n", elapsed_time, (double)(elapsed_time / 1e6) );
        printf("Array%scorrectly sorted.\r\n", (CheckSorted(arr,n)) ? " " : " not ");

        // Wait for a key then repeat
        getchar();
        printf("\t##########\t\r\n\n");
    }
    
    free(arr);
    return 0;
}
