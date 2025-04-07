#include <iostream>
#include <vector>

using namespace std;

// Custom max and min functions
inline int max(int a, int b)
{
    return (a > b) ? a : b;
}

inline int min(int a, int b)
{
    return (a < b) ? a : b;
}

// Custom log2 function using bit manipulation
inline int log2(int n)
{
    int result = 0;
    while (n >>= 1)
    {
        result++;
    }
    return result;
}

// Function to calculate GCD using Euclidean algorithm
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

class SparseTable
{
private:
    vector<vector<int>> maxTable;
    vector<vector<int>> minTable;
    vector<vector<int>> gcdTable;
    int n, logN;

public:
    SparseTable(const vector<int> &arr)
    {
        n = arr.size();
        logN = log2(n) + 1;

        // Initialize tables
        maxTable.resize(n, vector<int>(logN));
        minTable.resize(n, vector<int>(logN));
        gcdTable.resize(n, vector<int>(logN));

        // Fill the tables for range of length 1 (2^0)
        for (int i = 0; i < n; i++)
        {
            maxTable[i][0] = arr[i];
            minTable[i][0] = arr[i];
            gcdTable[i][0] = arr[i];
        }

        // Build the sparse tables
        for (int j = 1; j < logN; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                // For maximum
                maxTable[i][j] = max(maxTable[i][j - 1], maxTable[i + (1 << (j - 1))][j - 1]);

                // For minimum
                minTable[i][j] = min(minTable[i][j - 1], minTable[i + (1 << (j - 1))][j - 1]);

                // For GCD
                gcdTable[i][j] = gcd(gcdTable[i][j - 1], gcdTable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Query for maximum in range [L, R]
    int queryMax(int L, int R)
    {
        int length = R - L + 1;
        int k = log2(length);
        return max(maxTable[L][k], maxTable[R - (1 << k) + 1][k]);
    }

    // Query for minimum in range [L, R]
    int queryMin(int L, int R)
    {
        int length = R - L + 1;
        int k = log2(length);
        return min(minTable[L][k], minTable[R - (1 << k) + 1][k]);
    }

    // Query for GCD in range [L, R]
    int queryGCD(int L, int R)
    {
        int length = R - L + 1;
        int k = log2(length);
        return gcd(gcdTable[L][k], gcdTable[R - (1 << k) + 1][k]);
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    SparseTable sparseTable(arr);

    int L, R;
    cin >> L >> R;

    int maximum = sparseTable.queryMax(L, R);
    int minimum = sparseTable.queryMin(L, R);
    int gcdValue = sparseTable.queryGCD(L, R);

    cout << maximum << " " << minimum << " " << gcdValue << endl;

    return 0;
}