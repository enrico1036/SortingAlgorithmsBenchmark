//
//  Algoritmi e Strutture dati
//
//  algoritmi di ordinamento
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortingAlgorithms.h"
#include <time.h>

/* Prints the array sequentially */
void PrintArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d\t", arr[i]);
    
    printf("\r\n");
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
    int vett[] = {5,5,5,1,5,83,7,113,46,8765,32,1,68,4}; // Static vector (just a try)
    int n = 14; // Number of elements in a vector
    char choose = 0;    // Used to store the user's choose
    PrintArray(vett, n);
    while (1)
    {
        printf("Select what algorithm you'd like to use: \r\n1 - SelectionSort\r\n2 - QuickSort\r\n3 - MergeSort\r\n4 - Bubblesort\r\n");
        scanf("%c", &choose);
        getchar();  // Discard the \n caused by Enter key
        switch (choose){
            case '1':
                SelectionSort(vett, n);
                break;
            case '2':
                QuickSort(vett, n);
                break;
            case '3':
                MergeSort(vett, n);
                break;
            case '4':
                BubbleSort(vett, n);
                break;
            case 'q':
                return 0;
                break;
                
            default:
                //printf("Please insert a number between 1 and 4!")
                printf("%d", choose);
                break;
        }
        PrintArray(vett, n);
    }
    return 0;
}
