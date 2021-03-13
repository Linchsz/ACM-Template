#define N "Edit"
struct HLD
{
    int n, dfs_clock;
    int sz[maxn], top[maxn], son[maxn], dep[maxn], fa[maxn], id[maxn];
    vector<int> G[maxn];
    // vector<pair<PII, int>> edges; 维护边权时，将其下放为儿子结点的点权
    void init(int n)
    {
        this->n = n, memset(son, -1, sizeof(son)), dfs_clock = 0;
        for (int i = 0; i <= n; i++) G[i].clear();
    }
    void add_edge(int u, int v) { G[u].push_back(v), G[v].push_back(u); }
    void dfs(int u, int p, int d) {
        dep[u] = d, fa[u] = p, sz[u] = 1;
        for (auto& v : G[u])
        {
            if (v == p) continue;
            dfs(v, u, d + 1);
            sz[u] += sz[v];
            if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v;
        }
    }
    void link(int u, int t)
    {
        top[u] = t, id[u] = ++dfs_clock;
        if (son[u] == -1) return;
        link(son[u], t);
        for (auto& v : G[u])
            if (v != son[u] && v != fa[u]) link(v, v);
    }
    int query_path(int u, int v)
    { // 数据结构相关操作，一般使用线段树或者树状数组
        int ret = 0;
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            ret += query(id[top[u]], id[u]);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        ret += query(id[u], id[v]);
        /* 边权
        if (u == v) return ret;
        if (dep[u] > dep[v]) swap(u, v);
        ret += query(id[son[u]], id[v]);
        */
        return ret;
    }
};


#include <bits/stdc++.h>
using namespace std;

#define N 100005
#define ls(x) (x << 1)
#define rs(x) (x << 1 ^ 1)
#define print(x, c) wr(x), putchar(c)

inline int rd() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

inline void wr(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    int y = 1, len = 1;
    while (y <= x / 10) {
        y = (y << 1) + (y << 3);
        ++len;
    }
    for (; len; --len) {
        putchar(x / y ^ 48);
        x %= y;
        y /= 10;
    }
}

struct Node {
    int to, nx;
} e[N << 1];

int n, m, r, P, x, y, z, q, cnt, tot;
int h[N], w[N], wt[N], t[N << 2], tag[N << 2];
int id[N], dep[N], fa[N], son[N], siz[N], top[N];

inline void add(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nx = h[u];
    h[u] = cnt;
}

void dfs1(int u, int pre) {
    dep[u] = dep[pre] + 1;
    fa[u] = pre;
    siz[u] = 1;
    int maxsons = 0;
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].to;
        if (v != pre) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (maxsons < siz[v]) {
                maxsons = siz[v];
                son[u] = v;
            }
        }
    }
}

void dfs2(int u, int tpf) {
    top[u] = tpf;
    id[u] = ++tot;
    wt[tot] = w[u];
    if (!son[u]) {
        return;
    }
    dfs2(son[u], tpf);
    for (int i = h[u]; i; i = e[i].nx) {
        int v = e[i].to;
        if (v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

inline void pushup(int p) {
    t[p] = (t[ls(p)] + t[rs(p)]) % P;
}

inline void pushdown(int l, int r, int p) {
    if (tag[p]) {
        int mid = (l + r) >> 1;
        int L = ls(p), R = rs(p);
        (tag[L] += tag[p]) %= P;
        (tag[R] += tag[p]) %= P;
        (t[L] += tag[p] * (mid - l + 1)) %= P;
        (t[R] += tag[p] * (r - mid)) %= P;
        tag[p] = 0;
    }
}

void build(int l, int r, int p) {
    if (l == r) {
        t[p] = wt[l] % P;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, ls(p));
    build(mid + 1, r, rs(p));
    pushup(p);
}

int query(int l, int r, int p, int x, int y) {
    if (x <= l && y >= r) {
        return t[p];
    }
    pushdown(l, r, p);
    int ans = 0, mid = (l + r) >> 1;
    if (x <= mid) {
        ans += query(l, mid, ls(p), x, y);
    }
    if (y > mid) {
        ans += query(mid + 1, r, rs(p), x, y);
    }
    return ans % P;
}

void update(int l, int r, int p, int x, int y, int k) {
    if (x <= l && y >= r) {
        (tag[p] += k) %= P;
        (t[p] += k * (r - l + 1)) %= P;
        return;
    }
    pushdown(l, r, p);
    int mid = (l + r) >> 1;
    if (x <= mid) {
        update(l, mid, ls(p), x, y, k);
    }
    if (y > mid) {
        update(mid + 1, r, rs(p), x, y, k);
    }
    pushup(p);
}

inline void updRange(int x, int y, int z) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            swap(x, y);
        }
        update(1, n, 1, id[top[x]], id[x], z);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        swap(x, y);
    }
    update(1, n, 1, id[x], id[y], z);
}

inline int qRange(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            swap(x, y);
        }
        (ans += query(1, n, 1, id[top[x]], id[x])) %= P;;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        swap(x, y);
    }
    ans += query(1, n, 1, id[x], id[y]);
    return ans % P;
}

inline void updSon(int x, int z) {
    update(1, n, 1, id[x], id[x] + siz[x] - 1, z);
}

inline int qSon(int x) {
    return query(1, n, 1, id[x], id[x] + siz[x] - 1);
}

int main() {
    freopen("in.txt", "r", stdin);
    n = rd(), m = rd(), r = rd(), P =rd();
    for (int i = 1; i <= n; ++i) {
        w[i] = rd();
    }
    for (int i = 1; i < n; ++i) {
        x = rd(), y = rd();
        add(x, y), add(y, x);
    }
    dfs1(r, 0);
    dfs2(r, r);
    build(1, n, 1);
    while (m--) {
        q = rd(), x = rd();
        switch (q) {
            case 1:
                y = rd(), z = rd();
                updRange(x, y, z);
                break;
            case 2:
                y = rd();
                print(qRange(x, y), '\n');
                break;
            case 3:
                z = rd();
                updSon(x, z);
                break;
            case 4:
                print(qSon(x), '\n');
        }
    }
    return 0;
}


