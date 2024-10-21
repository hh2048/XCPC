/**   字典树 Trie
 *    2024-06-18: https://cf.dianhsu.com/gym/105222/submission/266217560
 *    2024-06-04: https://codeforces.com/contest/1980/submission/263960334
**/
constexpr int N = 1E7;
constexpr int inf = 1E9;
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