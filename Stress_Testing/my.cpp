#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double;
using str = string;

#define TcT template<class T

#define mp make_pair
#define F first
#define S second
using pi = pair<int, int>;

TcT > using V = vector<T>;
using vi = V<int>;
using vl = V<ll>;
using vpi = V<pi>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sor(x) sort(all(x))
#define ft front()
#define bk back()

#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define F0R(i, n) FOR(i, 0, n - 1)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define rep(i, n) F0R(i, n)
#define each(i, a) for (auto &i : a)

TcT > bool cmin(T &a, const T &b) { return (a > b) ? a = b, true : false; }
TcT > bool cmax(T &a, const T &b) { return (a < b) ? a = b, true : false; }

const int MAX = 1e6 + 100;
const ll INF = 1e18;

int n;
int a[MAX], b[MAX];

void read() {
    cin >> n;
    FOR(i, 1, 2 * n) cin >> a[i] >> b[i];
}

namespace sub1 {

    const int MAXC = 2e3 + 100;

    int dp[MAXC][MAXC]; //check val i, used j as

    void process() {
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;

        FOR(i, 1, 2 * n) {
            FOR(j, 0, n) {
                if (j) cmin(dp[i][j], dp[i - 1][j - 1] + a[i]);
                cmin(dp[i][j], dp[i - 1][j] + b[i]);
            }
        }

        cout << dp[2 * n][n];
    }
}

namespace full {

    bool cmp(const pi &x, const pi &y) {
        return x.F - x.S > y.F - y.S;
    }

    void process() {
        vpi val;
        FOR(i, 1, 2 * n) val.pb(mp(a[i], b[i]));

        sort(all(val), cmp);
        int res = 0;
        FOR(i, 1, 2 * n) {
            if (i <= n) res += val[i - 1].S;
            else res += val[i - 1].F;
        }
        cout << res;
    }
}

bool check1() {
    return n <= 1000;
}

void solve() {
    full::process();

//    full::process();
}

int main() {
//    freopen("acm.inp", "r", stdin);
//    freopen("acm.out", "w", stdout);
    if (fopen("in.inp", "r")) {
        freopen("in.inp", "r", stdin);
    }
    cin.tie(nullptr)->sync_with_stdio(false);
    read();
    solve();

    return 0;
}