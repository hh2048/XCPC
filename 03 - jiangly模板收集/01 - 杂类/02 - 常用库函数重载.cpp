using i64 = long long;
using i128 = __int128;

/**   上取整下取整
 *    2023-10-15: https://codeforces.com/contest/293/submission/228297248
**/
i64 ceilDiv(i64 n, i64 m) {
    if (n >= 0) {
        return (n + m - 1) / m;
    } else {
        return n / m;
    }
}
 
i64 floorDiv(i64 n, i64 m) {
    if (n >= 0) {
        return n / m;
    } else {
        return (n - m + 1) / m;
    }
}

/**   最大值赋值
 *    2023-09-30: https://codeforces.com/contest/1874/submission/226069129
**/
template<class T>
void chmax(T &a, T b) {
    if (a < b) {
        a = b;
    }
}

/**   最大公约数
 *    -: -
**/
i128 gcd(i128 a, i128 b) {
    return b ? gcd(b, a % b) : a;
}

/**   精确开平方
 *    2024-03-02: https://qoj.ac/submission/343317
**/
i64 sqrt(i64 n) {
    i64 s = std::sqrt(n);
    while (s * s > n) {
        s--;
    }
    while ((s + 1) * (s + 1) <= n) {
        s++;
    }
    return s;
}

/**   精确开平方
 *    2023-09-19: https://qoj.ac/submission/183430
**/
i64 get(i64 n) {
    i64 u = std::sqrt(2.0L * n);
    while (u * (u + 1) / 2 < n) {
        u++;
    }
    while (u * (u - 1) / 2 + 1 > n) {
        u--;
    }
    return u;
}