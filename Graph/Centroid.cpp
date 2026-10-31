class CentroidTree {
private:
    int n;
    vector<vector<int>> adj;
    vector<int> sz;
    vector<bool> removed;
    vector<int> centroid_parent;

    void get_sizes(int u, int p = -1) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v != p && !removed[v]) {
                get_sizes(v, u);
                sz[u] += sz[v];
            }
        }
    }

    int get_centroid(int u, int p, int total_sz) {
        for (int v : adj[u]) {
            if (v != p && !removed[v] && sz[v] > total_sz / 2) {
                return get_centroid(v, u, total_sz);
            }
        }
        return u;
    }

    void build_centroid_tree(int u, int p = -1) {
        get_sizes(u, -1);
        int centroid = get_centroid(u, -1, sz[u]);
        
        centroid_parent[centroid] = p;
        removed[centroid] = true;

        for (int v : adj[centroid]) {
            if (!removed[v]) {
                build_centroid_tree(v, centroid);
            }
        }
    }

public:
    CentroidTree(int n) : n(n) {
        adj.resize(n + 1);
        sz.resize(n + 1, 0);
        removed.assign(n + 1, false);
        centroid_parent.assign(n + 1, -1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 1) {
        build_centroid_tree(root, -1);
    }

    int operator[](int u) const {
        return centroid_parent[u];
    }
    
    int get_parent(int u) const {
        return centroid_parent[u];
    }
};
