class LazySegmentTree {
private:
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    void build(const vector<long long>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(arr, 2 * node, l, mid);
        build(arr, 2 * node + 1, mid + 1, r);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            int mid = l + (r - l) / 2;
            lazy[2 * node] += lazy[node];
            tree[2 * node] += lazy[node] * (mid - l + 1);
            lazy[2 * node + 1] += lazy[node];
            tree[2 * node + 1] += lazy[node] * (r - mid);
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int l, int r, int ql, int qr, long long val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[node] += val * (r - l + 1);
            lazy[node] += val;
            return;
        }
        push(node, l, r);
        int mid = (l + r) >> 1;
        updateRange(2 * node, l, mid, ql, qr, val);
        updateRange(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    long long queryRange(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        push(node, l, r);
        int mid = (l + r) >> 1;
        long long left_sum = queryRange(2 * node, l, mid, ql, qr);
        long long right_sum = queryRange(2 * node + 1, mid + 1, r, ql, qr);

        return left_sum + right_sum;
    }

public:
    LazySegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(4 * n + 100, 0);
        lazy.assign(4 * n + 100, 0);
        build(arr, 1, 1, n);
    }

    void updateRange(int l, int r, long long val) {
        updateRange(1, 1, n, l, r, val);
    }

    long long queryRange(int l, int r) {
        return queryRange(1, 1, n, l, r);
    }
};
