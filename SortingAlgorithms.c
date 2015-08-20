
#include "SortingAlgorithms.h"
#include <string.h>

#define FALSE 0
#define TRUE 1
typedef int bool;

static inline void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void SelectionSort(int arr[], int n) {
    if(n<1) return;
    int min = 0;
    for(int i=0; i<n-1; i++)
    {
        min = i;
        for(int j=i+1; j<n; j++)
            if(arr[j] < arr[min])
                min = j;
        
        /*
         int tmp = arr[i];
         arr[i] = arr[min];
         arr[min] = tmp;
         */
        swap(&arr[i], &arr[min]);
    }
}

void QuickSort(int arr[], int n) {
    if(n<2) return;
    int i = 0;
    int j = n-1;
    while (i<j)
    {
        while (arr[j] > arr[0]) j--;
        while (arr[i] <= arr[0] && i <= j) i++;
        if(i < j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    swap(&arr[0], &arr[j]);
    QuickSort(arr, j);
    QuickSort(&arr[j+1], n-j-1);
}

void merge(int arr[], int left, int center, int right) {
    int tmp[right+1];
    int i = left;
    int j = center+1;
    int k = left;
    
    while (i<=center && j<=right)
    {
        if(arr[i]<=arr[j])
        {
            tmp[k] = arr[i];
            i++;
        }else{
            tmp[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i<=center)
    {
        tmp[k] = arr[i];
        i++;
        k++;
    }
    while (j<=right) {
        tmp[k] = arr[j];
        j++;
        k++;
    }
    memcpy(arr, tmp, (right+1)*sizeof(int));
}

void MergeSort(int arr[], int n) {
    if (n<=1) return;
    int center = (n)/2;
    MergeSort(arr, center);
    MergeSort(&arr[center], n-center);
    merge(arr, 0, center-1, n-1);
}



void BubbleSort(int arr[], int n){
    bool sorted = TRUE;
    while(!sorted)
    {
        sorted = TRUE;
        for (int i=0; i < n-1; i++)
        {
            if(arr[i+1] < arr[i])
            {
                swap(&arr[i+1], &arr[i]);
                sorted = FALSE;
            }
        }
    }   
}
