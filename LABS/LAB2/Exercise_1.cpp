#include <iostream>
using namespace std;

/**
 * Exercise 1. Factorial
 *
 * Write a program to compute the factorial of a given non-negative integer n. The factorial of n is
 * defined as:
 * n! = n × (n − 1) × · · · × 1, where 0! = 1.
 * 
 * Input:
 * • A non-negative integer n (0 ≤ n ≤ 20).
 * 
 * Output:
 * • The factorial of n.
 * 
 */

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter a non-negative integer n: ";
    cin >> n;
    cout << "The factorial of " << n << " is " << factorial(n) << endl;

    return 0;
}
