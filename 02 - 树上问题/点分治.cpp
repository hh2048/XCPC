int root = 0, MaxTree = 1e18; //分别代表重心下标、最大子树大小
vector<int> vis(n + 1), siz(n + 1);
auto get = [&](auto self, int x, int fa, int n) -> void { // 获取树的重心
    siz[x] = 1;
    int val = 0;
    for (auto [y, w] : ver[x]) {
        if (y == fa || vis[y]) continue;
        self(self, y, x, n);
        siz[x] += siz[y];
        val = max(val, siz[y]);
    }
    val = max(val, n - siz[x]);
    if (val < MaxTree) {
        MaxTree = val;
        root = x;
    }
};

auto clac = [&](int x) -> void { // 以 x 为新的根，维护询问
    set<int> pre = {0}; // 记录到根节点 x 距离为 i 的路径是否存在
    vector<int> dis(n + 1);
    for (auto [y, w] : ver[x]) {
        if (vis[y]) continue;
        vector<int> child; // 记录 x 的子树节点的深度信息
        auto dfs = [&](auto self, int x, int fa) -> void {
            child.push_back(dis[x]);
            for (auto [y, w] : ver[x]) {
                if (y == fa || vis[y]) continue;
                dis[y] = dis[x] + w;
                self(self, y, x);
            }
        };
        dis[y] = w;
        dfs(dfs, y, x);
        
        for (auto it : child) {
            for (int i = 1; i <= m; i++) { // 根据询问更新值
                if (q[i] < it || !pre.count(q[i] - it)) continue;
                ans[i] = 1;
            }
        }
        pre.insert(child.begin(), child.end());
    }
};

auto dfz = [&](auto self, int x, int fa) -> void { // 点分治
    vis[x] = 1; // 标记已经被更新过的旧重心，确保只对子树分治
    clac(x);
    for (auto [y, w] : ver[x]) {
        if (y == fa || vis[y]) continue;
        MaxTree = 1e18;
        get(get, y, x, siz[y]);
        self(self, root, x);
    }
};

get(get, 1, 0, n);
dfz(dfz, root, 0);
