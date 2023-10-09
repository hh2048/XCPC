struct String {
    int MOD, BASE;
    vector<int> val;

    String(int MOD, int BASE, int N) {
        init(MOD, BASE, N);
    }
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
    int operator[](const int &s) {
        return val[s];
    }
    int operator[](const string &s) {
        return get(s);
    }
    int modify(int x, string &s, int idx, char now) {
        int n = s.size() - 1;
        return (x + val[n - idx] * (now - s[idx]) % MOD + MOD) % MOD;
    }
};

const int N = 1E5;
const int mod = 1E9 + 7;
const int base = 127;