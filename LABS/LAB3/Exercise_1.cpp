#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Linear Search (with while loop)
int linearSearch(const vector<int> &arr, int x)
{
    int i = 0;
    while (i < arr.size())
    {
        if (arr[i] == x)
            return i; // Return the index if the element is found
        i++;
    }
    return -1; // Return -1 if the element is not found
}

// Linear Search with Sentinel
int linearSearchSentinel(vector<int> arr, int x)
{
    int n = arr.size();
    arr.push_back(x); // Add sentinel
    int i = 0;
    while (arr[i] != x)
        i++;
    return (i == n) ? -1 : i; // Return -1 if the element is not found, otherwise return the index
}

// Binary Search (Array is sorted)
int binarySearch(const vector<int> &arr, int x)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x)
            return mid; // Return the index if the element is found
        else if (arr[mid] < x)
            left = mid + 1; // Search in the right half
        else
            right = mid - 1; // Search in the left half
    }
    return -1; // Return -1 if the element is not found
}

// Interpolation Search (Array is sorted)
int interpolationSearch(const vector<int> &arr, int x)
{
    int left = 0, right = arr.size() - 1;
    while (left <= right && x >= arr[left] && x <= arr[right])
    {
        if (left == right)
        {
            if (arr[left] == x)
                return left; // Return the index if the element is found
            return -1; // Return -1 if the element is not found
        }
        int pos = left + ((double)(right - left) / (arr[right] - arr[left]) * (x - arr[left]));
        if (arr[pos] == x)
            return pos; // Return the index if the element is found
        else if (arr[pos] < x)
            left = pos + 1; // Search in the right half
        else
            right = pos - 1; // Search in the left half
    }
    return -1; // Return -1 if the element is not found
}

int main(int argc, char *argv[])
{
    // Test the algorithms
    if (argc != 5)
    {
        cerr << "Usage: " << argv[0] << " algorithm x input_path output_path" << endl;
        return 1;
    }

    int algorithm = stoi(argv[1]);
    int x = stoi(argv[2]);
    string input_path = argv[3];
    string output_path = argv[4];

    ifstream inputFile(input_path);
    if (!inputFile)
    {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    int N;
    inputFile >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++)
    {
        inputFile >> arr[i];
    }
    inputFile.close();

    int result = -1;
    switch (algorithm)
    {
    case 1:
        result = linearSearch(arr, x);
        break;
    case 2:
        result = linearSearchSentinel(arr, x);
        break;
    case 3:
        result = binarySearch(arr, x);
        break;
    case 4:
        result = interpolationSearch(arr, x);
        break;
    default:
        cerr << "Invalid algorithm choice!" << endl;
        return 1;
    }

    ofstream outputFile(output_path);
    if (!outputFile)
    {
        cerr << "Error opening output file!" << endl;
        return 1;
    }
    outputFile << result;
    outputFile.close();

    return 0;
}
