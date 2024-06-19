/**   生成函数（q-int）
 *    2023-09-04: https://qoj.ac/submission/163986
**/
using i64 = long long;
using i128 = __int128;

i64 power(i64 a, i64 b, i64 p) {
    i64 res = 1;
    for (; b; b /= 2, a = i128(a) * a % p) {
        if (b % 2) {
            res = i128(res) * a % p;
        }
    }
    return res;
}

std::pair<int, int> qint(int q, int n, int p) {
    q %= p;
    for (int x = 2; x * x <= n; x++) {
        if (n % x == 0) {
            auto [v1, e1] = qint(q, x, p);
            auto [v2, e2] = qint(power(q, x, p), n / x, p);
            return {1LL * v1 * v2 % p, e1 + e2};
        }
    }
    if (q == 1) {
        if (n == p) {
            return {0, 1};
        }
        return {n, 0};
    }
    // std::cerr << q << " " << n << " " << p << "\n";
    i64 v = 1 - power(q, n, 1LL * p * p);
    if (v < 0) {
        v += 1LL * p * p;
    }
    assert(v != 0);
    int inv = power(1 - q + p, p - 2, p);
    if (v % p == 0) {
        return {(v / p) * inv % p, 1};
    } else {
        return {v % p * inv % p, 0};
    }
}