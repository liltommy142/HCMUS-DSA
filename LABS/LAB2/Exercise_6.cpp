#include <iostream>
using namespace std;

/**
 * Exercise 6. Check Palindrome String
 * 
 * Write a program to check whether a given string is a palindrome. A palindrome is a string that reads the same backward as forward.
 * 
 * Input:
 * • A string consisting of lowercase characters only.
 * 
 * Output:
 * • Yes if the string is a palindrome.
 * • No otherwise.
 * 
 */

bool isPalindrome(string str)
{
    if (str.length() <= 1)
    {
        return true;
    }
    if (str[0] != str[str.length() - 1])
    {
        return false;
    }
    return isPalindrome(str.substr(1, str.length() - 2));
}

int main(int argc, char const *argv[])
{
    string str;
    cout << "Enter a string: ";
    cin >> str;
    cout << (isPalindrome(str) ? "Yes" : "No") << endl;

    return 0;
}