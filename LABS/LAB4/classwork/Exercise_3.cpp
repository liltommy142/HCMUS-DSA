#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Structure to store employee details
struct Employee
{
    string id;
    string name;
    int birthYear;
};

// Function to correct birth year if it is too large
void correctBirthYear(int &year)
{
    if (year > 9999)
    {
        year = 1900 + (year % 100);
    }
}

// Function to get the current year
int getCurrentYear()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);
    return now->tm_year + 1900;
}

// Function to read employees from a file
void readEmployees(const string &filename, vector<Employee> &employees)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line))
    {
        Employee emp;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        emp.id = line.substr(0, pos1);
        emp.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        emp.birthYear = stoi(line.substr(pos2 + 1));
        correctBirthYear(emp.birthYear);
        employees.push_back(emp);
    }
    file.close();
}

// Function to write employees to a file
void writeEmployees(const string &filename, const vector<Employee> &employees)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    file << "id, name, birth year" << endl;
    for (const auto &emp : employees)
    {
        file << emp.id << "," << emp.name << "," << emp.birthYear << endl;
    }
    file.close();
}

// Function to compare two employees based on age and name
bool compareEmployees(const Employee &a, const Employee &b)
{
    int currentYear = getCurrentYear();
    int ageA = currentYear - a.birthYear;
    int ageB = currentYear - b.birthYear;
    if (ageA != ageB)
    {
        return ageA > ageB;
    }
    return a.name < b.name;
}

// Function to sort employees using insertion sort
void insertionSort(vector<Employee> &employees)
{
    int n = employees.size();
    for (int i = 1; i < n; ++i)
    {
        Employee key = employees[i];
        int j = i - 1;
        while (j >= 0 && compareEmployees(key, employees[j]))
        {
            employees[j + 1] = employees[j];
            j = j - 1;
        }
        employees[j + 1] = key;
    }
}

// Function to sort employees using selection sort
void selectionSort(vector<Employee> &employees)
{
    int n = employees.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int max_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (compareEmployees(employees[j], employees[max_idx]))
            {
                max_idx = j;
            }
        }
        swap(employees[max_idx], employees[i]);
    }
}

// Function to sort employees using interchange sort
void interchangeSort(vector<Employee> &employees)
{
    int n = employees.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (compareEmployees(employees[j], employees[i]))
            {
                swap(employees[i], employees[j]);
            }
        }
    }
}

// Function to print the menu
void printMenu()
{
    cout << "Select sorting algorithm:" << endl;
    cout << "1. Insertion Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "3. Interchange Sort" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    vector<Employee> employees;
    readEmployees("employee.txt", employees);

    int choice;
    printMenu();
    cin >> choice;

    switch (choice)
    {
    case 1:
        insertionSort(employees);
        break;
    case 2:
        selectionSort(employees);
        break;
    case 3:
        interchangeSort(employees);
        break;
    default:
        cout << "Invalid choice!" << endl;
        return 1;
    }

    writeEmployees("sortedemponage.txt", employees);
    cout << "Employees sorted and written to sortedemponage.txt" << endl;

    return 0;
}