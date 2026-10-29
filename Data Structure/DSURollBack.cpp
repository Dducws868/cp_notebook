struct DSURollBack {
    vector<int> par, sz;
    int components;
    vector<pair<int, int>> history;

    DSU_Rollback(int n) {
        par.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(par.begin(), par.end(), 0);
        components = n;
    }

    int find_set(int u) {
        while (u != par[u]) u = par[u];
        return u;
    }

    bool unite(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u == v) return false;

        if (sz[u] > sz[v]) swap(u, v);
        
        history.push_back({u, v});
        par[u] = v;
        sz[v] += sz[u];
        components--;
        return true;
    }

    int get_state() {
        return history.size();
    }

    void rollback(int state) {
        while (history.size() > state) {
            int u = history.back().first;
            int v = history.back().second;
            history.pop_back();

            sz[v] -= sz[u];
            par[u] = u;
            components++;
        }
    }
};
