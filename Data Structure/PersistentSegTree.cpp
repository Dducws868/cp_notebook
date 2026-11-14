class PersistentSegTree {
private:
    struct Node {
        int lc = 0, rc = 0;
        long long val = 0;
    };

    int n, node_cnt;
    vector<Node> st;

    int new_node(long long val = 0, int l = 0, int r = 0) {
        int id = ++node_cnt;
        st[id] = {l, r, val};
        return id;
    }

    int build_impl(const vector<long long>& a, int l, int r) {
        if (l == r) return new_node(a[l]);
        int mid = (l + r) >> 1;
        int lc = build_impl(a, l, mid);
        int rc = build_impl(a, mid + 1, r);
        return new_node(st[lc].val + st[rc].val, lc, rc);
    }

    int update_impl(int prev_id, int l, int r, int pos, long long v, bool is_set) {
        if (l == r) {
            long long new_val = is_set ? v : (st[prev_id].val + v);
            return new_node(new_val);
        }
        int mid = (l + r) >> 1;
        int lc = st[prev_id].lc;
        int rc = st[prev_id].rc;
        if (pos <= mid)
            lc = update_impl(lc, l, mid, pos, v, is_set);
        else
            rc = update_impl(rc, mid + 1, r, pos, v, is_set);
        return new_node(st[lc].val + st[rc].val, lc, rc);
    }

    long long query_impl(int id, int l, int r, int ql, int qr) const {
        if (!id || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[id].val;
        int mid = (l + r) >> 1;
        return query_impl(st[id].lc, l, mid, ql, qr)
             + query_impl(st[id].rc, mid + 1, r, ql, qr);
    }

    int kth_impl(int u, int v, int l, int r, long long k) const {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        long long left_cnt = st[st[v].lc].val - st[st[u].lc].val;
        if (k <= left_cnt)
            return kth_impl(st[u].lc, st[v].lc, l, mid, k);
        return kth_impl(st[u].rc, st[v].rc, mid + 1, r, k - left_cnt);
    }

public:
    PersistentSegTree(int _n = 0, int max_updates = 0) {
        init(_n, max_updates);
    }

    void init(int _n, int max_updates) {
        n = _n;
        node_cnt = 0;
        int lg = (n > 0) ? (__lg(n) + 2) : 2;
        st.assign(4 * n + max_updates * lg + 5, Node());
    }

    int build(const vector<long long>& a) {
        return build_impl(a, 1, n);
    }

    int add(int prev_root, int pos, long long delta) {
        return update_impl(prev_root, 1, n, pos, delta, false);
    }

    int set(int prev_root, int pos, long long new_val) {
        return update_impl(prev_root, 1, n, pos, new_val, true);
    }

    long long query(int ver_root, int ql, int qr) const {
        return query_impl(ver_root, 1, n, ql, qr);
    }

    int kth(int root_u, int root_v, long long k) const {
        return kth_impl(root_u, root_v, 1, n, k);
    }
};

void main() {
    PersistentSegTree pst(n, q);
    vector<int> root(q + 1);
    
    root[0] = pst.build(a); // Phiên bản 0
    
    // Cập nhật lần thứ i dựa trên phiên bản trước (hoặc phiên bản k bất kỳ)
    root[1] = pst.add(root[0], pos, delta);
    root[2] = pst.set(root[1], pos, new_val);
    
    // Truy vấn tổng đoạn [l, r] ở phiên bản 1
    long long ans = pst.query(root[1], l, r);
}
