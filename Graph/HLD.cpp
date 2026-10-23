#include <bits/stdc++.h>
using namespace std;

// --- LAZY SEGMENT TREE ---
// Quản lý mảng 1 chiều với các truy vấn Range Add và Range Sum
struct LazySegTree {
    int n;
    vector<long long> st, lazy;

    LazySegTree(int _n) {
        n = _n;
        st.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
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

// --- HEAVY-LIGHT DECOMPOSITION ---
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
        in[u] = ++timer;
        for (int v : adj[u]) {
            if (v != p) {
                dfs_hld(v, u, (v == adj[u][0] ? h : v));
            }
        }
        out[u] = timer;
    }

public:
    HLD(int _n) : n(_n), adj(_n), sz(_n), head(_n), parent(_n), depth(_n), in(_n), out(_n) {
        timer = -1;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        depth[root] = 0;
        dfs_sz(root, -1);
        dfs_hld(root, -1, root);
    }

    // Trả về các đoạn [L, R] trên mảng 1 chiều
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

// --- WRAPPER: TÍCH HỢP HLD + SEGMENT TREE ---
struct TreeProcessor {
    int n;
    HLD hld;
    LazySegTree st;

    TreeProcessor(int _n) : n(_n), hld(_n), st(_n) {}

    void add_edge(int u, int v) {
        hld.add_edge(u, v);
    }

    void build(int root = 0) {
        hld.build(root);
    }

    // Cập nhật cộng val vào các đỉnh trên đường đi từ u đến v
    void updatePath(int u, int v, long long val) {
        auto intervals = hld.getPathIntervals(u, v);
        for (auto [l, r] : intervals) {
            st.update(1, 0, n - 1, l, r, val);
        }
    }

    // Truy vấn tổng các đỉnh trên đường đi từ u đến v
    long long queryPath(int u, int v) {
        long long res = 0;
        auto intervals = hld.getPathIntervals(u, v);
        for (auto [l, r] : intervals) {
            res += st.query(1, 0, n - 1, l, r);
        }
        return res;
    }

    // Cập nhật toàn bộ cây con gốc u
    void updateSubtree(int u, long long val) {
        auto [l, r] = hld.getSubtreeInterval(u);
        st.update(1, 0, n - 1, l, r, val);
    }

    // Truy vấn tổng toàn bộ cây con gốc u
    long long querySubtree(int u) {
        auto [l, r] = hld.getSubtreeInterval(u);
        return st.query(1, 0, n - 1, l, r);
    }
};

// --- VÍ DỤ SỬ DỤNG ---
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 5;
    TreeProcessor tp(n);
    
    // Xây dựng cây (0-indexed)
    tp.add_edge(0, 1);
    tp.add_edge(0, 2);
    tp.add_edge(1, 3);
    tp.add_edge(1, 4);

    tp.build(0); // Khởi tạo HLD lấy đỉnh 0 làm gốc

    // 1. Cộng 10 vào các đỉnh trên đường đi từ 3 đến 2
    tp.updatePath(3, 2, 10);

    // 2. Truy vấn tổng trên đường đi từ 4 đến 0
    cout << "Tong (4 -> 0): " << tp.queryPath(4, 0) << "\n"; // Sẽ bằng 10 (vì đỉnh 0, 1 nằm trên đường đi 3->2)

    // 3. Cộng 5 vào toàn bộ cây con gốc 1
    tp.updateSubtree(1, 5);

    // 4. Truy vấn lại cây con gốc 1
    cout << "Tong subtree(1): " << tp.querySubtree(1) << "\n";

    return 0;
}
