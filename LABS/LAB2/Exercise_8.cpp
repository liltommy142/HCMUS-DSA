#include <iostream>
#include <vector>
using namespace std;

/**
 *
 * Exercise 8. Generate Subsets
 *
 * Write a program to generate all subsets of a given set of distinct integers.
 *
 * Input:
 * • An integer n (1 ≤ n ≤ 10) representing the number of elements in the set.
 * • A sequence of n distinct integers.
 *
 * Output:
 * • A list of all possible subsets, each on a new line.
 * • The subsets should be sorted in lexicographical order.
 *
 * Example:
 * Input:
 * 3
 * 1 2 3
 *
 * Output:
 * {}
 * {1}
 * {2}
 * {3}
 * {1, 2}
 * {1, 3}
 * {2, 3}
 * {1, 2, 3}
 *
 *
 */

void generateSubsets(int nums[], int size, int start, vector<int> &subset)
{
    for (int i = start; i < size; i++)
    {
        subset.push_back(nums[i]);                  // Include the current element in the subset
        generateSubsets(nums, size, i + 1, subset); // Recur for the next element
        subset.pop_back();                          // Exclude the current element from the subset
    }
    cout << "{ ";
    for (int i = 0; i < subset.size(); i++)
    {
        cout << subset[i] << ", "; // Print the current subset
    }
    cout << "}" << endl;
}

int main()
{
    int n;
    cout << "Enter the number of elements in the set: ";
    cin >> n;
    int nums[n];
    cout << "Enter the elements of the set: ";
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    vector<int> subset;
    generateSubsets(nums, n, 0, subset);

    return 0;
}