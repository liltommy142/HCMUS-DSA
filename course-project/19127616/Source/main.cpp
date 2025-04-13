#include <iostream>
#include <vector>
#include <string>
#include "header.h"

using namespace std;

void printArray(const vector<Element> &arr)
{
    for (const auto &elem : arr)
    {
        cout << "{" << elem.key << "; " << elem.index << "} ";
    }
    cout << endl;
}

int main()
{
    vector<Element> arr = {{3, 'A'}, {1, 'B'}, {3, 'C'}, {2, 'D'}};
    cout << "Original array: ";
    printArray(arr);
    cout << endl;

    // test bubble sort
    bubbleSort(arr);
    cout << "Sorted array using Bubble Sort: ";
    printArray(arr);
    cout << endl;

    // Pause the console to keep it open
    system("pause");

    return 0;
}