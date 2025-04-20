#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX; // Giá trị vô cực để biểu diễn khoảng cách không thể đạt được

// Hàm Dijkstra để tìm đường đi ngắn nhất từ đỉnh nguồn (src)
void dijkstra(const vector<vector<int>> &graph, int src)
{
    int n = graph.size();           // Số lượng đỉnh trong đồ thị
    vector<int> dist(n, INF);       // Mảng lưu khoảng cách ngắn nhất từ src đến các đỉnh
    vector<int> prev(n, -1);        // Mảng lưu đỉnh trước đó trên đường đi ngắn nhất
    vector<bool> visited(n, false); // Mảng đánh dấu các đỉnh đã được thăm

    dist[src] = 0; // Khoảng cách từ src đến chính nó là 0

    // Lặp qua tất cả các đỉnh
    for (int count = 0; count < n - 1; ++count)
    {
        int u = -1; // Đỉnh có khoảng cách nhỏ nhất chưa được thăm
        int minDist = INF;
        for (int i = 0; i < n; ++i)
            if (!visited[i] && dist[i] < minDist)
            {
                u = i;
                minDist = dist[i];
            }

        if (u == -1) // Nếu không tìm thấy đỉnh nào , thoát vòng lặp
            break;
        visited[u] = true; // Đánh dấu đỉnh u đã được thăm

        // Cập nhật khoảng cách đến các đỉnh kề của u
        for (int v = 0; v < n; ++v)
            if (graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v]; // Cập nhật khoảng cách ngắn nhất
                prev[v] = u;                     // Lưu đỉnh trước đó
            }
    }

    // In kết quả đường đi ngắn nhất từ src đến các đỉnh khác
    for (int i = 0; i < n; ++i)
    {
        if (i == src)
            continue;
        cout << "The shortest path from " << src << " to " << i << ": ";
        if (dist[i] == INF)
        {
            cout << "No path\n"; // Không có đường đi
            continue;
        }
        vector<int> path; // Lưu đường đi
        for (int v = i; v != -1; v = prev[v])
            path.insert(path.begin(), v); // Truy ngược lại đường đi
        for (size_t j = 0; j < path.size(); ++j)
        {
            cout << path[j];
            if (j != path.size() - 1)
                cout << " -> "; // In đường đi
        }
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

    dijkstra(graph, src); // Gọi hàm Dijkstra
    return 0;
}