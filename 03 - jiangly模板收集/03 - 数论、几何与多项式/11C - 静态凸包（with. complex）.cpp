/**   静态凸包（with. std::complex）
 *    2022-02-04: https://loj.ac/s/1370861
**/
using Point = std::complex<i64>;

#define x real
#define y imag

auto dot(const Point &a, const Point &b) {
    return (std::conj(a) * b).x();
}

auto cross(const Point &a, const Point &b) {
    return (std::conj(a) * b).y();
}

auto rot(const Point &p) {
    return Point(-p.y(), p.x());
}

auto complexHull(std::vector<Point> a) {
    std::sort(a.begin(), a.end(), [&](auto a, auto b) {
        if (a.x() != b.x()) {
            return a.x() < b.x();
        } else {
            return a.y() < b.y();
        }
    });

    std::vector<Point> l, h;

    for (auto p : a) {
        while (l.size() > 1 && cross(l.back() - l[l.size() - 2], p - l.back()) <= 0) {
            l.pop_back();
        }

        while (h.size() > 1 && cross(h.back() - h[h.size() - 2], p - h.back()) >= 0) {
            h.pop_back();
        }

        l.push_back(p);
        h.push_back(p);
    }

    std::reverse(h.begin(), h.end());

    h.insert(h.end(), l.begin() + 1, l.end() - 1);

    return h;
}

int sgn(Point p) {
    if (p.y() > 0 || (p.y() == 0 && p.x() < 0)) {
        return 0;
    } else {
        return 1;
    }
}