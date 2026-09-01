#include <bits/stdc++.h>
#define up(i,a,b) for (int i = (int)a; i <= (int)b; i++)
#define down(i,a,b) for (int i = (int)a; i >= (int)b; i--)
#define pii pair<int, int>
#define f first
#define s second
#define ep emplace_back
using namespace std;

ifstream finp("input.inp");
ifstream fout("my.out");
ifstream fans("correct.out");

int n;

int cs(int x) {
    int ans = 0;
    while (x > 0) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #define Task "A"
    if (fopen(Task".inp", "r")){
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }

    int b, c, a;
    cin >> b >> c >> a;
    if (b + c != a) return false;
    int t1 = cs(b), t2 = cs(c);
    if (abs(t1 - t2) > 1) return false;
    return true;
}
