#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Hàm in đường đi từ đỉnh nguồn đến đỉnh đích
void printPath(const vector<int> &prev, int v)
{
    if (v == -1) // Nếu không có đỉnh trước đó , dừng lại
        return;
    printPath(prev, prev[v]); // Đệ quy để in các đỉnh trước đó
    cout << v;
    if (prev[v] != -1)
        cout << " -> "; // In dấu mũi tên giữa các đỉnh
}

// Hàm Bellman-Ford để tìm đường đi ngắn nhất từ đỉnh nguồn (src)
void bellmanFord(const vector<vector<int>> &graph, int src)
{
    int n = graph.size();     // Số lượng đỉnh trong đồ thị
    vector<int> dist(n, INF); // Mảng lưu khoảng cách ngắn nhất từ src đến các đỉnh
    vector<int> prev(n, -1);  // Mảng lưu đỉnh trước đó trên đường đi ngắn nhất
    dist[src] = 0;            // Khoảng cách từ src đến chính nó là 0

    vector<tuple<int, int, int>> edges; // Danh sách các cạnh (u , v , trọng số w)
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            if (graph[u][v] != 0)                     // Nếu có cạnh từ u đến v
                edges.push_back({u, v, graph[u][v]}); // Thêm cạnh vào danh sách

    // Thư giãn các cạnh n-1 lần
    for (int i = 0; i < n - 1; ++i)
        for (auto [u, v, w] : edges)
            if (dist[u] != INF && dist[u] + w < dist[v]) // Nếu tìm được khoảng cách ngắn hơn
            {
                dist[v] = dist[u] + w; // Cập nhật khoảng cách ngắn nhất
                prev[v] = u;           // Lưu đỉnh trước đó
            }

    // Kiểm tra chu trình trọng số âm (không nên xảy ra trong bài này)
    for (auto [u, v, w] : edges)
        if (dist[u] != INF && dist[u] + w < dist[v]) // Nếu phát hiện chu trình âm
        {
            cout << "Graph contains negative weight cycle\n"; // Đồ thị chứa chu trình trọng số âm
            return;
        }

    // In kết quả đường đi ngắn nhất từ src đến các đỉnh khác
    for (int i = 0; i < n; ++i)
    {
        if (i == src)
            continue;
        cout << "The shortest path from " << src << " to " << i << ": ";
        if (dist[i] == INF) // Nếu không có đường đi
        {
            cout << "No path\n"; // Không có đường đi
            continue;
        }
        printPath(prev, i); // In đường đi
        cout << ".\n";
    }
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

    int src;
    cout << "Enter source vertex: ";
    cin >> src; // Nhập đỉnh nguồn

    bellmanFord(graph, src); // Gọi hàm Bellman-Ford
    return 0;
}