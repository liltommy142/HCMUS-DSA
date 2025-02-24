#include <iostream>
#include <vector>
using namespace std;

// Function to sort the matrix elements in spiral order
void spiralSort(vector<vector<int>> &matrix)
{
    int m = matrix.size();    // Number of rows
    int n = matrix[0].size(); // Number of columns
    vector<int> elements;     // Vector to store matrix elements

    // Extract elements from the matrix into a 1D vector
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            elements.push_back(val);
        }
    }

    // Simple sorting without using prohibited libraries
    for (size_t i = 0; i < elements.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < elements.size(); ++j)
        {
            if (elements[i] > elements[j])
            {
                swap(elements[i], elements[j]);
            }
        }
    }

    // Fill the matrix back in spiral order
    int left = 0, right = n - 1, top = 0, bottom = m - 1, index = 0;
    while (left <= right && top <= bottom)
    {
        // Fill top row
        for (int i = left; i <= right && index < elements.size(); ++i)
        {
            matrix[top][i] = elements[index++];
        }
        ++top;

        // Fill right column
        for (int i = top; i <= bottom && index < elements.size(); ++i)
        {
            matrix[i][right] = elements[index++];
        }
        --right;

        // Fill bottom row
        for (int i = right; i >= left && index < elements.size(); --i)
        {
            matrix[bottom][i] = elements[index++];
        }
        --bottom;

        // Fill left column
        for (int i = bottom; i >= top && index < elements.size(); --i)
        {
            matrix[i][left] = elements[index++];
        }
        ++left;
    }
}

// Function to print the matrix
void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main()
{
    // Initialize the matrix
    vector<vector<int>> matrix = {
        {4, 3, 2, 1},
        {5, 14, 13, 12},
        {6, 15, 16, 11},
        {7, 8, 9, 10}};

    // Print the original matrix
    cout << "Original matrix:\n";
    printMatrix(matrix);

    // Sort the matrix in spiral order
    spiralSort(matrix);

    // Print the sorted matrix
    cout << "Sorted matrix:\n";
    printMatrix(matrix);

    return 0;
}
