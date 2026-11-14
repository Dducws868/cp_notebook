class LazyPersistentSegTree {
private:
    struct Node {
        int lc = 0, rc = 0;
        long long val = 0, lazy = 0;
    };

    int n, node_cnt;
    vector<Node> st;

    int clone_node(int id) {
        int nid = ++node_cnt;
        st[nid] = st[id];
        return nid;
    }

    void apply(int id, int l, int r, long long add_val) {
        st[id].val += add_val * (r - l + 1);
        st[id].lazy += add_val;
    }

    void push(int id, int l, int r) {
        if (st[id].lazy == 0 || l == r) return;
        int mid = (l + r) >> 1;
        st[id].lc = clone_node(st[id].lc);
        st[id].rc = clone_node(st[id].rc);
        apply(st[id].lc, l, mid, st[id].lazy);
        apply(st[id].rc, mid + 1, r, st[id].lazy);
        st[id].lazy = 0;
    }

    int build_impl(const vector<long long>& a, int l, int r) {
        int id = ++node_cnt;
        if (l == r) {
            st[id].val = a[l];
            return id;
        }
        int mid = (l + r) >> 1;
        st[id].lc = build_impl(a, l, mid);
        st[id].rc = build_impl(a, mid + 1, r);
        st[id].val = st[st[id].lc].val + st[st[id].rc].val;
        return id;
    }

    int update_impl(int prev_id, int l, int r, int ql, int qr, long long add_val) {
        int id = clone_node(prev_id);
        if (ql <= l && r <= qr) {
            apply(id, l, r, add_val);
            return id;
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            st[id].lc = update_impl(st[id].lc, l, mid, ql, qr, add_val);
        if (qr > mid)
            st[id].rc = update_impl(st[id].rc, mid + 1, r, ql, qr, add_val);
        st[id].val = st[st[id].lc].val + st[st[id].rc].val;
        return id;
    }

    long long query_impl(int id, int l, int r, int ql, int qr, long long acc_lazy) const {
        if (qr < l || r < ql) return 0;
        if (!id) return acc_lazy * (min(r, qr) - max(l, ql) + 1);
        if (ql <= l && r <= qr) return st[id].val + acc_lazy * (r - l + 1);
        int mid = (l + r) >> 1;
        acc_lazy += st[id].lazy;
        return query_impl(st[id].lc, l, mid, ql, qr, acc_lazy)
             + query_impl(st[id].rc, mid + 1, r, ql, qr, acc_lazy);
    }

public:
    LazyPersistentSegTree(int _n = 0, int max_updates = 0) {
        init(_n, max_updates);
    }

    void init(int _n, int max_updates) {
        n = _n;
        node_cnt = 0;
        int lg = (n > 0) ? (__lg(n) + 2) : 2;
        st.assign(4 * n + max_updates * 4 * lg + 5, Node());
    }

    int build(const vector<long long>& a) {
        return build_impl(a, 1, n);
    }

    // Tạo phiên bản mới từ prev_root: cộng add_val vào mọi phần tử thuộc [ql, qr]
    int update(int prev_root, int ql, int qr, long long add_val) {
        return update_impl(prev_root, 1, n, ql, qr, add_val);
    }

    // Truy vấn tổng đoạn [ql, qr] trên phiên bản ver_root
    long long query(int ver_root, int ql, int qr) const {
        return query_impl(ver_root, 1, n, ql, qr, 0);
    }
};

void main() {
    int n = 5, q = 3;
    vector<long long> a = {0, 1, 2, 3, 4, 5}; // Mảng 1-indexed

    LazyPersistentSegTree lpst(n, q);
    vector<int> root(q + 1, 0);

    root[0] = lpst.build(a);                // v0: [1, 2, 3, 4, 5]
    root[1] = lpst.update(root[0], 1, 3, 10); // v1: [11, 12, 13, 4, 5]
    root[2] = lpst.update(root[1], 2, 5, 5);  // v2: [11, 17, 18, 9, 10]
    root[3] = lpst.update(root[0], 4, 5, 20); // v3 (rẽ từ v0): [1, 2, 3, 24, 25]

    cout << lpst.query(root[1], 1, 5) << '\n'; // 45
    cout << lpst.query(root[2], 2, 4) << '\n'; // 44
    cout << lpst.query(root[3], 1, 5) << '\n'; // 55

}
