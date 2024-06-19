/**   自适应辛普森法 Simpson
 *    2023-09-02: https://qoj.ac/submission/161388
**/
const double Pi = std::acos(-1.0);
constexpr double EPS = 1e-9;
double v, r, d;
double f(double x) {
    double s = std::sin(x);
    return 1 / v / (std::sqrt(s * s + 3) - s);
}
double simpson(double l, double r) {
    return (f(l) + 4 * f((l + r) / 2) + f(r)) * (r - l) / 6;
}
double integral(double l, double r, double eps, double st) {
    double mid = (l + r) / 2;
    double sl = simpson(l, mid);
    double sr = simpson(mid, r);
    if (std::abs(sl + sr - st) <= 15 * eps)
        return sl + sr + (sl + sr - st) / 15;
    return integral(l, mid, eps / 2, sl) + integral(mid, r, eps / 2, sr);
}
double integral(double l, double r) {
    return integral(l, r, EPS, simpson(l, r));
}