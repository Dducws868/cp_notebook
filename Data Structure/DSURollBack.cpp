struct DSU {
    vector<int> parent, sz;
    int components;
    //history
    struct State {
        int u, v, sz_v;
    };
    vector<State> history;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
        components = n;
    }

    int find(int i) {
        while (i != parent[i]) {
            i = parent[i];
        }
        return i;
    }

    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;

        if (sz[u] > sz[v]) swap(u, v);
        history.push_back({u, v, sz[v]});

        parent[u] = v;
        sz[v] += sz[u];
        components--;
        return true;
    }

    void rollback(int checkpoint) {
        while (history.size() > checkpoint) {
            State s = history.back();
            history.pop_back();

            parent[s.u] = s.u; //roll back par
            sz[s.v] = s.sz_v;
            ++components;    //++components
        }
    }
};
