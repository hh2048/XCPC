struct DSU {
    vector<int> fa;

    DSU() {}
    void init(int n) {
        fa.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
    }
    int get(int x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool merge(int x, int y) { // 设x是y的祖先
        x = get(x), y = get(y);
        if (x == y) return false;
        fa[y] = x;
        return true;
    }
    bool same(int x, int y) {
        return get(x) == get(y);
    }
};
struct MaxMatch {
    int n, cnt;
    vector<vector<int>> ver;
    vector<int> pre, mark, match;
    DSU dsu;

    MaxMatch(int n) : n(n) {
        cnt = 0;
        ver.resize(n);
        match.resize(n, -1);
        pre.resize(n, -1);
        mark.resize(n, -1);
    }
    void add(int x, int y) {
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    int lca(int x, int y) {
        ++cnt;
        while (1) {
            if (x != -1) {
                x = dsu.get(x);
                if (mark[x] == cnt) break;
                mark[x] = cnt;
                x = match[x] != -1 ? pre[match[x]] : -1;
            }
            swap(x, y);
        }
        return x;
    }
    bool get_match(int s) {
        dsu.init(n);
        vector<int> q;
        q.push_back(s);
        vector<int> type(n, -1);
        type[s] = 0;
        for (int i = 0; i < (int)q.size(); ++i) { // 注意这里不能用 auto
            int x = q[i];
            for (auto y : ver[x]) {
                if (type[y] == -1) {
                    pre[y] = x;
                    type[y] = 1;
                    int z = match[y];
                    if (z == -1) {
                        for (int u = y; u != -1;) {
                            int v = match[pre[u]];
                            match[u] = pre[u];
                            match[pre[u]] = u;
                            u = v;
                        }
                        return true;
                    }
                    q.push_back(z);
                    type[z] = 0;
                } else if (type[y] == 0 && !dsu.same(x, y)) {
                    int z = lca(x, y);
                    auto blossom = [&](int x, int y, int z) -> void {
                        while (!dsu.same(x, z)) {
                            pre[x] = y;
                            if (type[match[x]] == 1) {
                                type[match[x]] = 0;
                                q.push_back(match[x]);
                            }
                            if (dsu.get(x) == x) {
                                dsu.merge(z, x); // z为祖先，注意顺序
                            }
                            if (dsu.get(match[x]) == match[x]) {
                                dsu.merge(z, match[x]); // z为祖先，注意顺序
                            }
                            y = match[x];
                            x = pre[y];
                        }
                    };
                    blossom(x, y, z);
                    blossom(y, x, z);
                }
            }
        }
        return false;
    };
    pair<int, vector<int>> work() { // {最大匹配数量, i号点的另一个匹配点 (0代表无匹配)}
        int matching = 0;
        for (int x = 0; x < n; ++x) {
            if (match[x] == -1 && get_match(x)) {
                matching++;
            }
        }
        return {matching, match};
    }
};
signed main() {
    int n, m;
    cin >> n >> m;

    MaxMatch match(n);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        match.add(x - 1, y - 1);
    }
    auto [ans, match] = match.work();
    cout << ans << endl;
    for (auto it : match) {
        cout << it + 1 << " ";
    }
}