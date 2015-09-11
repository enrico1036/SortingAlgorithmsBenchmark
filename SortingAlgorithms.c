#include "SortingAlgorithms.h"
#include <string.h>

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
        swap(&arr[i], &arr[min]);
    }
}

void QuickSort(int arr[], int n) {
    if(n<2) return;
    int i = -1;
    int j = n;
    int p = arr[(n-1)/2];
    
    while (true)
    {
        do { j--; } while ( arr[j] > p);
        do { i++; } while ( arr[i] < p);
        if(i < j)
            swap(&arr[i], &arr[j]);
        else
            break;
    }
    
    QuickSort(arr, j+1);
    QuickSort(&arr[j+1], n-j-1);
}

// Merge's temporary array
int* tmp_arr;

void merge(int arr[], int left, int center, int right) {
    int i = left;
    int j = center+1;
    int k = left;

    while (i<=center && j<=right)
    {
        if(arr[i]<=arr[j])
        {
            tmp_arr[k] = arr[i];
            i++;
        }else{
            tmp_arr[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i<=center)
    {
        tmp_arr[k] = arr[i];
        i++;
        k++;
    }
    while (j<=right) {
        tmp_arr[k] = arr[j];
        j++;
        k++;
    }
    memcpy(arr, tmp_arr, (right+1)*sizeof(int));
}

void rec_merge_sort(int arr[], int n){
    if (n<=1) return;
    int center = (n)/2;
    rec_merge_sort(arr, center);
    rec_merge_sort(&arr[center], n-center);
    merge(arr, 0, center-1, n-1);
}

void MergeSort(int arr[], int n) {
    tmp_arr = (int*) malloc(sizeof(int) * n);
    rec_merge_sort(arr, n);
    free(tmp_arr);
}


void BubbleSort(int arr[], int n){
    bool sorted = false;

    while(!sorted)
    {
        sorted = true;
        for (int i=0; i < n-1; i++)
        {
            if(arr[i+1] < arr[i])
            {
                swap(&arr[i+1], &arr[i]);
                sorted = false;
            }
        }
    }
}

void ShakerSort(int arr[], int n){
    bool sorted = false;
    bool descending = true;
    
    while(!sorted)
    {
        sorted = true;
        if(descending){
            for (int i=0; i < n-1; i++){
                if(arr[i+1] < arr[i]){
                    swap(&arr[i+1], &arr[i]);
                    sorted = false;
                }
            }
        }
        else {
            for (int i=n-1; i > 0; i--){
                if(arr[i-1] > arr[i]){
                    swap(&arr[i-1], &arr[i]);
                    sorted = false;
                }
            }
        }
        
        descending = !descending;
    }
}


