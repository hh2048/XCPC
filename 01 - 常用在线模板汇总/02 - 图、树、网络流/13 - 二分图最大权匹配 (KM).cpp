struct MaxCostMatch {
    vector<int> ansl, ansr, pre;
    vector<int> lx, ly;
    vector<vector<int>> ver;
    int n;

    MaxCostMatch(int n) : n(n) {
        ver.resize(n + 1, vector<int>(n + 1));
        ansl.resize(n + 1, -1);
        ansr.resize(n + 1, -1);
        lx.resize(n + 1);
        ly.resize(n + 1, -1E18);
        pre.resize(n + 1);
    }
    void add(int x, int y, int w) {
        ver[x][y] = w;
    }
    void bfs(int x) {
        vector<bool> visl(n + 1), visr(n + 1);
        vector<int> slack(n + 1, 1E18);
        queue<int> q;
        function<bool(int)> check = [&](int x) {
            visr[x] = 1;
            if (~ansr[x]) {
                q.push(ansr[x]);
                visl[ansr[x]] = 1;
                return false;
            }
            while (~x) {
                ansr[x] = pre[x];
                swap(x, ansl[pre[x]]);
            }
            return true;
        };
        q.push(x);
        visl[x] = 1;
        while (1) {
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int y = 1; y <= n; ++y) {
                    if (visr[y]) continue;
                    int del = lx[x] + ly[y] - ver[x][y];
                    if (del < slack[y]) {
                        pre[y] = x;
                        slack[y] = del;
                        if (!slack[y] && check(y)) return;
                    }
                }
            }
            int val = 1E18;
            for (int i = 1; i <= n; ++i) {
                if (!visr[i]) {
                    val = min(val, slack[i]);
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (visl[i]) lx[i] -= val;
                if (visr[i]) {
                    ly[i] += val;
                } else {
                    slack[i] -= val;
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (!visr[i] && !slack[i] && check(i)) {
                    return;
                }
            }
        }
    }
    int work() {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                ly[i] = max(ly[i], ver[j][i]);
            }
        }
        for (int i = 1; i <= n; ++i) bfs(i);
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res += ver[i][ansl[i]];
        }
        return res;
    }
    void getMatch(int x, int y) { // 获取方案 (0代表无匹配)
        for (int i = 1; i <= x; ++i) {
            cout << (ver[i][ansl[i]] ? ansl[i] : 0) << " ";
        }
        cout << endl;
        for (int i = 1; i <= y; ++i) {
            cout << (ver[i][ansr[i]] ? ansr[i] : 0) << " ";
        }
        cout << endl;
    }
};

signed main() {
    int n1, n2, m;
    cin >> n1 >> n2 >> m;

    MaxCostMatch match(max(n1, n2));
    for (int i = 1; i <= m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        match.add(x, y, w);
    }
    cout << match.work() << '\n';
    match.getMatch(n1, n2);
}