struct DSURollBack {
    vector<int> parent, sz;
    int components;
    
    struct State {
        int u, v;
        int sz_u, sz_v;
        int components;
    };
    stack<State> st;

    DSURollBack(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        components = n;
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return find(parent[i]);
    }

    void unite(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u == root_v) {
            st.push({-1, -1, -1, -1, components});
            return;
        }

        if (sz[root_u] < sz[root_v]) swap(root_u, root_v);

        st.push({root_u, root_v, sz[root_u], sz[root_v], components});

        parent[root_v] = root_u;
        sz[root_u] += sz[root_v];
        components--;
    }

    void rollback() {
        if (st.empty()) return;
        State s = st.top();
        st.pop();

        if (s.u != -1) {
            parent[s.v] = s.v;
            sz[s.u] = s.sz_u;
            sz[s.v] = s.sz_v;
            components = s.components;
        }
    }
};

struct QueryTree {
    int T;
    vector<vector<pair<int, int>>> tree;
    vector<int> answers;

    QueryTree(int T) : T(T) {
        tree.resize(4 * T + 1);
        answers.assign(T + 1, -1);
    }

    void add_edge_to_tree(int node, int l, int r, int ql, int qr, int u, int v) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node].push_back({u, v});
            return;
        }
        int mid = l + (r - l) / 2;
        add_edge_to_tree(2 * node, l, mid, ql, qr, u, v);
        add_edge_to_tree(2 * node + 1, mid + 1, r, ql, qr, u, v);
    }

    void add_edge(int l, int r, int u, int v) {
        if (l > r) return;
        add_edge_to_tree(1, 1, T, l, r, u, v);
    }

    void dfs(int node, int l, int r, RollbackDSU& dsu) {
        for (auto& edge : tree[node]) {
            dsu.unite(edge.first, edge.second);
        }

        if (l == r) {
            answers[l] = dsu.components; 
        } else {
            int mid = l + (r - l) / 2;
            dfs(2 * node, l, mid, dsu);
            dfs(2 * node + 1, mid + 1, r, dsu);
        }

        for (auto& edge : tree[node]) {
            dsu.rollback();
        }
    }

    void solve(RollbackDSU& dsu) {
        if (T > 0) dfs(1, 1, T, dsu);
    }
};
