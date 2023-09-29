template<class T> constexpr T mypow(T n, int k) {
    T r = 1;
    for (; k; k /= 2, n *= n) {
        if (k % 2) {
            r *= n;
        }
    }
    return r;
}

template<int MOD> struct Zmod {
    int x;
    Zmod(int x = 0) : x(norm(x % MOD)) {}

    constexpr int norm(int x) const {
        if (x < 0) {
            x += MOD;
        }
        if (x >= MOD) {
            x -= MOD;
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Zmod operator-() const {
        Zmod val = norm(MOD - x);
        return val;
    }
    constexpr Zmod inv() const {
        assert(x != 0);
        return mypow(*this, MOD - 2);
    }
    friend constexpr auto &operator>>(istream &in, Zmod &j) {
        int v;
        in >> v;
        j = Zmod(v);
        return in;
    }
    friend constexpr auto &operator<<(ostream &o, const Zmod &j) {
        return o << j.val();
    }
    constexpr Zmod &operator++() { return x = norm(x + 1), *this; }
    constexpr Zmod &operator--() { return x = norm(x - 1), *this; }
    constexpr Zmod &operator+=(const Zmod &i) { return x = norm(x + i.x), *this; }
    constexpr Zmod &operator-=(const Zmod &i) { return x = norm(x - i.x), *this; }
    constexpr Zmod &operator*=(const Zmod &i) { return x = x * i.x % MOD, *this; }
    constexpr Zmod &operator/=(const Zmod &i) { return *this *= i.inv(); }
    constexpr Zmod &operator%=(const int &i) { return x %= i, *this; }
    friend constexpr Zmod operator+(const Zmod i, const Zmod j) { return Zmod(i) += j; }
    friend constexpr Zmod operator-(const Zmod i, const Zmod j) { return Zmod(i) -= j; }
    friend constexpr Zmod operator*(const Zmod i, const Zmod j) { return Zmod(i) *= j; }
    friend constexpr Zmod operator/(const Zmod i, const Zmod j) { return Zmod(i) /= j; }
    friend constexpr Zmod operator%(const Zmod i, const int j) { return Zmod(i) %= j; }
    friend constexpr bool operator==(const Zmod i, const Zmod j) { return i.val() == j.val(); }
    friend constexpr bool operator!=(const Zmod i, const Zmod j) { return i.val() != j.val(); }
    friend constexpr bool operator<(const Zmod i, const Zmod j) { return i.val() < j.val(); }
    friend constexpr bool operator>(const Zmod i, const Zmod j) { return i.val() > j.val(); }
};

constexpr int MOD[] = {998244353, 1000000007};
using Z = Zmod<MOD[1]>;

Z power(int n) {
    return mypow(Z(2), n);
}