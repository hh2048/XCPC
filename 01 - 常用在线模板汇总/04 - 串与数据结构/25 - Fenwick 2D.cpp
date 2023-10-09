struct BIT_2D {
    int n, m;
    vector<vector<int>> w;
    
    BIT_2D(int n, int m) : n(n), m(m) {
        w.resize(n + 1, vector<int>(m + 1));
    }
    void add(int x, int y, int k) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                w[i][j] += k;
            }
        }
    }
    void add(int x, int y, int X, int Y, int k) { // 区块修改：二维差分
        X++, Y++;
        add(x, y, k), add(X, y, -k);
        add(X, Y, k), add(x, Y, -k);
    }
    int ask(int x, int y) { // 单点查询
        int ans = 0;
        for (int i = x; i; i -= i & -i) {
            for (int j = y; j; j -= j & -j) {
                ans += w[i][j];
            }
        }
        return ans;
    }
    int ask(int x, int y, int X, int Y) { // 区块查询：二维前缀和
        x--, y--;
        return ask(X, Y) - ask(x, Y) - ask(X, y) + ask(x, y);
    }
};