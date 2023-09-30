struct E_DCC {
    int n;
    vector<int> h, ver, ne;
    vector<int> dfn, low, col, S;
    int now, cnt, tot;
    vector<bool> bridge; // 记录是否是割边

    E_DCC(int n, int m) : n(n) {
        m *= 2; // 注意链式前向星边的数量翻倍
        ver.resize(m + 1);
        ne.resize(m + 1);
        bridge.resize(m + 1);
        
        h.resize(n + 1, -1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        col.resize(n + 1);
        S.clear();
        tot = cnt = now = 0;
    }
    void add(int x, int y) { // 注意，这里的编号从 0 开始
        ver[tot] = y, ne[tot] = h[x], h[x] = tot++;
        ver[tot] = x, ne[tot] = h[y], h[y] = tot++;
    }
    void tarjan(int x, int fa) { // 这里是缩边双，不是缩点，不相同
        dfn[x] = low[x] = ++now;
        S.push_back(x);
        for (int i = h[x]; ~i; i = ne[i]) {
            int y = ver[i];
            if (!dfn[y]) {
                tarjan(y, i); // 这里储存的是父亲边的编号
                low[x] = min(low[x], low[y]);
                // y 不能到达 x 的任何一个祖先节点，(x - y) 即为一条割边
                // 但是在这里，我们不直接储存 (x - y) 这条边，而是储存边的编号
                // 这样做是为了处理重边的情况（点可能相同，但是边的编号绝对不相同）
                if (dfn[x] < low[y]) {
                    bridge[i] = bridge[i ^ 1] = true;
                }
            } else if (i != (fa ^ 1)) { // 这里同样的，使用边的编号来处理重边情况
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int pre = 0;
            cnt++;
            do {
                pre = S.back();
                S.pop_back();
                col[pre] = cnt;
            } while (pre != x);
        }
    }
    pair<int, vector<vector<int>>> rebuild() { // [新图的顶点数量, 新图]
        work();
        vector<vector<int>> adj(cnt + 1);
        for (int i = 0; i < tot; ++i) {
            if (bridge[i]) { // 如果 (i, i ^ 1) 是割边
                int x = col[ver[i]], y = col[ver[i ^ 1]];
                adj[x].push_back(y); // 割边两端点颜色必定不同，故直接连边
            }
        }
        return {cnt, adj};
    }
    void work() {
        for (int i = 1; i <= n; i++) { // 避免图不连通
            if (dfn[i] == 0) {
                tarjan(i, -1);
            }
        }
    }
};