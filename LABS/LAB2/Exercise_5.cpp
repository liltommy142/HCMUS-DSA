#include <iostream>
using namespace std;

/**
 * Exercise 5. Reverse a String
 *
 * Write a program to reverse a given string.
 *
 * Input:
 * • A string consisting of lowercase or uppercase characters.
 *
 * Output:
 * • The reversed string.
 *
 */

string reverseString(string str)
{
    if (str.length() == 0)
    {
        return "";
    }
    return str[str.length() - 1] + reverseString(str.substr(0, str.length() - 1));
}

int main()
{
    string str;
    cout << "Enter a string: ";
    cin >> str;
    cout << "The reversed string is " << reverseString(str) << endl;

    return 0;
}