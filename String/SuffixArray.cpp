struct SuffixArray {
    int n;
    string s;
    vector<int> sa;   // Suffix Array
    vector<int> rank; // rank[i] = vị trí của hậu tố bắt đầu tại i trong mảng sa
    vector<int> lcp;  // lcp[i] = LCP của hậu tố sa[i] và sa[i-1]

    SuffixArray(string _s) {
        // Thêm ký tự '$' (nhỏ hơn mọi ký tự thường) để làm mốc kết thúc
        s = _s + "$";
        n = s.size();
        sa.assign(n, 0);
        rank.assign(n, 0);
        lcp.assign(n, 0);

        build_sa();
        build_lcp();
    }

private:
    void build_sa() {
        const int ALPHABET = 256;
        vector<int> p(n), c(n), cnt(max(ALPHABET, n), 0);

        // Bước k = 0: Sắp xếp theo 1 ký tự đầu tiên (Counting Sort)
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < ALPHABET; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;

        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i - 1]]) classes++;
            c[p[i]] = classes - 1;
        }

        // Bước k > 0: Nhân đôi độ dài tiền tố (Radix Sort)
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            // Sắp xếp nửa sau
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0) pn[i] += n;
            }

            // Counting Sort nửa đầu
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];

            // Cập nhật mảng c (hạng mới)
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }

        sa = p;
        rank = c;
    }

    void build_lcp() {
        int k = 0;
        // Duyệt chuỗi gốc (bỏ qua ký tự '$' ở cuối vì lcp của nó với thằng khác luôn là 0)
        for (int i = 0; i < n - 1; i++) {
            int pi = rank[i]; // Vị trí của hậu tố s[i..] trong mảng SA
            if (pi == 0) continue; // Bỏ qua thằng đứng đầu (chính là chuỗi "$")

            int j = sa[pi - 1]; // Hậu tố đứng ngay trước nó trong SA
            // Tăng k (chiều dài lcp) chừng nào các ký tự còn khớp
            while (s[i + k] == s[j + k]) k++;

            lcp[pi] = k;
            // Áp dụng định lý Kasai: LCP của bước tiếp theo ít nhất là k - 1
            k = max(k - 1, 0);
        }
    }
};
