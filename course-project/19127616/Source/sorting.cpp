#include "header.h"
#include <iostream>
using namespace std;

// Bubble Sort - thuật toán sắp xếp bọt
void bubbleSort(vector<Element> &arr)
{
    int n = arr.size(); // Lấy kích thước của mảng
    // Lặp qua tất cả các phần tử trong mảng
    for (int i = 0; i < n - 1; i++)
    {
        // Lặp qua các phần tử chưa được sắp xếp
        for (int j = 0; j < n - i - 1; j++)
        {
            // Nếu phần tử hiện tại lớn hơn phần tử kế tiếp, hoán đổi chúng
            if (arr[j].key > arr[j + 1].key)
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort - thuật toán sắp xếp chọn
void selectionSort(vector<Element> &arr)
{
    int n = arr.size();
    // Lặp qua tất cả các phần tử trong mảng
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i; // Giả sử phần tử hiện tại là phần tử nhỏ nhất
        // Tìm phần tử nhỏ nhất trong phần còn lại của mảng
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j].key < arr[min_idx].key)
            {
                min_idx = j; // Cập nhật chỉ số phần tử nhỏ nhất
            }
        }
        // Hoán đổi phần tử nhỏ nhất với phần tử đầu tiên chưa được sắp xếp
        swap(arr[min_idx], arr[i]);
    }
}

// Insertion Sort - thuật toán sắp xếp chèn
void insertionSort(vector<Element> &arr)
{
    int n = arr.size();
    // Bắt đầu từ phần tử thứ hai, so sánh và chèn vào vị trí đúng
    for (int i = 1; i < n; i++)
    {
        Element key = arr[i]; // Lưu phần tử cần chèn
        int j = i - 1;
        // Dịch chuyển các phần tử lớn hơn key sang phải để chèn key vào vị trí đúng
        while (j >= 0 && arr[j].key > key.key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Chèn key vào vị trí đúng
    }
}

// Heapify - hàm duy trì tính chất heap trong Heap Sort
void heapify(vector<Element> &arr, int n, int i)
{
    int largest = i;       // Giả sử nút hiện tại là lớn nhất
    int left = 2 * i + 1;  // Con trái
    int right = 2 * i + 2; // Con phải

    // Nếu con trái lớn hơn nút hiện tại, cập nhật largest
    if (left < n && arr[left].key > arr[largest].key)
    {
        largest = left;
    }
    // Nếu con phải lớn hơn nút hiện tại, cập nhật largest
    if (right < n && arr[right].key > arr[largest].key)
    {
        largest = right;
    }
    // Nếu largest không phải là nút hiện tại, hoán đổi và gọi lại heapify
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort - thuật toán sắp xếp heap
void heapSort(vector<Element> &arr)
{
    int n = arr.size();
    // Xây dựng heap (sắp xếp các phần tử thành heap)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    // Hoán đổi phần tử đầu tiên (lớn nhất) với phần tử cuối cùng, và heapify lại phần còn lại
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0); // Đảm bảo tính chất heap sau mỗi lần hoán đổi
    }
}

// Partition - hàm phân chia trong Quick Sort
int partition(vector<Element> &arr, int low, int high)
{
    Element pivot = arr[high]; // Chọn phần tử cuối cùng làm pivot
    int i = low - 1;           // Vị trí của phần tử nhỏ hơn pivot

    // Duyệt qua mảng và hoán đổi các phần tử nhỏ hơn pivot sang bên trái
    for (int j = low; j < high; j++)
    {
        if (arr[j].key <= pivot.key)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Hoán đổi pivot vào đúng vị trí của nó
    return i + 1;                // Trả về vị trí của pivot
}

// Quick Sort - thuật toán sắp xếp nhanh
void quickSort(vector<Element> &arr, int low, int high)
{
    if (low < high)
    {
        // Chia mảng thành 2 phần và đệ quy sắp xếp từng phần
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Wrapper cho Quick Sort
void quickSortWrapper(vector<Element> &arr)
{
    if (!arr.empty()) // Kiểm tra mảng không rỗng
    {
        quickSort(arr, 0, arr.size() - 1); // Gọi hàm Quick Sort
    }
}

// Merge - hàm hợp nhất trong Merge Sort
void merge(vector<Element> &arr, int l, int m, int r)
{
    int n1 = m - l + 1; // Kích thước mảng con trái
    int n2 = r - m;     // Kích thước mảng con phải

    vector<Element> L(n1), R(n2);

    // Sao chép dữ liệu vào mảng phụ L và R
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    // Hợp nhất hai mảng con vào mảng chính
    while (i < n1 && j < n2)
    {
        if (L[i].key <= R[j].key)
        {
            arr[k++] = L[i++]; // Thêm phần tử nhỏ hơn vào mảng chính
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    // Sao chép phần tử còn lại trong L hoặc R vào mảng chính
    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

// Merge Sort - thuật toán sắp xếp hợp nhất
void mergeSort(vector<Element> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;  // Tính chỉ số giữa
        mergeSort(arr, l, m);     // Sắp xếp nửa trái
        mergeSort(arr, m + 1, r); // Sắp xếp nửa phải
        merge(arr, l, m, r);      // Hợp nhất các nửa lại
    }
}

// Wrapper cho Merge Sort
void mergeSortWrapper(vector<Element> &arr)
{
    if (!arr.empty()) // Kiểm tra mảng không rỗng
    {
        mergeSort(arr, 0, arr.size() - 1); // Gọi hàm Merge Sort
    }
}

// Radix Sort - thuật toán sắp xếp cơ số
void radixSort(vector<Element> &arr)
{
    int maxKey = 0;
    // Tìm giá trị lớn nhất trong mảng để xác định số vòng lặp
    for (const auto &elem : arr)
    {
        maxKey = max(maxKey, elem.key);
    }

    // Sắp xếp theo từng chữ số (digit) của key từ thấp đến cao
    for (int exp = 1; maxKey / exp > 0; exp *= 10)
    {
        vector<int> count(10, 0); // Mảng đếm số lần xuất hiện của từng chữ số
        vector<Element> output(arr.size());

        // Đếm số lần xuất hiện của các chữ số
        for (const auto &elem : arr)
        {
            count[(elem.key / exp) % 10]++;
        }

        // Tính số lượng phần tử theo dạng tích lũy
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        // Đặt phần tử vào đúng vị trí trong mảng output
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            int digit = (arr[i].key / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        arr = output; // Cập nhật lại mảng arr với kết quả sắp xếp
    }
}

// Counting Sort - thuật toán sắp xếp đếm
void countingSort(vector<Element> &arr)
{
    int maxKey = 0;
    // Tìm giá trị lớn nhất trong mảng
    for (const auto &elem : arr)
    {
        maxKey = max(maxKey, elem.key);
    }

    vector<int> count(maxKey + 1, 0); // Mảng đếm số lần xuất hiện của các phần tử
    // Đếm số lần xuất hiện của từng phần tử
    for (const auto &elem : arr)
    {
        count[elem.key]++;
    }

    // Tính số lượng phần tử theo dạng tích lũy
    for (int i = 1; i <= maxKey; i++)
    {
        count[i] += count[i - 1];
    }

    vector<Element> output(arr.size());
    // Đặt phần tử vào đúng vị trí trong mảng output
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        output[count[arr[i].key] - 1] = arr[i];
        count[arr[i].key]--;
    }

    arr = output; // Cập nhật lại mảng arr với kết quả sắp xếp
}
