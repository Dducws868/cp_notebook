#include <bits/stdc++.h>
using namespace std;
int UID(int L, int R) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(L, R)(rng);
}
signed main() {
    int n = UID(1, 1000);
    cout << n << endl;
    for (int i = 1; i <= n; ++i) cout << UID(1, 100) << ' ' << UID(1, 100) << endl;
    return 0;
}
