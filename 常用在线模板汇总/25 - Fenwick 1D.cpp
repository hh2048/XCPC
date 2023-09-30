struct BIT {
    int n;
    vector<int> w;

    BIT() {}
    BIT(int n) {
        this->n = n; // 这里必须写 n ，否则会RE
        w.resize(n + 1);
    }
    void add(int x, int k) {
        for (; x <= n; x += x & -x) {
            w[x] += k;
        }
    }
    void add(int x, int y, int k) {
        add(x, k), add(y, -k);
    }
    int ask(int x) {
        int ans = 0;
        for (; x; x -= x & -x) {
            ans += w[x];
        }
        return ans;
    }
    int ask(int x, int y) {
        return ask(y) - ask(x - 1);
    }
};