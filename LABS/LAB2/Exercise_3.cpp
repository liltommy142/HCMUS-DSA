#include <iostream>
using namespace std;

/**
 * Exercise 3. Greatest Common Divisor
 *
 * Write a program to compute the greatest common divisor (GCD) of two integers a and b.
 *
 * Input:
 * • Two positive integers a and b (1 ≤ a, b ≤ 106).
 *
 * Output:
 * • The greatest common divisor of a and b.
 *
 */

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int main()
{
    int a, b;
    cout << "Enter two positive integers a and b: ";
    cin >> a >> b;
    cout << "The greatest common divisor of " << a << " and " << b << " is " << gcd(a, b) << endl;

    return 0;
}