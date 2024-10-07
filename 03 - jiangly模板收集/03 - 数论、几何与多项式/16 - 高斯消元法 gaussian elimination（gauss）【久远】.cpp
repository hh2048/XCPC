/**   高斯消元法（gaussian elimination）【久远】
 *    2020-08-30: https://codeforces.com/gym/102129/submission/91334513
**/
std::vector<int> operator*(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    std::vector<int> res(lhs.size() + rhs.size() - 1);
    for (int i = 0; i < int(lhs.size()); ++i)
        for (int j = 0; j < int(rhs.size()); ++j)
            res[i + j] = (res[i + j] + 1ll * lhs[i] * rhs[j]) % P;
    return res;
}
std::vector<int> operator%(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    auto res = lhs;
    int m = rhs.size() - 1;
    int inv = power(rhs.back(), P - 2);
    for (int i = res.size() - 1; i >= m; --i) {
        int x = 1ll * inv * res[i] % P;
        for (int j = 0; j < m; ++j)
            res[i - m + j] = (res[i - m + j] + 1ll * (P - x) * rhs[j]) % P;
    }
    if (int(res.size()) > m)
        res.resize(m);
    return res;
}
std::vector<int> gauss(std::vector<std::vector<int>> a, std::vector<int> b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        int r = i;
        while (a[r][i] == 0)
            ++r;
        std::swap(a[i], a[r]);
        std::swap(b[i], b[r]);
        int inv = power(a[i][i], P - 2);
        for (int j = i; j < n; ++j)
            a[i][j] = 1ll * a[i][j] * inv % P;
        b[i] = 1ll * b[i] * inv % P;
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            int x = a[j][i];
            for (int k = i; k < n; ++k)
                a[j][k] = (a[j][k] + 1ll * (P - x) * a[i][k]) % P;
            b[j] = (b[j] + 1ll * (P - x) * b[i]) % P;
        }
    }
    return b;
}
/**   高斯消元法（gaussian elimination）【久远】
 *    2020-12-02: https://www.codechef.com/viewsolution/39942900
**/
std::vector<double> gauss(std::vector<std::vector<double>> a, std::vector<double> b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        double x = a[i][i];
        for (int j = i; j < n; ++j) a[i][j] /= x;
        b[i] /= x;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            x = a[j][i];
            for (int k = i; k < n; ++k) a[j][k] -= a[i][k] * x;
            b[j] -= b[i] * x;
        }
    }
    return b;
}