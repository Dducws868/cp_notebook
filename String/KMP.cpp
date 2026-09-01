vector<int> compute_lps(const string& P) {
    int m = P.length();
    vector<int> lps(m, 0);
    
    // j is pre len
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && P[i] != P[j]) {
            j = lps[j - 1]; // backtracking until suitable
        }
        if (P[i] == P[j]) {
            j++;
        }
        lps[i] = j;
    }
    return lps;
}
