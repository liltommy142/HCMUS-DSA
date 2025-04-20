#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Hàm Prim để tìm cây khung nhỏ nhất (MST) của đồ thị
void prim(const vector<vector<int>> &graph)
{
    int n = graph.size();         // Số lượng đỉnh trong đồ thị
    vector<int> parent(n, -1);    // Mảng lưu đỉnh cha của mỗi đỉnh trong MST
    vector<int> key(n, INF);      // Mảng lưu trọng số nhỏ nhất để kết nối mỗi đỉnh
    vector<bool> inMST(n, false); // Mảng đánh dấu các đỉnh đã nằm trong MST

    key[0] = 0; // Bắt đầu từ đỉnh 0 , trọng số để kết nối là 0

    // Lặp qua tất cả các đỉnh để xây dựng MST
    for (int count = 0; count < n - 1; ++count)
    {
        int u = -1; // Đỉnh có trọng số nhỏ nhất chưa nằm trong MST
        int minKey = INF;

        // Tìm đỉnh có trọng số nhỏ nhất chưa nằm trong MST
        for (int v = 0; v < n; ++v)
            if (!inMST[v] && key[v] < minKey)
            {
                u = v;
                minKey = key[v];
            }

        if (u == -1) // Nếu không tìm thấy đỉnh nào , thoát vòng lặp
            break;
        inMST[u] = true; // Đánh dấu đỉnh u đã nằm trong MST

        // Cập nhật trọng số của các đỉnh kề với u
        for (int v = 0; v < n; ++v)
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v]; // Cập nhật trọng số nhỏ nhất
                parent[v] = u;        // Lưu đỉnh cha của v
            }
    }

    // In các cạnh và trọng số trong MST
    cout << "Edge\tWeight\n";
    for (int v = 1; v < n; ++v)
        if (parent[v] != -1)
            cout << parent[v] << " - " << v << "\t" << graph[parent[v]][v] << "\n";
}

int main()
{
    freopen("graph.txt", "r", stdin); // Đọc dữ liệu từ file graph.txt
    int n;
    cin >> n;                                     // Số lượng đỉnh trong đồ thị
    vector<vector<int>> graph(n, vector<int>(n)); // Ma trận trọng số của đồ thị
    for (auto &row : graph)
        for (auto &val : row)
            cin >> val; // Nhập ma trận trọng số

    prim(graph); // Gọi hàm Prim để tìm MST
    return 0;
}