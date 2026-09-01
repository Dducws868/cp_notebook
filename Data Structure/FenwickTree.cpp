class FenwickTree {
private:
    int n;
    vector<long long> bit;

public:
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n + 1, 0); 
    }

    FenwickTree(const vector<long long>& arr) {
        n = arr.size();
        bit.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            bit[i + 1] += arr[i]; 
            int nxt = (i + 1) + ((i + 1) & -(i + 1)); 
            if (nxt <= n) {
                bit[nxt] += bit[i + 1];
            }
        }
    }

    void add(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    long long query(int idx) {
        long long sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += bit[idx];
        }
        return sum;
    }

    long long queryRange(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};
