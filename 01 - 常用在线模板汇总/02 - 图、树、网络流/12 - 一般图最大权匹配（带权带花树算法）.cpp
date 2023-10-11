using i64 = long long;

struct Graph {
    const int inf = INT_MAX;
    static const int N = 2 * 514;
    struct edge {
        int u, v, w;
        edge() {}
        edge(int u, int v, int w) : u(u), v(v), w(w) {}
    };
    int n, n_x;
    edge g[N][N];
    int lab[N];
    int match[N], slack[N], st[N], pa[N];
    int flo_from[N][N + 1], S[N], vis[N];
    vector<int> flo[N];
    queue<int> q;
    
    Graph(int n_) : n(n_) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                g[u][v] = {u, v, 0};
            }
        }
    }
    void add(int x, int y, int w) {
        g[x][y].w = g[y][x].w = w;
    }
    int e_delta(const edge &e) {
        return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2;
    }
    void update_slack(int u, int x) {
        if (!slack[x] || e_delta(g[u][x]) < e_delta(g[slack[x]][x])) {
            slack[x] = u;
        }
    }
    void set_slack(int x) {
        slack[x] = 0;
        for (int u = 1; u <= n; ++u) {
            if (g[u][x].w > 0 && st[u] != x && S[st[u]] == 0) {
                update_slack(u, x);
            }
        }
    }
    void q_push(int x) {
        if (x <= n) {
            q.push(x);
        } else {
            for (int i = 0; i < flo[x].size(); i++) {
                q_push(flo[x][i]);
            }
        }
    }
    void set_st(int x, int b) {
        st[x] = b;
        if (x > n) {
            for (int i = 0; i < flo[x].size(); ++i) {
                set_st(flo[x][i], b);
            }
        }
    }
    int get_pr(int b, int xr) {
        int pr = find(flo[b].begin(), flo[b].end(), xr) - flo[b].begin();
        if (pr % 2 == 1) {
            reverse(flo[b].begin() + 1, flo[b].end());
            return (int)flo[b].size() - pr;
        }
        return pr;
    }
    void set_match(int u, int v) {
        match[u] = g[u][v].v;
        if (u <= n) return;
        edge e = g[u][v];
        int xr = flo_from[u][e.u], pr = get_pr(u, xr);
        for (int i = 0; i < pr; ++i) {
            set_match(flo[u][i], flo[u][i ^ 1]);
        }
        set_match(xr, v);
        rotate(flo[u].begin(), flo[u].begin() + pr, flo[u].end());
    }
    void augment(int u, int v) {
        while (1) {
            int xnv = st[match[u]];
            set_match(u, v);
            if (!xnv) return;
            set_match(xnv, st[pa[xnv]]);
            u = st[pa[xnv]], v = xnv;
        }
    }
    int get_lca(int u, int v) {
        static int t = 0;
        for (++t; u || v; swap(u, v)) {
            if (u == 0) continue;
            if (vis[u] == t) return u;
            vis[u] = t;
            u = st[match[u]];
            if (u) u = st[pa[u]];
        }
        return 0;
    }
    void add_blossom(int u, int lca, int v) {
        int b = n + 1;
        while (b <= n_x && st[b]) ++b;
        if (b > n_x) ++n_x;
        lab[b] = 0, S[b] = 0;
        match[b] = match[lca];
        flo[b].clear();
        flo[b].push_back(lca);
        for (int x = u, y; x != lca; x = st[pa[y]]) {
            flo[b].push_back(x);
            flo[b].push_back(y = st[match[x]]);
            q_push(y);
        }
        reverse(flo[b].begin() + 1, flo[b].end());
        for (int x = v, y; x != lca; x = st[pa[y]]) {
            flo[b].push_back(x);
            flo[b].push_back(y = st[match[x]]);
            q_push(y);
        }
        set_st(b, b);
        for (int x = 1; x <= n_x; ++x) {
            g[b][x].w = g[x][b].w = 0;
        }
        for (int x = 1; x <= n; ++x) {
            flo_from[b][x] = 0;
        }
        for (int i = 0; i < flo[b].size(); ++i) {
            int xs = flo[b][i];
            for (int x = 1; x <= n_x; ++x) {
                if (g[b][x].w == 0 || e_delta(g[xs][x]) < e_delta(g[b][x])) {
                    g[b][x] = g[xs][x], g[x][b] = g[x][xs];
                }
            }
            for (int x = 1; x <= n; ++x) {
                if (flo_from[xs][x]) {
                    flo_from[b][x] = xs;
                }
            }
        }
        set_slack(b);
    }
    void expand_blossom(int b) {
        for (int i = 0; i < flo[b].size(); ++i) {
            set_st(flo[b][i], flo[b][i]);
        }
        int xr = flo_from[b][g[b][pa[b]].u], pr = get_pr(b, xr);
        for (int i = 0; i < pr; i += 2) {
            int xs = flo[b][i], xns = flo[b][i + 1];
            pa[xs] = g[xns][xs].u;
            S[xs] = 1, S[xns] = 0;
            slack[xs] = 0, set_slack(xns);
            q_push(xns);
        }
        S[xr] = 1, pa[xr] = pa[b];
        for (int i = pr + 1; i < flo[b].size(); ++i) {
            int xs = flo[b][i];
            S[xs] = -1, set_slack(xs);
        }
        st[b] = 0;
    }
    bool on_found_edge(const edge &e) {
        int u = st[e.u], v = st[e.v];
        if (S[v] == -1) {
            pa[v] = e.u, S[v] = 1;
            int nu = st[match[v]];
            slack[v] = slack[nu] = 0;
            S[nu] = 0, q_push(nu);
        } else if (S[v] == 0) {
            int lca = get_lca(u, v);
            if (!lca) {
                return augment(u, v), augment(v, u), true;
            } else {
                add_blossom(u, lca, v);
            }
        }
        return false;
    }
    bool bfs() {
        memset(S + 1, -1, sizeof(int) * n_x);
        memset(slack + 1, 0, sizeof(int) * n_x);
        q = queue<int>();
        for (int x = 1; x <= n_x; ++x) {
            if (st[x] == x && !match[x]) {
                pa[x] = S[x] = 0;
                q_push(x);
            }
        }
        if (q.empty()) return false;
        while (1) {
            while (q.size()) {
                int u = q.front();
                q.pop();
                if (S[st[u]] == 1) continue;
                for (int v = 1; v <= n; ++v) {
                    if (g[u][v].w > 0 && st[u] != st[v]) {
                        if (e_delta(g[u][v]) == 0) {
                            if (on_found_edge(g[u][v])) return true;
                        } else {
                            update_slack(u, st[v]);
                        }
                    }
                }
            }
            int d = inf;
            for (int b = n + 1; b <= n_x; ++b) {
                if (st[b] == b && S[b] == 1) {
                    d = min(d, lab[b] / 2);
                }
            }
            for (int x = 1; x <= n_x; ++x) {
                if (st[x] == x && slack[x]) {
                    if (S[x] == -1) {
                        d = min(d, e_delta(g[slack[x]][x]));
                    } else if (S[x] == 0) {
                        d = min(d, e_delta(g[slack[x]][x]) / 2);
                    }
                }
            }
            for (int u = 1; u <= n; ++u) {
                if (S[st[u]] == 0) {
                    if (lab[u] <= d) return 0;
                    lab[u] -= d;
                } else if (S[st[u]] == 1) {
                    lab[u] += d;
                }
            }
            for (int b = n + 1; b <= n_x; ++b) {
                if (st[b] == b) {
                    if (S[st[b]] == 0) {
                        lab[b] += d * 2;
                    } else if (S[st[b]] == 1) {
                        lab[b] -= d * 2;
                    }
                }
            }
            q = queue<int>();
            for (int x = 1; x <= n_x; ++x) {
                if (st[x] == x && slack[x] && st[slack[x]] != x && e_delta(g[slack[x]][x]) == 0) {
                    if (on_found_edge(g[slack[x]][x])) return true;
                }
            }
            for (int b = n + 1; b <= n_x; ++b) {
                if (st[b] == b && S[b] == 1 && lab[b] == 0) {
                    expand_blossom(b);
                }
            }
        }
        return false;
    }
    pair<i64, int> work() {
        memset(match + 1, 0, sizeof(int) * n);
        n_x = n;
        int n_matches = 0;
        i64 tot_weight = 0;
        for (int u = 0; u <= n; ++u) {
            st[u] = u;
            flo[u].clear();
        }
        int w_max = 0;
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                flo_from[u][v] = (u == v ? u : 0);
                w_max = max(w_max, g[u][v].w);
            }
        }
        for (int u = 1; u <= n; ++u) {
            lab[u] = w_max;
        }
        while (bfs()) ++n_matches;
        for (int u = 1; u <= n; ++u) {
            if (match[u] && match[u] < u) {
                tot_weight += g[u][match[u]].w;
            }
        }
        return {tot_weight, n_matches};
    }
    auto getMatch() {
        vector<array<int, 2>> ans;
        for (int i = 1; i <= n; i++) {
            if (match[i]) {
                ans.push_back({i, match[i]});
            }
        }
        return ans;
    }
};

signed main() {
    int n, m;
    cin >> n >> m;
    
    Graph graph(n);
    while (m--) {
        int x, y, w;
        cin >> x >> y >> w;
        graph.add(x, y, w);
    }
    cout << graph.work().first << "\n";
    auto ans = match();
}