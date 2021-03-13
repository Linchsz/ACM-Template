// ---
// 使用前用init()进行初始化\\
// 加边使用函数addedge(u,v)
// ---
const int maxn = "Edit";
int n;
vector<int> G[maxn];
int linker[maxn];
bool used[maxn];
inline void init(int n)
{
    for (int i = 0; i < n; i++) G[i].clear();
}
inline void addedge(int u, int v) { G[u].push_back(v); }
bool dfs(int u)
{
    for (auto& v : G[u])
    {
        if (!used[v])
        {
            used[v] = true;
            if (linker[v] == -1 || dfs(linker[v]))
            {
                linker[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int ans = 0;
    memset(linker, -1, sizeof(linker));
    for (int u = 0; u < n; u++)
    {
        memset(used, 0, sizeof(used));
        if (dfs(u)) ans++;
    }
    return ans;
}
