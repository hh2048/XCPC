/**   字典树 Trie（例题）
 *    2023-09-26: https://qoj.ac/submission/188993
**/
constexpr int N = 1 << 18;

int mx[30][N];

void build(int d, int p, int l, int r, const std::vector<int> &v) {
    if (r - l == 1) {
        mx[d][p] = v[l];
        return;
    }
    int m = (l + r) / 2;
    build(d, 2 * p, l, m, v);
    build(d, 2 * p + 1, m, r, v);
    mx[d][p] = std::max(mx[d][2 * p], mx[d][2 * p + 1]);
}

int query(int d, int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
        return -1;
    }
    if (l >= x && r <= y) {
        return mx[d][p];
    }
    int m = (l + r) / 2;
    return std::max(query(d, 2 * p, l, m, x, y), query(d, 2 * p + 1, m, r, x, y));
}

int main() {
    int N, Q;
    std::cin >> N >> Q;
    
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    
    std::vector nxt(N + 1, std::vector<int>(30, N));
    for (int i = N - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        for (int j = 0; j < 30; j++) {
            if (A[i] >> j & 1) {
                nxt[i][j] = i;
            }
        }
    }
    
    std::vector lst(N + 1, std::vector<int>(30, 0));
    for (int i = 0; i < N; i++) {
        lst[i + 1] = lst[i];
        for (int j = 0; j < 30; j++) {
            if (A[i] >> j & 1) {
                lst[i + 1][j] = i + 1;
            }
        }
    }
    std::vector<int> val(N, -1);
    for (int j = 29; j >= 0; j--) {
        for (int i = 0; i < N; i++) {
            if (A[i] >> j & 1) {
                val[i] = j;
            }
        }
        build(j, 1, 0, N, val);
    }
}