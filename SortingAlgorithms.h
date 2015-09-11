
#ifndef SortingAlgorithms_h
#define SortingAlgorithms_h

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define ALG_NUM 5

enum SortingAlgorithmID{
    SELECTION_SORT,
    QUICK_SORT,
    MERGE_SORT,
    BUBBLE_SORT,
    SHAKER_SORT
};

void SelectionSort(int arr[], int n);
void QuickSort(int arr[], int n);
void MergeSort(int arr[], int n);
void BubbleSort(int arr[], int n);
void ShakerSort(int arr[], int n);

#endif 
