#include <iostream>
using namespace std;

// Function to input an array from the keyboard
void inputArray(int *&arr, int n)
{
    arr = new int[n];
    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
}

// Function to print an array
void printArray(int *arr, int n)
{
    cout << "Array elements: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to find the maximum value in an array
int findMax(int *arr, int n)
{
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

// Function to find the sum of array elements
int findSum(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

// Function to concatenate two arrays into a new array
void concatArrays(int *a, int na, int *b, int nb, int *&res, int &nres)
{
    nres = na + nb;
    res = new int[nres];
    for (int i = 0; i < na; i++)
    {
        res[i] = a[i];
    }
    for (int i = 0; i < nb; i++)
    {
        res[na + i] = b[i];
    }
}

// Function to find the longest ascending subarray
void findLongestAscendingSubarray(int *arr, int n, int *&res, int &nres)
{
    int maxLength = 1, start = 0;
    int currentLength = 1;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[i - 1])
        {
            currentLength++;
        }
        else
        {
            if (currentLength > maxLength)
            {
                maxLength = currentLength;
                start = i - currentLength;
            }
            currentLength = 1;
        }
    }

    if (currentLength > maxLength)
    {
        maxLength = currentLength;
        start = n - currentLength;
    }

    nres = maxLength;
    res = new int[nres];
    for (int i = 0; i < maxLength; i++)
    {
        res[i] = arr[start + i];
    }
}

int main()
{
    int *a;
    int *b;
    int *c;
    int *longestSubarray;
    int na, nb, nres;

    // Input array a
    cout << "Enter the number of elements in array a: ";
    cin >> na;
    inputArray(a, na);

    // Input array b
    cout << "Enter the number of elements in array b: ";
    cin >> nb;
    inputArray(b, nb);

    // Concatenate arrays a and b into c
    concatArrays(a, na, b, nb, c, nres);

    // Print the concatenated array
    printArray(c, nres);

    // Print the maximum value in array c
    cout << "Maximum value in the array: " << findMax(c, nres) << endl;

    // Print the sum of elements in array c
    cout << "Sum of elements in the array: " << findSum(c, nres) << endl;

    // Find and print the longest ascending subarray
    findLongestAscendingSubarray(c, nres, longestSubarray, nres);
    cout << "Longest ascending subarray: ";
    printArray(longestSubarray, nres);

    // Clean up dynamic memory
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] longestSubarray;

    return 0;
}
