namespace Geometry { // 立体几何基础
    struct Point3 {
        ld x, y, z;
        Point3(ld x_ = 0, ld y_ = 0, ld z_ = 0) : x(x_), y(y_), z(z_) {}
        Point3 &operator+=(Point3 p) & {
            return x += p.x, y += p.y, z += p.z, *this;
        }
        Point3 &operator-=(Point3 p) & {
            return x -= p.x, y -= p.y, z -= p.z, *this;
        }
        Point3 &operator*=(Point3 p) & {
            return x *= p.x, y *= p.y, z *= p.z, *this;
        }
        Point3 &operator*=(ld t) & {
            return x *= t, y *= t, z *= t, *this;
        }
        Point3 &operator/=(ld t) & {
            return x /= t, y /= t, z /= t, *this;
        }
        friend Point3 operator+(Point3 a, Point3 b) { return a += b; }
        friend Point3 operator-(Point3 a, Point3 b) { return a -= b; }
        friend Point3 operator*(Point3 a, Point3 b) { return a *= b; }
        friend Point3 operator*(Point3 a, ld b) { return a *= b; }
        friend Point3 operator*(ld a, Point3 b) { return b *= a; }
        friend Point3 operator/(Point3 a, ld b) { return a /= b; }
        friend auto &operator>>(istream &is, Point3 &p) {
            return is >> p.x >> p.y >> p.z;
        }
        friend auto &operator<<(ostream &os, Point3 p) {
            return os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        }
    };
    struct Line3 {
        Point3 a, b;
    };
    struct Plane {
        Point3 u, v, w;
    };

    ld len(P3 p) { // 原点到当前点的距离计算
        return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    }
    P3 crossEx(P3 a, P3 b) { // 叉乘
        P3 ans;
        ans.x = a.y * b.z - a.z * b.y;
        ans.y = a.z * b.x - a.x * b.z;
        ans.z = a.x * b.y - a.y * b.x;
        return ans;
    }
    ld cross(P3 a, P3 b) {
        return len(crossEx(a, b));
    }
    ld dot(P3 a, P3 b) { // 点乘
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    P3 getVec(Plane s) { // 获取平面法向量
        return crossEx(s.u - s.v, s.v - s.w);
    }
    ld dis(P3 a, P3 b) { // 三维欧几里得距离公式
        ld val = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
        return sqrt(val);
    }
    P3 standardize(P3 vec) { // 将三维向量转换为单位向量
        return vec / len(vec);
    }
} // namespace Geometry