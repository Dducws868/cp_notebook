class SegmentTree {
private:
    int n;
    vector<long long> tree;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(arr, 2 * node, l, mid);
        build(arr, 2 * node + 1, mid + 1, r);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int node, int l, int r, int idx, long long val) {
        if (l == r) {
            tree[node] += val;
            return;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(2 * node, l, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, r, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];

        int mid = l + (r - l) / 2;
        long long left_sum = query(2 * node, l, mid, ql, qr);
        long long right_sum = query(2 * node + 1, mid + 1, r, ql, qr);
        return left_sum + right_sum;
    }

public:
    SegmentTree(int _n, int arr[]) {
        n = _n;
        tree.assign(4 * n + 100, 0);
        build(1, 1, n);
    }

    void update(int idx, long long val) {
        update(1, 1, n, idx, val);
    }

    long long query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};
