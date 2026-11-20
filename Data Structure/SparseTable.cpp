const int MAX = 200005;
const int LOG = 19;

int st[LOG][MAX];

int merge_val(int a, int b) {
    return min(a, b);
}

void build(int n, const vector<int>& a) {
    for (int i = 0; i < n; ++i) st[0][i] = a[i];
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[j][i] = merge_val(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
}

int query(int l, int r) {
    int j = 31 - __builtin_clz(r - l + 1);
    return merge_val(st[j][l], st[j][r - (1 << j) + 1]);
}
