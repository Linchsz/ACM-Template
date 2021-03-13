const int INF = 0x7fffffff;
struct Splay {
#define root t[0].ch[1]
    private:
        struct Node {
            int ch[2];
            int fa, val, siz, tot;
        };
        Node t[N];
        int cnt, num;
        ii id(int x) {
            return x == t[t[x].fa].ch[1];
        }
        iv update(int x) {
            t[x].siz = t[t[x].ch[0]].siz + t[t[x].ch[1]].siz + t[x].tot;
        }
        ii New(int v, int fa) {
            t[++cnt].fa = fa;
            t[cnt].val = v;
            t[cnt].siz = t[cnt].tot = 1;
            return cnt;
        }
        iv destroy(int x) {
            t[x].ch[0] = t[x].ch[1] = t[x].fa = t[x].val = t[x].siz = t[x].tot = 0;
        }
        iv connect(int fa, int x, int d) {
            t[x].fa = fa;
            t[fa].ch[d] = x;
        }
        iv rotate(int x) {
            int f = t[x].fa;
            int ff = t[f].fa;
            int fson = id(x);
            int ffson = id(f);
            int son = t[x].ch[fson ^ 1];
            connect(f, son, fson);
            connect(x, f, fson ^ 1);
            connect(ff, x, ffson);
            update(f), update(x);
        }
        iv splay(int x, int to) {
            to = t[to].fa;
            while (t[x].fa != to) {
                int f = t[x].fa;
                if (t[f].fa != to) {
                    if (id(f) == id(x)) {
                        rotate(f);
                    } else {
                        rotate(x);
                    }
                }
                rotate(x);
            }
        }
    public:
        ii find(int v) {
            int x = root;
            while (x && t[x].val != v) {
                int d = v < t[x].val ? 0 : 1;
                x = t[x].ch[d];
            }
            if (x) {
                splay(x, root);
            }
            return x;
        }
        ii build(int v) {
            ++num;
            if (!root) {
                return root = New(v, 0);
            }
            int x = root;
            while (1) {
                ++t[x].siz;
                if (t[x].val == v) {
                    ++t[x].tot;
                    return x;
                }
                int d = v < t[x].val ? 0 : 1;
                if (!t[x].ch[d]) {
                    return t[x].ch[d] = New(v, x);
                }
                x = t[x].ch[d];
            }
            return 0;
        }
        iv insert(int v) {
            splay(build(v), root);
        }
        iv del(int v) {
            int x = find(v);
            if (!x) {
                return;
            }
            --num;
            if (t[x].tot > 1) {
                --t[x].tot;
                --t[x].siz;
                return;
            }
            if (!t[x].ch[0]) {
                root = t[x].ch[1];
                t[root].fa = 0;
            } else {
                int L = t[x].ch[0];
                int R = t[x].ch[1];
                while (t[L].ch[1]) {
                    L = t[L].ch[1];
                }
                splay(L, t[x].ch[0]);
                connect(0, L, 1);
                connect(L, R, 1);
                update(L);
            }
            destroy(x);
        }
        ii get_rk(int v) { // 寻找权值为 v 的点的排名
            int x = root, rk = 0;
            while (x) {
                if (v == t[x].val) {
                    rk += t[t[x].ch[0]].siz + 1;
                    break;
                }
                if (v < t[x].val) {
                    x = t[x].ch[0];
                } else {
                    rk += t[t[x].ch[0]].siz + t[x].tot;
                    x = t[x].ch[1];
                }
            }
            if (x) {
                splay(x, root);
            }
            return rk;
        }
        ii get_val(int rk) { // 寻找排名为 rk 的点的权值
            // if (rk > num) {
                // return INF;
            // }
            int x = root;
            while (1) {
                int s = t[t[x].ch[0]].siz;
                if (rk <= s) {
                    x = t[x].ch[0];
                }
                else if (rk <= s + t[x].tot) {
                    break;
                }
                else {
                    rk -= s + t[x].tot;
                    x = t[x].ch[1];
                }
            }
            splay(x, root);
            return t[x].val;
        }
        ii get_pre(int v) { // 寻找权值为 v 的点的前驱结点
            int x = root, pre = -INF;
            while (x) {
                if (t[x].val < v) {
                    pre = t[x].val;
                    x = t[x].ch[1];
                } else {
                    x = t[x].ch[0];
                }
            }
            return pre;
        }
        ii get_nx(int v) { // 寻找权值为 v 的点的后继结点
            int x = root, nx = INF;
            while (x) {
                if (t[x].val > v) {
                    nx = t[x].val;
                    x = t[x].ch[0];
                } else {
                    x = t[x].ch[1];
                }
            }
            return nx;
        }
#undef root
} S;
