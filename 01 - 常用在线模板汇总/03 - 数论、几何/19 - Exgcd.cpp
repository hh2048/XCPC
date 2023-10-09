template <class T> T sign(const T &a) {
    return a == 0 ? 0 : (a < 0 ? -1 : 1);
}
template <class T> T ceil(const T &a, const T &b) {
    T A = abs(a), B = abs(b);
    assert(b != 0);
    return sign(a) * sign(b) > 0 ? (A + B - 1) / B : -A / B;
}
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

auto clac = [&](int a, int b, int c) -> void {
    int x, y, d = exgcd(a, b, x, y);
    if (c % d != 0) {
        cout << -1 << endl;
        return;
    }
    x *= c / d, y *= c / d;
    int p = b / d, q = a / d, k;
    if (x < 0) {
        k = ceil(1 - x, p);
        x += p * k;
        y -= q * k;
    }
    else if (x >= 0) { //将x提高到最小正整数
        k = (x - 1) / p;
        x -= p * k; //将x降低到最小正整数
        y += q * k;
    }
    if (y > 0) { //有正整数解
        cout << (y - 1) / q + 1 << endl; //将y减到1的方案数即为解的个数
        cout << x << endl; //当前的x即为最小正整数x
        cout << (y - 1) % q + 1 << endl; //将y取到最小正整数
        cout << x + (y - 1) / q * p << endl; //将x提升到最大
        cout << y << endl; //特解即为y最大值      
    } else { //无整数解
        cout << x << endl; //当前的x即为最小的正整数x
        cout << y + q * ceil(1 - y, q) << endl; //将y提高到正整数
    }
};