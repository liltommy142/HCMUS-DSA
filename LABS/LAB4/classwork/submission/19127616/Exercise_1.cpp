#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;

// Function prototypes
void insertionSort(vector<int> &arr);
void selectionSort(vector<int> &arr);
void interchangeSort(vector<int> &arr);
double measureExecutionTime(void (*sortFunc)(vector<int> &), vector<int> arr);
double min(double a, double b);
double min(double a, double b, double c);
double max(double a, double b);
double max(double a, double b, double c);
vector<int> generateVector(int size);

int main()
{
    const int SIZE = 10000;
    vector<int> arr(SIZE);

    // Generate random values for the array
    arr = generateVector(SIZE);

    // Measure execution times
    double insertionSortTime = measureExecutionTime(insertionSort, arr);
    double selectionSortTime = measureExecutionTime(selectionSort, arr);
    double interchangeSortTime = measureExecutionTime(interchangeSort, arr);

    // Print execution times
    cout << "Insertion Sort Time: " << insertionSortTime << " seconds" << endl;
    cout << "Selection Sort Time: " << selectionSortTime << " seconds" << endl;
    cout << "Interchange Sort Time: " << interchangeSortTime << " seconds" << endl;

    // Determine and print the fastest and slowest algorithms
    double minTime = min(insertionSortTime, selectionSortTime, interchangeSortTime);
    double maxTime = max(insertionSortTime, selectionSortTime, interchangeSortTime);

    if (minTime == insertionSortTime)
    {
        cout << "The fastest algorithm: Insertion Sort" << endl;
    }
    else if (minTime == selectionSortTime)
    {
        cout << "The fastest algorithm: Selection Sort" << endl;
    }
    else
    {
        cout << "The fastest algorithm: Interchange Sort" << endl;
    }

    if (maxTime == insertionSortTime)
    {
        cout << "The slowest algorithm: Insertion Sort" << endl;
    }
    else if (maxTime == selectionSortTime)
    {
        cout << "The slowest algorithm: Selection Sort" << endl;
    }
    else
    {
        cout << "The slowest algorithm: Interchange Sort" << endl;
    }

    // Free the array
    arr.clear();

    return 0;
}

// Function to find the minimum of two values
double min(double a, double b)
{
    return a < b ? a : b;
}

// Function to find the minimum of three values
double min(double a, double b, double c)
{
    return min(min(a, b), c);
}

// Function to find the maximum of two values
double max(double a, double b)
{
    return a > b ? a : b;
}

// Function to find the maximum of three values
double max(double a, double b, double c)
{
    return max(max(a, b), c);
}

// Function to generate a vector of random integers
vector<int> generateVector(int size)
{
    vector<int> result;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 1000);
    for (int i = 0; i < size; ++i)
    {
        result.push_back(dis(gen));
    }
    return result;
}

// Function to sort an array using insertion sort
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to sort an array using selection sort
void selectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

// Function to sort an array using interchange sort
void interchangeSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[i] > arr[j])
            {
                swap(arr[i], arr[j]);
            }
        }
    }
}

// Function to measure the execution time of a sorting function
double measureExecutionTime(void (*sortFunc)(vector<int> &), vector<int> arr)
{
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}