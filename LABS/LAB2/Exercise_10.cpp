#include <iostream>
using namespace std;

/**
 * Exercise 10. N-Queens Problem
 * 
 * Write a program to solve the N-Queens problem, which places n queens on an n × n chessboard
 * 
 * such that no two queens attack each other.
 * 
 * Input:
 * • An integer n (1 ≤ n ≤ 10) representing the size of the chessboard.
 * 
 * Output:
 * • A list of all possible valid solutions.
 * • Each solution should be represented as an n-length list, where the i-th number represents the column position of the queen in row i.
 * 
 * Example:
 * Input:
 * 4
 * 
 * Output:
 * [2, 4, 1, 3]
 * [3, 1, 4, 2]
 * 
 * 
 */

bool isSafe(int board[], int row, int col, int n)
{
    // Check the left side of the row
    for (int i = 0; i < col; i++)
    {
        if (board[i] == row)
        {
            return false; // There is a queen in the same row
        }
    }
    // Check the upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[j] == i)
        {
            return false; // There is a queen in the upper diagonal
        }
    }
    // Check the lower diagonal on the left side
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[j] == i)
        {
            return false; // There is a queen in the lower diagonal
        }
    }
    return true; // The position is safe for the queen
}

bool solveNQueens(int board[], int col, int n)
{
    if (col == n)
    {
        for (int i = 0; i < n; i++)
        {
            cout << board[i] + 1 << " "; // Print the solution
        }
        cout << endl;
        return true; // Found a solution
    }
    bool res = false;
    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col, n))
        {
            board[col] = i; // Place the queen at the current position
            res = solveNQueens(board, col + 1, n) || res; // Recur to place the rest of the queens
            board[col] = -1; // Backtrack and remove the queen from the current position
        }
    }
    return res; // Return whether a solution was found
}

int main()
{
    int n;
    cout << "Enter the size of the chessboard: ";
    cin >> n;
    int board[n];
    for (int i = 0; i < n; i++)
    {
        board[i] = -1; // Initialize the board with -1
    }
    solveNQueens(board, 0, n); // Solve the N-Queens problem

    return 0;
}
