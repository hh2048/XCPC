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