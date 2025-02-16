#include <iostream>
using namespace std;

/**
 * Exercise 7. Generate Permutations
 *
 * Write a program to generate all permutations of a given set of distinct integers.
 *
 * Input:
 * • An integer n (1 ≤ n ≤ 10) representing the number of elements in the set.
 * • A sequence of n distinct integers.
 *
 * Output:
 * • A list of all possible permutations of the given set, each on a new line.
 *
 * Example:
 * Input:
 * 3
 * 1 2 3
 *
 * Output:
 * 1 2 3
 * 1 3 2
 * 2 1 3
 * 2 3 1
 * 3 2 1
 * 3 1 2
 *
 *                 1 2 3
 *               /   |   \
 *              /    |    \
 *             /     |     \
 *            /      |      \
 *           /       |       \
 *          /        |        \
 *     2 1 3       2 3 1      3 1 2
 *     / | \       / | \      / | \
 *    /  |  \     /  |  \    /  |  \
 *   3 1 2  3    2 1  1 2   3  1 3 2
 *
 *
 */

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void generatePermutations(int nums[], int size, int start)
{
    if (start == size)
    {
        for (int i = 0; i < size; i++)
        {
            cout << nums[i] << " "; // Print the current permutation
        }
        cout << endl;
        return;
    }
    for (int i = start; i < size; i++)
    {
        swap(nums[start], nums[i]);                  // Swap the current element with the start element
        generatePermutations(nums, size, start + 1); // Recursively generate permutations for the next element
        swap(nums[start], nums[i]);                  // Backtrack to restore the original array
    }
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int *elements = new int[n]; // Dynamically allocate an array of size n
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> elements[i]; // Read the elements into the array
    }

    generatePermutations(elements, n, 0); // Generate all permutations of the array

    delete[] elements; // Free the dynamically allocated memory
    return 0;
}
