#include <iostream>
#include <vector>
using namespace std;

int fibo(int n)
{
    return n <= 1 ? n : fibo(n - 1) + fibo(n - 2);
}

int factorial(int n)
{
    return n == 0 ? 1 : n * factorial(n - 1);
}

int sum(int n)
{
    return n == 0 ? 0 : n % 10 + sum(n / 10);
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

bool checkIncreasing(int *a, int n)
{
    if (n == 2)
    {
        return a[0] < a[1];
    }
    return a[n - 2] < a[n - 1] && checkIncreasing(a, n - 1);
}

void isIncreasing()
{
    int n;
    cin >> n;
    if (n < 2)
    {
        cout << "No";
        return;
    }
    int *a;
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    checkIncreasing(a, n) ? cout << "Yes" : cout << "No";
}

string reverse(string s)
{
    if (s.length() == 1)
    {
        return s;
    }
    return s[s.length() - 1] + reverse(s.substr(0, s.length() - 1));
}

void isPalindrome()
{
    string s;
    cin >> s;
    s == reverse(s) ? cout << "Yes" : cout << "No";
}

// permuteHelper({1, 2, 3}, l=0, r=2)
//  ├── swap(0,0) → {1, 2, 3}
//  │   ├── permuteHelper({1, 2, 3}, l=1, r=2)
//  │   │   ├── swap(1,1) → {1, 2, 3}
//  │   │   │   ├── permuteHelper({1, 2, 3}, l=2, r=2) → Add {1, 2, 3}
//  │   │   ├── swap(1,2) → {1, 3, 2}
//  │   │   │   ├── permuteHelper({1, 3, 2}, l=2, r=2) → Add {1, 3, 2}
//  │   │   ├── Backtrack → {1, 2, 3}
//  │   ├── swap(0,1) → {2, 1, 3}
//  │   │   ├── permuteHelper({2, 1, 3}, l=1, r=2)
//  │   │   │   ├── swap(1,1) → {2, 1, 3}
//  │   │   │   │   ├── permuteHelper({2, 1, 3}, l=2, r=2) → Add {2, 1, 3}
//  │   │   │   ├── swap(1,2) → {2, 3, 1}
//  │   │   │   │   ├── permuteHelper({2, 3, 1}, l=2, r=2) → Add {2, 3, 1}
//  │   │   │   ├── Backtrack → {2, 1, 3}
//  │   │   ├── Backtrack → {1, 2, 3}
//  │   ├── swap(0,2) → {3, 2, 1}
//  │   │   ├── permuteHelper({3, 2, 1}, l=1, r=2)
//  │   │   │   ├── swap(1,1) → {3, 2, 1}
//  │   │   │   │   ├── permuteHelper({3, 2, 1}, l=2, r=2) → Add {3, 2, 1}
//  │   │   │   ├── swap(1,2) → {3, 1, 2}
//  │   │   │   │   ├── permuteHelper({3, 1, 2}, l=2, r=2) → Add {3, 1, 2}
//  │   │   │   ├── Backtrack → {3, 2, 1}
//  │   │   ├── Backtrack → {1, 2, 3}

void permute(vector<int> &elements, int l, int r)
{
    if (l == r)
    {
        for (int num : elements)
        {
            cout << num << " ";
        }
        cout << endl;
        return;
    }
    for (int i = l; i <= r; i++)
    {
        swap(elements[l], elements[i]);
        permute(elements, l + 1, r);
        swap(elements[l], elements[i]); // Backtrack
    }
}

void subset(int i, vector<int> &arr, vector<vector<int>> &res, vector<int> &ss)
{

    // add subset at end of array
    if (i == arr.size())
    {
        res.push_back(ss);
        return;
    }

    // include the current value and
    // recursively find all subsets
    ss.push_back(arr[i]);
    subset(i + 1, arr, res, ss);

    // exclude the current value and
    // recursively find all subsets.
    ss.pop_back();
    subset(i + 1, arr, res, ss);
}

void printBinHelper(int n, int *a, int i)
{
    if (i == n)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[j];
        }
        cout << endl;
        return;
    }

    a[i] = 0;
    printBinHelper(n, a, i + 1);

    a[i] = 1;
    printBinHelper(n, a, i + 1);
}

int main(int argc, char const *argv[])
{
    // cout << "Fibonacci of 5: " << fibo(5) << endl;
    // cout << "Factorial of 0: " << factorial(0) << endl;
    // cout << "Sum of 9876: " << sum(9876) << endl;
    // cout << "GCD of 100 and 75: " << gcd(100, 75) << endl;
    // isIncreasing();

    // string s = "world";
    // cout << "Reverse of " << s << " is " << reverse(s) << endl;

    // isPalindrome();

    // int n;
    // cin >> n;
    // vector<int> a(n);
    // for (size_t i = 0; i < n; i++)
    // {
    //     cin >> a[i];
    // }
    // permute(a, 0, n - 1);

    // vector<vector<int>> res;
    // vector<int> ss;

    // subset(0, a, res, ss);
    // for (auto &v : res)
    // {
    //     cout << "{ ";
    //     for (auto &num : v)
    //     {
    //         cout << num << " ";
    //     }
    //     cout << "}" << endl;
    // }

    int n;
    cin >> n;
    int a[n];
    printBinHelper(n, a, 0);

    return 0;
}
