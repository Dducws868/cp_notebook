#include <bits/stdc++.h>
using namespace std;

// --- LAZY SEGMENT TREE (1-Indexed) ---
struct LazySegTree {
    int n;
    vector<long long> st, lazy;

    LazySegTree(int _n) {
        n = _n;
        st.assign(4 * n + 4, 0); // Mở rộng thêm an toàn cho 1-indexed
        lazy.assign(4 * n + 4, 0);
    }

    void push(int id, int l, int r) {
        if (lazy[id] != 0) {
            int mid = l + (r - l) / 2;
            st[id * 2] += lazy[id] * (mid - l + 1);
            lazy[id * 2] += lazy[id];
            
            st[id * 2 + 1] += lazy[id] * (r - mid);
            lazy[id * 2 + 1] += lazy[id];
            
            lazy[id] = 0;
        }
    }

    void update(int id, int l, int r, int ql, int qr, long long val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            st[id] += val * (r - l + 1);
            lazy[id] += val;
            return;
        }
        push(id, l, r);
        int mid = l + (r - l) / 2;
        update(id * 2, l, mid, ql, qr, val);
        update(id * 2 + 1, mid + 1, r, ql, qr, val);
        st[id] = st[id * 2] + st[id * 2 + 1];
    }

    long long query(int id, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return st[id];
        push(id, l, r);
        int mid = l + (r - l) / 2;
        return query(id * 2, l, mid, ql, qr) + query(id * 2 + 1, mid + 1, r, ql, qr);
    }
};

// --- HEAVY-LIGHT DECOMPOSITION (1-Indexed) ---
class HLD {
private:
    int n;
    vector<vector<int>> adj;
    vector<int> sz, head, parent, depth, in, out;
    int timer;

    void dfs_sz(int u, int p) {
        sz[u] = 1;
        parent[u] = p;
        for (auto &v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs_sz(v, u);
                sz[u] += sz[v];
                if (sz[v] > sz[adj[u][0]] || adj[u][0] == p) {
                    swap(v, adj[u][0]);
                }
            }
        }
    }

    void dfs_hld(int u, int p, int h) {
        head[u] = h;
        in[u] = ++timer; // in[u] sẽ chạy từ 1 đến N
        for (int v : adj[u]) {
            if (v != p) {
                dfs_hld(v, u, (v == adj[u][0] ? h : v));
            }
        }
        out[u] = timer;
    }

public:
    // Cấp phát kích thước N + 1 để dùng chỉ số 1..N
    HLD(int _n) : n(_n), adj(_n + 1), sz(_n + 1), head(_n + 1), parent(_n + 1), depth(_n + 1), in(_n + 1), out(_n + 1) {
        timer = 0; // Bắt đầu từ 0 để ++timer ra 1
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 1) { // Gốc mặc định là 1
        depth[root] = 0;
        dfs_sz(root, 0); // Nút 0 đóng vai trò là cha ảo của gốc
        dfs_hld(root, 0, root);
    }

    vector<pair<int, int>> getPathIntervals(int u, int v, bool is_edge_query = false) {
        vector<pair<int, int>> res;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            res.push_back({in[head[u]], in[u]});
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        
        if (is_edge_query) {
            if (u != v) res.push_back({in[u] + 1, in[v]});
        } else {
            res.push_back({in[u], in[v]});
        }
        return res;
    }

    pair<int, int> getSubtreeInterval(int u) {
        return {in[u], out[u]};
    }
};

// --- WRAPPER (1-Indexed) ---
struct TreeProcessor {
    int n;
    HLD hld;
    LazySegTree st;

    TreeProcessor(int _n) : n(_n), hld(_n), st(_n) {}

    void add_edge(int u, int v) {
        hld.add_edge(u, v);
    }

    void build(int root = 1) {
        hld.build(root);
    }

    void updatePath(int u, int v, long long val) {
        auto intervals = hld.getPathIntervals(u, v);
        for (auto [l, r] : intervals) {
            st.update(1, 1, n, l, r, val); // Cập nhật từ 1 đến N
        }
    }

    long long queryPath(int u, int v) {
        long long res = 0;
        auto intervals = hld.getPathIntervals(u, v);
        for (auto [l, r] : intervals) {
            res += st.query(1, 1, n, l, r); // Truy vấn từ 1 đến N
        }
        return res;
    }

    void updateSubtree(int u, long long val) {
        auto [l, r] = hld.getSubtreeInterval(u);
        st.update(1, 1, n, l, r, val);
    }

    long long querySubtree(int u) {
        auto [l, r] = hld.getSubtreeInterval(u);
        return st.query(1, 1, n, l, r);
    }
};

// --- VÍ DỤ SỬ DỤNG ---
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 5;
    TreeProcessor tp(n);
    
    // Xây dựng cây (1-indexed)
    tp.add_edge(1, 2);
    tp.add_edge(1, 3);
    tp.add_edge(2, 4);
    tp.add_edge(2, 5);

    tp.build(1); // Khởi tạo HLD lấy đỉnh 1 làm gốc

    // 1. Cộng 10 vào các đỉnh trên đường đi từ 4 đến 3
    tp.updatePath(4, 3, 10);

    // 2. Truy vấn tổng trên đường đi từ 5 đến 1
    // (Đường đi 5 -> 2 -> 1, trong đó 2 và 1 đã được cộng 10 từ bước trước)
    cout << "Tong (5 -> 1): " << tp.queryPath(5, 1) << "\n"; // Kết quả là 20

    return 0;
}
