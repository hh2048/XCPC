namespace LP { // Longest_Path，最长路封装（Topsort）
    vector<PII> ver[N];
    int deg[N];
    int d[N];

    void clear(int n) {
        FOR(i, 1, n) {
            ver[i].clear();
            deg[i] = 0;
        }
    }
    void add(int x, int y, int w) {
        ver[x].pb({y, w});
        ++deg[y];
    }
    void topsort(int n, int s) {
        queue<int> q;
        FOR(i, 1, n) {
            if (deg[i] == 0) q.push(i);
        }
        fill(d + 1, d + 1 + n, -INFF);
        d[s] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto [y, w] : ver[x]) {
                d[y] = max(d[y], d[x] + w);
                --deg[y];
                if (deg[y] == 0) q.push(y);
            }
        }
    }
    void solve(int n, int s) {
        topsort(n, s);
    }
} // namespace LP
int main() {
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n) {
        int x, y, w;
        cin >> x >> y >> w;
        LP::add(x, y, w);
    }
    int start, end;
    cin >> start >> end; //输入源汇
    LP::solve(n, start);
    cout << LP::d[end] << endl;

    LP::clear(n); //清空
}