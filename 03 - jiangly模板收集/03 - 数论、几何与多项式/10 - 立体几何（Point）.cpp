/**   立体几何
 *    2023-09-25 (i64): https://qoj.ac/submission/188519
 *    2023-09-28 (double): https://qoj.ac/submission/190463
**/
using i64 = long long;
using real = double;

struct Point {
    real x = 0;
    real y = 0;
    real z = 0;
};

Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Point operator*(const Point &a, real b) {
    return {a.x * b, a.y * b, a.z * b};
}

Point operator/(const Point &a, real b) {
    return {a.x / b, a.y / b, a.z / b};
}

real length(const Point &a) {
    return std::hypot(a.x, a.y, a.z);
}

Point normalize(const Point &a) {
    real l = length(a);
    return {a.x / l, a.y / l, a.z / l};
}

real getAng(real a, real b, real c) {
    return std::acos((a * a + b * b - c * c) / 2 / a / b);
}

std::ostream &operator<<(std::ostream &os, const Point &a) {
    return os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
}

real dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross(const Point &a, const Point &b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}