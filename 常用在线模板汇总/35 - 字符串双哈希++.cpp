mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int r(int a, int b) { return rnd() % (b - a + 1) + a; }
int add(int a, int b, int mod) {
    a += b;
    return a >= mod ? a - mod : a;
}
int sub(int a, int b, int mod) {
    a -= b;
    return a < 0 ? a + mod : a;
}
int mul(int a, int b, int mod) {
    int r = a * b - mod * (int)(1.L / mod * a * b);
    return r - mod * (r >= mod) + mod * (r < 0);
}
int mypow(int a, int b, int mod) {
    int res(1);
    for (; b; b >>= 1, a = mul(a, a, mod)) {
        if (b & 1) res = mul(res, a, mod);
    }
    return res;
}
bool Miller_rabin(int n) { // 素数测试
    if (n <= 1) return false;
    vector<int> base = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (int p : base) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    int m = (n - 1) >> __builtin_ctz(n - 1);
    for (int p : base) {
        int t = m, a = mypow(p, m, n);
        while (t != n - 1 && a != 1 && a != n - 1) {
            a = mul(a, a, n);
            t *= 2;
        }
        if (a != n - 1 && t % 2 == 0) return false;
    }
    return true;
}
int findPrime(int n) {
    while (!Miller_rabin(n)) {
        n++;
    }
    return n;
}

using pii = pair<int, int>;

struct String {
    int MOD, BASE;
    vector<int> val;
    
    String() {}
    String(int MOD, int BASE, int N) { init(MOD, BASE, N); }
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
            ans = (ans * BASE + i - 'a') % MOD;
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
        int mod1 = findPrime(r(1E8, 5E8)), base1 = findPrime(r(2, 100));
        int mod2 = findPrime(r(mod1, 1E9)), base2 = findPrime(r(base1, 200));
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