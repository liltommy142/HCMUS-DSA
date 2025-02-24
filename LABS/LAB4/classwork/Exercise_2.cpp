#include <iostream>
#include <vector>
using namespace std;

// Function to sort the array in ascending order using bubble sort
void bubbleSortAscending(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to sort the array in descending order using bubble sort
void bubbleSortDescending(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] < arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to sort even numbers in ascending order and odd numbers in descending order
void sortEvenOdd(vector<int> &arr)
{
    vector<int> evens, odds;

    // Separate even and odd numbers
    for (int num : arr)
    {
        if (num % 2 == 0)
        {
            evens.push_back(num);
        }
        else
        {
            odds.push_back(num);
        }
    }

    // Sort even numbers in ascending order
    bubbleSortAscending(evens);

    // Sort odd numbers in descending order
    bubbleSortDescending(odds);

    // Merge sorted even and odd numbers back into the original array
    int evenIndex = 0, oddIndex = 0;
    for (int &num : arr)
    {
        if (num % 2 == 0)
        {
            num = evens[evenIndex++];
        }
        else
        {
            num = odds[oddIndex++];
        }
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    // Sort the array with even numbers in ascending order and odd numbers in descending order
    sortEvenOdd(arr);

    // Print the sorted array
    cout << "Sorted array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}