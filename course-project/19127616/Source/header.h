#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Function declarations
// Define the Element structure
struct Element
{
    int key;
    char index;
};
void bubbleSort(vector<Element> &arr);
void selectionSort(vector<Element> &arr);
void insertionSort(vector<Element> &arr);
void heapSort(vector<Element> &arr);
void quickSort(vector<Element> &arr, int low, int high);
void mergeSort(vector<Element> &arr, int l, int r);
void mergeSortWrapper(vector<Element> &arr);
void radixSort(vector<Element> &arr);
void countingSort(vector<Element> &arr);
void merge(vector<Element> &arr, int l, int m, int r);
void heapify(vector<Element> &arr, int n, int i);
int partition(vector<Element> &arr, int low, int high);

#endif // HEADER_H