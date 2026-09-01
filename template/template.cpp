#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double;  // or double, if TL is tight
using str = string;      // yay python!

// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
#define mp make_pair
#define F first
#define S second

#define tcT template <class T
#define tcTU tcT, class U
// ^ lol this makes everything look weird but I'll try it
tcT, size_t SZ > using AR = array<T, SZ>;
tcT > using V = vector<T>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

// vectors
#define sz(x) int(size(x))
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()

// loops
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define F0R(i, a) FOR(i, 0, a - 1)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)

constexpr int pct(int x) { return __builtin_popcount(x); }  // # of bits set
constexpr int bits(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }  // floor(log2(x))
constexpr bool bt(int x, int i) { return ((x >> i) & 1); }
constexpr ll pw2(int x) { return 1LL << x; }
constexpr ll msk2(int x) { return pw2(x) - 1; }

tcT > bool ckmin(T &a, const T &b) {
    return b < a ? a = b, 1 : 0;
}
tcT > bool ckmax(T &a, const T &b) {
    return a < b ? a = b, 1 : 0;
}

inline namespace DEBUG {
#ifdef LOCAL
#include "D:\template.cpp"
#else
#define debug(...)
#define debugArr(...)
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
void timeElapsed() {
    cerr << "\nTime elapsed: " << chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time).count() << " s";
}
}  // namespace DEBUG

inline namespace FILEIO {
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(12);
    if (fopen("in.inp", "r")) setIn("in.inp");
    if (sz(s)) setIn(s + ".inp"), setOut(s + ".out");
}
}  // namespace FILEIO

const int MOD = 998244353;  // 1e9+7
const int MAX = (int)1e6 + 100;
const int LOG = 20;
const ll INF = (ll)1e18;
const db PI = acos((db)-1);
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());


int main() {
    setIO();


    return 0;
}
/* STUFF YOU SHOULD LOOK FOR
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
