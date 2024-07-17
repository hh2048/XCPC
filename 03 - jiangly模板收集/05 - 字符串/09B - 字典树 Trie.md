```cpp
/**   字典树 Trie
 *    2023-09-26: https://qoj.ac/submission/188957
**/
constexpr i64 inf = 1E18;

constexpr int N = 1E6 + 10;

int trie[N][26];
int tot;

int newNode() {
    tot++;
    std::fill(trie[tot], trie[tot] + 26, 0);
    val[tot] = inf;
    return tot;
}

void solve() {
    //* init
    tot = 0;
    newNode();

    //* insert
    for (int i = 0; i < N; i++) { 
        int p = 1;
        int l = S[i].size();
        for (int j = 0; j < l; j++) {
            int x = S[i][j] - 'a';
            if (!trie[p][x]) {
                trie[p][x] = newNode();
            }
            p = trie[p][x];
            //* 处理
            //* val[p] = std::min(val[p], l + K + f[(K - (l - j - 1) % K) % K]);
        }
    }
    
    //* query
    for (int i = 0; i < L; i++) {
        int p = 1;
        for (int j = i; j < L; j++) {
            int x = T[j] - 'a';
            p = trie[p][x];
            if (!p) {
                continue;
            }
            //* 处理
            //* dp[j + 1] = std::min(dp[j + 1], dp[i] + val[p]);
        }
    }
}
```

```cpp
/**   字典树 Trie
 *    2024-06-18: https://cf.dianhsu.com/gym/105222/submission/266217560?version=1.5
**/
int tot;
int trie[N][2];
int f[N];

int newNode() {
    int x = ++tot;
    trie[x][0] = trie[x][1] = 0;
    f[x] = inf;
    return x;
}
void add(int x, int i) {
    int p = 1;
    for (int j = 29; j >= 0; j--) {
        int &q = trie[p][x >> j & 1];
        if (q == 0) {
            q = newNode();
        }
        p = q;
        f[p] = std::min(f[p], i);
    }
}

int query(int a, int b) {
    int ans1 = inf, ans2 = inf;
    int p = 1;
    for (int i = 29; i >= 0; i--) {
        int d = a >> i & 1;
        int e = b >> i & 1;
        if (e) {
            ans1 = std::min(ans1, f[trie[p][d]]);
        } else {
            ans2 = std::min(ans2, f[trie[p][d ^ 1]]);
        }
        p = trie[p][e ^ d];
    }
    ans1 = std::min(ans1, f[p]);
    ans2 = std::min(ans2, f[p]);
    if (ans1 == inf || ans2 == inf) {
        return -1;
    }
    return std::max({1, ans1, ans2});
}
```

```cpp
/**   字典树 Trie
 *    2024-06-03: https://codeforces.com/contest/1980/submission/263960334
**/
int trie[N][2];
int cnt[N][2];
 
int tot = 0;
int newNode() {
    int x = ++tot;
    trie[x][0] = trie[x][1] = 0;
    cnt[x][0] = cnt[x][1] = 0;
    return x;
}
 
void add(int x, int d, int t = 1) {
    int p = 1;
    cnt[p][d] += t;
    for (int i = 29; i >= 0; i--) {
        int u = x >> i & 1;
        if (!trie[p][u]) {
            trie[p][u] = newNode();
        }
        p = trie[p][u];
        cnt[p][d] += t;
    }
}
 
int query(int x, int d) {
    int p = 1;
    if (!cnt[p][d]) {
        return 0;
    }
    int ans = 0;
    for (int i = 29; i >= 0; i--) {
        int u = x >> i & 1;
        if (cnt[trie[p][u ^ 1]][d]) {
            ans |= 1 << i;
            p = trie[p][u ^ 1];
        } else {
            p = trie[p][u];
        }
    }
    return ans;
}
```