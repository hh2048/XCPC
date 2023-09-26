struct HLD {
    vector<vector<int>> e;
    vector<int> siz, son, cnt;
    vector<LL> ans;
    LL sum, Max;
    int hson;
    HLD(int n) {
        e.resize(n + 1);
        siz.resize(n + 1);
        son.resize(n + 1);
        ans.resize(n + 1);
        cnt.resize(n + 1);
        hson = 0;
        sum = 0;
        Max = 0;
    }
    void add(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }
    void dfs1(int u, int fa) {
        siz[u] = 1;
        for (auto v : e[u]) {
            if (v == fa) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    void calc(int u, int fa, int val) {
        cnt[color[u]] += val;
        if (cnt[color[u]] > Max) {
            Max = cnt[color[u]];
            sum = color[u];
        } else if (cnt[color[u]] == Max) {
            sum += color[u];
        }
        for (auto v : e[u]) {
            if (v == fa || v == hson) continue;
            calc(v, u, val);
        }
    }
    void dfs2(int u, int fa, int opt) {
        for (auto v : e[u]) {
            if (v == fa || v == son[u]) continue;
            dfs2(v, u, 0);
        }
        if (son[u]) {
            dfs2(son[u], u, 1);
            hson = son[u]; //记录重链编号，计算的时候跳过
        }
        calc(u, fa, 1);
        hson = 0; //消除的时候所有儿子都清除
        ans[u] = sum;
        if (!opt) {
            calc(u, fa, -1);
            sum = 0;
            Max = 0;
        }
    }
};
