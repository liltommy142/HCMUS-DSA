#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Hàm đọc ma trận từ file
bool readMatrix(const char *filename, int **&matrix, int &rows, int &cols)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false; // Không thể mở file
    }

    rows = 0;
    cols = -1;
    string line;
    // Đọc từng dòng trong file
    while (getline(file, line))
    {
        istringstream stream(line);
        int tempCols = 0;
        int value;
        // Đếm số cột trong dòng
        while (stream >> value)
        {
            tempCols++;
        }

        if (cols == -1)
        {
            cols = tempCols; // Gán số cột đầu tiên
        }
        else if (cols != tempCols)
        {
            return false; // Cấu trúc ma trận không hợp lệ
        }

        rows++; // Tăng số dòng
    }

    file.clear();
    file.seekg(0); // Đưa con trỏ file về đầu

    // Cấp phát bộ nhớ cho ma trận
    matrix = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];
    }

    int rowIndex = 0;
    // Đọc lại file và lưu giá trị vào ma trận
    while (getline(file, line))
    {
        istringstream stream(line);
        for (int colIndex = 0; colIndex < cols; ++colIndex)
        {
            stream >> matrix[rowIndex][colIndex];
        }
        rowIndex++;
    }

    return true; // Đọc thành công
}

// Hàm in ma trận ra file
void printMatrix(const char *filename, int **matrix, int rows, int cols)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return; // Không thể mở file để ghi
    }

    // Ghi ma trận vào file
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            file << matrix[i][j];
            if (j < cols - 1)
            {
                file << " "; // Thêm khoảng trắng giữa các giá trị
            }
        }
        file << endl; // Xuống dòng sau mỗi hàng
    }
}

// Hàm giải phóng bộ nhớ của ma trận
void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] matrix[i]; // Giải phóng bộ nhớ từng hàng
    }
    delete[] matrix; // Giải phóng bộ nhớ của mảng con trỏ
}

int main()
{
    int **matrix;
    int rows, cols;

    // Đọc ma trận từ file
    if (!readMatrix("input.txt", matrix, rows, cols))
    {
        cerr << "Error: Unable to read matrix from file." << endl;
        return 1; // Thoát chương trình nếu đọc thất bại
    }

    // In ma trận ra file
    printMatrix("output.txt", matrix, rows, cols);

    // Giải phóng bộ nhớ
    freeMatrix(matrix, rows);

    return 0; // Kết thúc chương trình
}