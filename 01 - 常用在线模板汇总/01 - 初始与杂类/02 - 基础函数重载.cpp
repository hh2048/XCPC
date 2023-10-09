int mypow(int n, int k, int p = MOD) { // 复杂度是 log N
    int r = 1;
    for (; k; k >>= 1, n = n * n % p) {
        if (k & 1) r = r * n % p;
    }
    return r;
}
int mylcm(int x, int y) {
    return x / __gcd(x, y) * y;
}
int Log2(int x) { // 计算log2(x)，向下取整
    return 31 - __builtin_clz(x);
}
int ceiledLog2(int x) { // 计算log2(x)，但是向上取整
    return Log2(x) + (__builtin_popcount(x) != 1);
}
template <class T> T sign(const T &a) {
    return a == 0 ? 0 : (a < 0 ? -1 : 1);
}
template <class T> T floor(const T &a, const T &b) { // 注意大数据计算时会丢失精度
    T A = abs(a), B = abs(b);
    assert(B != 0);
    return sign(a) * sign(b) > 0 ? A / B : -(A + B - 1) / B;
}
template <class T> T ceil(const T &a, const T &b) { // 注意大数据计算时会丢失精度
    T A = abs(a), B = abs(b);
    assert(b != 0);
    return sign(a) * sign(b) > 0 ? (A + B - 1) / B : -A / B;
}