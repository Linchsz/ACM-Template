#define ls(x) t[x].ch[0]
#define rs(x) t[x].ch[1]
#define tls(x) t[ls(x)]
#define trs(x) t[rs(x)]
const int INF = 0x7fffffff;
struct Splay {
    int ch[2];
    int fa, val, siz, tag;
} t[N];
int n, m, l, r, rt, cnt;
int a[N];
ii id(int x) {
    return x == rs(t[x].fa);
}
iv update(int x) {
    t[x].siz = tls(x).siz + trs(x).siz + 1;
}
iv push_down(int x) {
    if (t[x].tag) {
        ls(x) ^= rs(x) ^= ls(x) ^= rs(x);
        tls(x).tag ^= 1;
        trs(x).tag ^= 1;
        t[x].tag = 0;
    }
}
iv connect(int fa, int x, int d) {
    t[x].fa = fa;
    t[fa].ch[d] = x;
}
iv rotate(int x) {
    int f = t[x].fa;
    int ff = t[f].fa;
    push_down(x);
    push_down(f);
    int fson = id(x);
    int ffson = id(f);
    int son = t[x].ch[fson ^ 1];
    connect(f, son, fson);
    connect(x, f, fson ^ 1);
    connect(ff, x, ffson);
    update(f), update(x);
}
iv splay(int x, int to) {
#define f t[x].fa
    while (f != to) {
        if (t[f].fa != to) {
            rotate(id(x) == id(f) ? f : x);
        }
        rotate(x);
    }
    if (!to) {
        rt = x;
    }
#undef f
}
int build(int l, int r, int fa) {
    if (l > r) {
        return 0;
    }
    int mid = (l + r) >> 1;
    int x = ++cnt;
    t[x].fa = fa;
    t[x].siz = 1;
    t[x].val = a[mid];
    ls(x) = build(l, mid - 1, x);
    rs(x) = build(mid + 1, r, x);
    update(x);
    return x;
}
ii find(int rk) {
    int x = rt;
    while (1) {
        push_down(x);
        if (rk == tls(x).siz + 1) {
            return x;
        }
        if (rk <= tls(x).siz) {
            x = ls(x);
        } else {
            rk -= tls(x).siz + 1;
            x = rs(x);
        }
    }
}
iv init(int n) {
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        a[i + 1] = i;
    }
    a[1] = -INF, a[n + 2] = INF;
    rt = build(1, n + 2, 0);
}
iv reverse(int l, int r) { // 翻转区间(l, r)
    l = find(l), r = find(r + 2);
    splay(l, 0), splay(r, l);
    t[ls(rs(rt))].tag ^= 1;
}
void print(int x) {
    push_down(x);
    if (ls(x)) {
        print(ls(x));
    }
    if (t[x].val != -INF && t[x].val != INF) {
        printf("%d ", t[x].val);
    }
    if (rs(x)) {
        print(rs(x));
    }
}
