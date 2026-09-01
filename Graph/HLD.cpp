#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

// ================= SEGMENT TREE =================
// Cây Segment Tree dùng để quản lý mảng 1 chiều sau khi đã trải phẳng cây
long long st[4 * MAXN];
long long arr[MAXN]; // Mảng lưu giá trị của các đỉnh (theo chỉ số HLD)

void build(int id, int l, int r) {
    if (l == r) {
        st[id] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    st[id] = st[2 * id] + st[2 * id + 1]; // Phép toán kết hợp (ví dụ: Tổng)
}

void update_st(int id, int l, int r, int pos, long long val) {
    if (l == r) {
        st[id] = val; // Cập nhật gán (hoặc st[id] += val nếu cộng thêm)
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update_st(2 * id, l, mid, pos, val);
    else update_st(2 * id + 1, mid + 1, r, pos, val);
    st[id] = st[2 * id] + st[2 * id + 1];
}

long long query_st(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return 0; // Giá trị trung lập của phép toán
    if (u <= l && r <= v) return st[id];
    int mid = (l + r) / 2;
    return query_st(2 * id, l, mid, u, v) + query_st(2 * id + 1, mid + 1, r, u, v);
}

// ================= HLD =================
int n;
vector<int> adj[MAXN];
long long node_val[MAXN]; // Giá trị ban đầu của các đỉnh

// Các mảng phục vụ HLD
int parent_node[MAXN], depth[MAXN], sz[MAXN];
int heavy[MAXN]; // heavy[u] = con nặng của u
int head[MAXN];  // head[u] = đỉnh đầu tiên của chuỗi nặng chứa u
int pos[MAXN];   // pos[u] = vị trí của u trên mảng 1 chiều của Segment Tree
int timer = 0;

// DFS 1: Tính kích thước cây con, độ sâu, cha, và tìm con nặng
void dfs_sz(int v, int p) {
    sz[v] = 1;
    parent_node[v] = p;
    depth[v] = depth[p] + 1;
    heavy[v] = -1;
    int max_sub = 0;

    for (int u : adj[v]) {
        if (u != p) {
            dfs_sz(u, v);
            sz[v] += sz[u];
            if (sz[u] > max_sub) {
                max_sub = sz[u];
                heavy[v] = u; // Lưu lại con nặng nhất
            }
        }
    }
}

// DFS 2: Tạo các chuỗi (chains) và trải phẳng cây ra mảng 1 chiều
void dfs_hld(int v, int p, int h) {
    head[v] = h;
    pos[v] = ++timer;
    arr[pos[v]] = node_val[v]; // Lưu giá trị đỉnh vào mảng của Segment tree

    // Ưu tiên duyệt con nặng trước để chúng nằm liên tiếp nhau trên Segment Tree
    if (heavy[v] != -1) {
        dfs_hld(heavy[v], v, h);
    }

    // Duyệt các con nhẹ
    for (int u : adj[v]) {
        if (u != p && u != heavy[v]) {
            dfs_hld(u, v, u); // Con nhẹ sẽ bắt đầu một chuỗi (chain) mới
        }
    }
}

// ================= TRUY VẤN VÀ CẬP NHẬT =================

// Cập nhật giá trị tại đỉnh u thành val
void update_node(int u, long long val) {
    update_st(1, 1, n, pos[u], val);
}

// Truy vấn tổng trên đường đi từ u đến v
long long query_path(int u, int v) {
    long long res = 0;
    // Lặp cho đến khi u và v nằm trên cùng một chuỗi
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) {
            swap(u, v);
        }
        // Truy vấn đoạn từ đỉnh đầu chuỗi (head[u]) đến u
        res += query_st(1, 1, n, pos[head[u]], pos[u]);
        // Nhảy lên cha của đỉnh đầu chuỗi
        u = parent_node[head[u]];
    }
    
    // Khi u và v đã nằm trên cùng một chuỗi
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    // LƯU Ý: Nếu trọng số nằm trên CẠNH (edges) thay vì ĐỈNH,
    // đoạn này phải cộng thêm 1 vào pos[u], tức là: query_st(..., pos[u] + 1, pos[v])
    res += query_st(1, 1, n, pos[u], pos[v]);
    
    return res;
}

int main() {
    // Tối ưu I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Ví dụ đọc dữ liệu
    /*
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> node_val[i];
    
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Khởi tạo HLD
    depth[0] = 0;
    dfs_sz(1, 0);       // Bắt đầu từ gốc 1
    dfs_hld(1, 0, 1);   // Gốc của chuỗi đầu tiên là 1
    build(1, 1, n);     // Xây dựng Segment Tree
    
    // Truy vấn
    cout << query_path(u, v) << "\n";
    */
    
    return 0;
}
