using pii = pair<int, int>;
struct String {
    int MOD, BASE;
    vector<int> val;
    String() {}
    void init(int MOD, int BASE, int N) {
        this->MOD = MOD;
        this->BASE = BASE;
        val.resize(N + 1);
        val[0] = 1;
        for (int i = 1; i <= N; i++) {
            val[i] = (val[i - 1] * BASE) % MOD;
        }
    }
    int get(const string &s) {
        int ans = 0;
        for (auto i : s) {
            ans = (ans * BASE + i) % MOD;
        }
        return ans;
    }
    int operator[](const string &s) {
        return get(s);
    }
    int modify(int x, string &s, int idx, char now) {
        int n = s.size() - 1;
        return (x + val[n - idx] * (now - s[idx]) % MOD + MOD) % MOD;
    }
};
struct StringHash {
    String chk1, chk2;
    StringHash(int n = 1 << 21) {
        int mod1 = 1E9 + 7, base1 = 127;
        int mod2 = 1E9 + 9, base2 = 131;
        chk1.init(mod1, base1, n);
        chk2.init(mod2, base2, n);
    }
    pii operator[](const string &s) {
        return {chk1[s], chk2[s]};
    }
    pii modify(pii x, string &s, int idx, char now) {
        return {chk1.modify(x.first, s, idx, now), chk2.modify(x.second, s, idx, now)};
    }
};