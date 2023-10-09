struct BIT {
    int n;
    vector<int> w;

    BIT() {}
    BIT(int n) {
        this->n = n; // 注意 n 不能 +1
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
    int kth(int k) { // ex: 查找第k大的值
        int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            int val = ans + (1 << i);
            if (val < n && w[val] < k) {
                k -= w[val];
                ans = val;
            }
        }
        return ans + 1;
    }
    int get(auto val) { // ex: 获取逆序对数量
        this->n = val.size() - 1; // 注意 n 不能 +1
        w.resize(n + 1);

        vector<pair<int, int>> alls;
        for (int i = 1; i <= n; i++) {
            alls.emplace_back(val[i], i);
        }
        sort(alls.begin(), alls.end());

        int ans = 0;
        for (auto [val, idx] : alls) {
            ans += ask(idx + 1, n);
            add(idx, 1);
        }
        return ans;
    }
};