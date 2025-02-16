#include <iostream>
using namespace std;

/**
 * Exercise 2. Sum of Digits
 *
 * Write a program to compute the sum of the digits of a given positive integer.
 *
 * Input:
 * • A positive integer n (1 ≤ n ≤ 109).
 *
 * Output:
 * • The sum of the digits of n.
 *
 */

int sumOfDigits(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return n % 10 + sumOfDigits(n / 10);
}

int main()
{
    int n;
    cout << "Enter a positive integer n: ";
    cin >> n;
    cout << "The sum of the digits of " << n << " is " << sumOfDigits(n) << endl;

    return 0;
}
