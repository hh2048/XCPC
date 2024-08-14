/**   扩展欧几里得（exgcd）
 *    2024-08-07: https://codeforces.com/contest/1993/submission/275110715
**/
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
 
// ax + b = 0 (mod m)
std::pair<i64, i64> sol(i64 a, i64 b, i64 m) {
    assert(m > 0);
    b *= -1;
    i64 x, y;
    i64 g = exgcd(a, m, x, y);
    if (g < 0) {
        g *= -1;
        x *= -1;
        y *= -1;
    }
    if (b % g != 0) {
        return {-1, -1};
    }
    x = x * (b / g) % (m / g);
    if (x < 0) {
        x += m / g;
    }
    return {x, m / g};
}

/**   扩展欧几里得（exgcd）
 *    2023-09-05: https://qoj.ac/submission/165983
**/
std::array<i64, 3> exgcd(i64 a, i64 b) {
    if (!b) {
        return {a, 1, 0};
    }
    auto [g, x, y] = exgcd(b, a % b);
    return {g, y, x - a / b * y};
}