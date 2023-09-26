struct HopcroftKarp {
    vector<vector<int>> g;
    vector<int> pa, pb, vis;
    int n, m, dfn, res;

    HopcroftKarp(int _n, int _m) : n(_n + 1), m(_m + 1) {
        assert(0 <= n && 0 <= m);
        pa.assign(n, -1);
        pb.assign(m, -1);
        vis.resize(n);
        g.resize(n);
        res = 0;
        dfn = 0;
    }
    void add(int x, int y) {
        assert(0 <= x && x < n && 0 <= y && y < m);
        g[x].push_back(y);
    }
    bool dfs(int v) {
        vis[v] = dfn;
        for (int u : g[v]) {
            if (pb[u] == -1) {
                pb[u] = v;
                pa[v] = u;
                return true;
            }
        }
        for (int u : g[v]) {
            if (vis[pb[u]] != dfn && dfs(pb[u])) {
                pa[v] = u;
                pb[u] = v;
                return true;
            }
        }
        return false;
    }
    int work() {
        while (1) {
            dfn++;
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (pa[i] == -1 && dfs(i)) {
                    cnt++;
                }
            }
            if (cnt == 0) break;
            res += cnt;
        }
        return res;
    }
};
signed main() {
    int n1, n2, m;
    cin >> n1 >> n2 >> m;
    HopcroftKarp flow(n1, n2);
    while (m--) {
        int x, y;
        cin >> x >> y;
        flow.add(x, y);
    }
    cout << flow.work() << endl;
}