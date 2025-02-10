#include <iostream>
using namespace std;

/**
 * 
 * Exercise 4. Check Strictly Increasing Array
 * 
 * Write a program to determine whether a given array of integers is strictly increasing.
 * 
 * Input:
 * • An integer n (1 ≤ n ≤ 100), the number of elements in the array.
 * • A sequence of n integers (−106 ≤ ai ≤ 106).
 * 
 * Output:
 * • Yes if the array is strictly increasing.
 * • No otherwise.
 * 
 */

bool isStrictlyIncreasing(int arr[], int n)
{
    if (n == 1)
    {
        return true;
    }
    if (arr[n - 1] <= arr[n - 2])
    {
        return false;
    }
    return isStrictlyIncreasing(arr, n - 1);
}

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << (isStrictlyIncreasing(arr, n) ? "Yes" : "No") << endl;

    return 0;
}