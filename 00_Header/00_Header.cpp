#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const double pi = 4.0 * atan(1.0);

typedef long long ll;
typedef long double ld;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define fastin                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
#define fi first
#define se second
#define gc getchar()
#define pc(x) putchar(x)
#define pb(x) push_back(x)
#define eb(x) emplace_back(x)
#define rd_() rd<__int128>()
#define wd_(x) wr<__int128>(x)
#define print(x, c) wr(x), putchar(c)
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repn(i, n) for (int i = 1; i <= (n); ++i)

template <typename T>
inline T rd() {
    T x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) f = c == '-' ? -1 : 1, c = getchar();
    while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * f;
}

template <typename T>
inline void wr(T x) {
    T y = 1, len = 1;
    if (x < 0) x = -x, putchar('-');
    while (y <= x / 10) y = (y << 1) + (y << 3), ++len;
    for (; len; --len) putchar(x / y ^ 48), x %= y, y /= 10;
}

int main() {
#ifdef IO
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif

    return 0;
}
