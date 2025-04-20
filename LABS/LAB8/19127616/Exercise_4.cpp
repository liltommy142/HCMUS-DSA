#include <iostream>
#include <vector>

using namespace std;

struct Edge
{
    int u, v, weight; // Cấu trúc lưu thông tin cạnh: đỉnh đầu , đỉnh cuối , trọng số
};

// Disjoint Set Union (Union-Find)
class DSU
{
    vector<int> parent, rank; // Mảng lưu cha và hạng của mỗi tập hợp

public:
    DSU(int n)
    {
        parent.resize(n);  // Khởi tạo mảng cha
        rank.assign(n, 0); // Khởi tạo mảng hạng với giá trị 0
        for (int i = 0; i < n; ++i)
            parent[i] = i; // Ban đầu , mỗi đỉnh là cha của chính nó
    }

    int find(int x)
    {
        if (x != parent[x])              // Nếu x không phải là gốc
            parent[x] = find(parent[x]); // Tìm gốc và nén đường đi
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int xr = find(x), yr = find(y); // Tìm gốc của hai tập hợp
        if (xr == yr)                   // Nếu cùng gốc , không hợp nhất
            return false;

        // Hợp nhất hai tập hợp dựa trên hạng
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else
        {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

// Hàm sắp xếp các cạnh theo trọng số(Selection Sort)
void sortEdges(vector<Edge> &edges)
{
    int n = edges.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int minIdx = i; // Tìm cạnh có trọng số nhỏ nhất
        for (int j = i + 1; j < n; ++j)
            if (edges[j].weight < edges[minIdx].weight)
                minIdx = j;
        if (minIdx != i)
            swap(edges[i], edges[minIdx]); // Hoán đổi cạnh
    }
}

// Hàm Kruskal để tìm cây khung nhỏ nhất (MST)
void kruskal(const vector<vector<int>> &graph)
{
    int n = graph.size(); // Số lượng đỉnh trong đồ thị
    vector<Edge> edges;   // Danh sách các cạnh

    // Duyệt qua ma trận trọng số để lấy danh sách các cạnh
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (graph[i][j] != 0) // Nếu có cạnh giữa i và j
                edges.push_back({i, j, graph[i][j]});

    sortEdges(edges); // Sắp xếp các cạnh theo trọng số

    DSU dsu(n); // Khởi tạo DSU để quản lý tập hợp các đỉnh
    cout << "Edge\tWeight\n";
    for (auto &e : edges)
    {
        if (dsu.unite(e.u, e.v))                                     // Nếu hợp nhất được hai tập hợp
            cout << e.u << " - " << e.v << "\t" << e.weight << "\n"; // In cạnh thuộc MST
    }
}

int main()
{
    freopen("graph.txt", "r", stdin); // Đọc dữ liệu từ file graph.txt
    int n;
    cin >> n;                                     // Số lượng đỉnnh trong đồ thị
    vector<vector<int>> graph(n, vector<int>(n)); // Ma trận trọng số của đồ thị
    for (auto &row : graph)
        for (auto &val : row)
            cin >> val; // Nhập ma trận trọng số

    kruskal(graph); // Gọi hàm Kruskal để tìm MST
    return 0;
}