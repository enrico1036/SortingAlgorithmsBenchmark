//
//  Algoritmi e Strutture dati
//
//  algoritmi di ordinamento
//

#include <stdio.h>
#include "SortingAlgorithms.h"

void GenRandomArray(int* arr, unsigned int n, int minval, int maxval){
    srand((unsigned) time(NULL));
    for(int i=0; i<n; i++)
    {
        arr[i] = minval + rand()%(maxval-minval);
    }
}


void PrintArray(int arr[], int n) {
    for(int i=0; i<n; i++)
        printf("%d\t", arr[i]);
    
    printf("\r\n");
}

int main(int argc, const char * argv[]) {
    int vett[] = {5,5,5,1,5,83,7,113,46,8765,32,1,68,4};
    int n = 14;
    PrintArray(vett, n);
    MergeSort(vett, n);
    PrintArray(vett, n);
    return 0;
}
