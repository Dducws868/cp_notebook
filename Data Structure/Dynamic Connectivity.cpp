class DynamicConnectivity {
private:
    int q;
    vector<vector<pair<int, int>>> seg_tree;
    vector<bool> is_query;
    vector<int> ans;

    void add_edge(int node, int l, int r, int ql, int qr, int u, int v) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            seg_tree[node].push_back({u, v});
            return;
        }
        int mid = (l + r) / 2;
        add_edge(2 * node, l, mid, ql, qr, u, v);
        add_edge(2 * node + 1, mid + 1, r, ql, qr, u, v);
    }

    void solve(int node, int l, int r, DSU_Rollback& dsu) {
        int state = dsu.get_state();
        
        for (auto edge : seg_tree[node]) {
            dsu.unite(edge.first, edge.second);
        }

        if (l == r) {
            if (is_query[l]) {
                ans.push_back(dsu.components);
            }
        } else {
            int mid = (l + r) / 2;
            solve(2 * node, l, mid, dsu);
            solve(2 * node + 1, mid + 1, r, dsu);
        }

        dsu.rollback(state);
    }

public:
    DynamicConnectivity(int q_size) {
        q = q_size;
        seg_tree.resize(4 * q + 1);
        is_query.assign(q + 1, false);
    }

    void add_interval(int l, int r, int u, int v) {
        if (l <= r) {
            add_edge(1, 1, q, l, r, u, v);
        }
    }

    void mark_query(int time) {
        is_query[time] = true;
    }

    void process(int n) {
        DSU_Rollback dsu(n);
        solve(1, 1, q, dsu);
        for (int res : ans) {
            cout << res << "\n";
        }
    }
};
