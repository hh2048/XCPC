## 第十三章：卡常

### 基础算法 | 最大公约数 `gcd` | 位运算加速

略快于内置函数。

```c++
LL gcd(LL a, LL b) {
    #define tz __builtin_ctzll
    if (!a || !b) return a | b;
    int t = tz(a | b);
    a >>= tz(a);
    while (b) {
        b >>= tz(b);
        if (a > b) swap(a, b);
        b -= a;
    }
    return a << t;
    #undef tz
}
```

### 数论 | 质数判定 | 预分类讨论加速

常数优化，达到 $\mathcal O(\frac {\sqrt N}{3})$ 。

```c++
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 6 != 1 && n % 6 != 5) return false;
    for (int i = 5, j = n / i; i <= j; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
```

### 数论 | 质数判定 | Miller-Rabin

借助蒙哥马利模乘加速取模运算。

```c++
using u64 = uint64_t;
using u128 = __uint128_t;

struct Montgomery {
    u64 m, m2, im, l1, l2;
    Montgomery() {}
    Montgomery(u64 m) : m(m) {
        l1 = -(u64)m % m, l2 = -(u128)m % m;
        m2 = m << 1, im = m;
        for (int i = 0; i < 5; i++) {
            im *= 2 - m * im;
        }
    }
    inline u64 operator()(i64 a, i64 b) const {
        u128 c = (u128)a * b;
        return u64(c >> 64) + m - u64((u64)c * im * (u128)m >> 64);
    }
    inline u64 reduce(u64 a) const {
        a = m - u64(a * im * (u128)m >> 64);
        return a >= m ? a - m : a;
    }
    inline u64 trans(i64 a) const {
        return (*this)(a, l2);
    }

    inline u64 mul(i64 a, i64 b) const {
        u64 r = (*this)(trans(a), trans(b));
        return reduce(r);
    }
    u64 pow(u64 a, u64 n) {
        u64 r = l1;
        a = trans(a);
        for (; n; n >>= 1, a = (*this)(a, a)) {
            if (n & 1) r = (*this)(r, a);
        }
        return reduce(r);
    }
};

bool isprime(i64 n) {
    if (n < 2 || n % 6 % 4 != 1) {
        return (n | 1) == 3;
    }
    u64 s = __builtin_ctzll(n - 1), d = n >> s;
    Montgomery M(n);
    for (i64 a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        u64 p = M.pow(a, d), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) {
            p = M.mul(p, p);
        }
        if (p != n - 1 && i != s) return false;
    }
    return true;
}
```

### 数论 | 质因数分解 | Pollard-Rho

```c++
struct Montgomery {} M(10); // 注意预赋值
bool isprime(i64 n) {}
 
i64 rho(i64 n) {
    if (!(n & 1)) return 2;
    i64 x = 0, y = 0, prod = 1;
    auto f = [&](i64 x) -> i64 {
        return M.mul(x, x) + 5; // 这里的种子能被 hack ，如果是在线比赛，请务必 rand 生成
    };
    for (int t = 30, z = 0; t % 64 || gcd(prod, n) == 1; ++t) {
        if (x == y) x = ++z, y = f(x);
        if (i64 q = M.mul(prod, x + n - y)) prod = q;
        x = f(x), y = f(f(y));
    }
    return gcd(prod, n);
}
 
vector<i64> factorize(i64 x) {
    vector<i64> res;
    auto f = [&](auto f, i64 x) {
        if (x == 1) return;
        M = Montgomery(x); // 重设模数
        if (isprime(x)) return res.push_back(x);
        i64 y = rho(x);
        f(f, y), f(f, x / y);
    };
    f(f, x), sort(res.begin(), res.end());
    return res;
}
```

### 数论 | 取模运算类 | 蒙哥马利模乘

```c++
using u64 = uint64_t;
using u128 = __uint128_t;

struct Montgomery {
    u64 m, m2, im, l1, l2;
    Montgomery() {}
    Montgomery(u64 m) : m(m) {
        l1 = -(u64)m % m, l2 = -(u128)m % m;
        m2 = m << 1, im = m;
        for (int i = 0; i < 5; i++) im *= 2 - m * im;
    }
    inline u64 operator()(i64 a, i64 b) const {
        u128 c = (u128)a * b;
        return u64(c >> 64) + m - u64((u64)c * im * (u128)m >> 64);
    }
    inline u64 reduce(u64 a) const {
        a = m - u64(a * im * (u128)m >> 64);
        return a >= m ? a - m : a;
    }
    inline u64 trans(i64 a) const {
        return (*this)(a, l2);
    }
    
    inline u64 add(i64 a, i64 b) const {
        u64 c = trans(a) + trans(b);
        if (c >= m2) c -= m2;
        return reduce(c);
    }
    inline u64 sub(i64 a, i64 b) const {
        u64 c = trans(a) - trans(b);
        if (c >= m2) c += m2;
        return reduce(c);
    }
    inline u64 mul(i64 a, i64 b) const {
        return reduce((*this)(trans(a), trans(b)));
    }
    inline u64 div(i64 a, i64 b) const {
        a = trans(a), b = trans(b);
        u64 n = m - 2, inv = l1;
        for (; n; n >>= 1, b = (*this)(b, b))
            if (n & 1) inv = (*this)(inv, b);
        return reduce((*this)(a, inv));
    }
    u64 pow(u64 a, u64 n) {
        u64 r = l1;
        a = trans(a);
        for (; n; n >>= 1, a = (*this)(a, a))
            if (n & 1) r = (*this)(r, a);
        return reduce(r);
    }
};
```

### 网络流 | 最大流 | 预流推进 HLPP

理论最坏复杂度为 $\mathcal O(N^2\sqrt M)$ ，例题范围：$N=1200,\ m=1.2\times 10^5$ 。

```c++
template <typename T> struct PushRelabel {
    const int inf = 0x3f3f3f3f;
    const T INF = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int to, cap, flow, anti;
        Edge(int v = 0, int w = 0, int id = 0) : to(v), cap(w), flow(0), anti(id) {}
    };
    vector<vector<Edge>> e; 
    vector<vector<int>> gap;
    vector<T> ex; // 超额流
    vector<bool> ingap;
    vector<int> h;
    int n, gobalcnt, maxH = 0;
    T maxflow = 0;

    PushRelabel(int n) : n(n), e(n + 1), ex(n + 1), gap(n + 1) {}
    void addedge(int u, int v, int w) {
        e[u].push_back({v, w, (int)e[v].size()});
        e[v].push_back({u, 0, (int)e[u].size() - 1});
    }
    void PushEdge(int u, Edge &edge) {
        int v = edge.to, d = min(ex[u], 1LL * edge.cap - edge.flow);
        ex[u] -= d;
        ex[v] += d;
        edge.flow += d;
        e[v][edge.anti].flow -= d;
        if (h[v] != inf && d > 0 && ex[v] == d && !ingap[v]) {
            ++gobalcnt;
            gap[h[v]].push_back(v);
            ingap[v] = 1;
        }
    }
    void PushPoint(int u) {
        for (auto k = e[u].begin(); k != e[u].end(); k++) {
            if (h[k->to] + 1 == h[u] && k->cap > k->flow) {
                PushEdge(u, *k);
                if (!ex[u]) break;
            }
        }
        if (!ex[u]) return;
        if (gap[h[u]].empty()) {
            for (int i = h[u] + 1; i <= min(maxH, n); i++) {
                for (auto v : gap[i]) {
                    ingap[v] = 0;
                }
                gap[i].clear();
            }
        }
        h[u] = inf;
        for (auto [to, cap, flow, anti] : e[u]) {
            if (cap > flow) {
                h[u] = min(h[u], h[to] + 1);
            }
        }
        if (h[u] >= n) return;
        maxH = max(maxH, h[u]);
        if (!ingap[u]) {
            gap[h[u]].push_back(u);
            ingap[u] = 1;
        }
    }
    void init(int t, bool f = 1) {
        ingap.assign(n + 1, 0);
        for (int i = 1; i <= maxH; i++) {
            gap[i].clear();
        }
        gobalcnt = 0, maxH = 0;
        queue<int> q;
        h.assign(n + 1, inf);
        h[t] = 0, q.push(t);
        while (q.size()) {
            int u = q.front();
            q.pop(), maxH = h[u];
            for (auto &[v, cap, flow, anti] : e[u]) {
                if (h[v] == inf && e[v][anti].cap > e[v][anti].flow) {
                    h[v] = h[u] + 1;
                    q.push(v);
                    if (f) {
                        gap[h[v]].push_back(v);
                        ingap[v] = 1;
                    }
                }
            }
        }
    }
    T work(int s, int t) {
        init(t, 0);
        if (h[s] == inf) return maxflow;
        h[s] = n;
        ex[s] = INF;
        ex[t] = -INF;
        for (auto k = e[s].begin(); k != e[s].end(); k++) {
            PushEdge(s, *k);
        }
        while (maxH > 0) {
            if (gap[maxH].empty()) {
                maxH--;
                continue;
            }
            int u = gap[maxH].back();
            gap[maxH].pop_back();
            ingap[u] = 0;
            PushPoint(u);
            if (gobalcnt >= 10 * n) {
                init(t);
            }
        }
        ex[s] -= INF;
        ex[t] += INF;
        return maxflow = ex[t];
    }
};
```

### 快读

注意读入到文件结尾才结束，直接运行会无输出。

```c++
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline char getc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? 0 : *p1++;
}
template<typename T> void Cin(T &a) {
    T ans = 0;
    bool f = 0;
    char c = getc();
    for (; c < '0' || c > '9'; c = getc()) {
        if (c == '-') f = -1;
    }
    for (; c >= '0' && c <= '9'; c = getc()) {
        ans = ans * 10 + c - '0';
    }
    a = f ? -ans : ans;
}
template<typename T, typename... Args> void Cin(T &a, Args &...args) {
    Cin(a), Cin(args...);
}
template<typename T> void Cout(T x) { // 注意，这里输出不带换行
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) Cout(x / 10);
    putchar(x % 10 + '0');
}
```

<div style="page-break-after:always">/END/</div>