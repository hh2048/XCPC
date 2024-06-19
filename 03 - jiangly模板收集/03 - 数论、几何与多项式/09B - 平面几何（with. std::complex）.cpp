/**   平面几何（with. std::complex）
 *    2023-09-04: https://qoj.ac/submission/164445
**/
using Point = std::complex<long double>;

#define x real
#define y imag

long double dot(const Point &a, const Point &b) {
    return (std::conj(a) * b).x();
}

long double cross(const Point &a, const Point &b) {
    return (std::conj(a) * b).y();
}

long double length(const Point &a) {
    return std::sqrt(dot(a, a));
}

long double dist(const Point &a, const Point &b) {
    return length(a - b);
}

long double get(const Point &a, const Point &b, const Point &c, const Point &d) {
    auto e = a + (b - a) * cross(c - a, d - a) / cross(b - a, d - c);
    return dist(d, e);
}