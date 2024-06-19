/**   扩展欧几里得（exgcd）
 *    2023-10-09: https://atcoder.jp/contests/tenka1-2017/submissions/46411797
**/
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
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