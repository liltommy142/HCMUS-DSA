#include <iostream>
using namespace std;

/**
 * Exercise 9. Generate Binary Strings
 * 
 * Write a program to generate all binary strings of length n.
 * 
 * Input:
 * • An integer n (1 ≤ n ≤ 10) representing the length of the binary string.
 * 
 * Output:
 * • A list of all possible binary strings of length n, each on a new line.
 * 
 * Example:
 * 
 * Input:
 * 3
 * 
 * Output:
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 * 111
 * 
 * 
 */

void generateBinaryStrings(int n, string str)
{
    if (n == 0)
    {
        cout << str << endl;
        return;
    }
    generateBinaryStrings(n - 1, str + "0");
    generateBinaryStrings(n - 1, str + "1");
}

int main()
{
    int n;
    cout << "Enter the length of the binary string: ";
    cin >> n;
    generateBinaryStrings(n, "");

    return 0;
}