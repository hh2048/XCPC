namespace Geometry { // 二维凸包
    template<class T> vector<Point<T>> staticConvexHull(vector<Point<T>> A, int flag = 1) {
        int n = A.size();
        if (n <= 2) { // 特判
            return A;
        }
        vector<Point<T>> ans(n * 2);
        sort(A.begin(), A.end());
        int now = -1;
        for (int i = 0; i < n; i++) { // 维护下凸包
            while (now > 0 && cross(A[i], ans[now], ans[now - 1]) < flag) {
                now--;
            }
            ans[++now] = A[i];
        }
        int pre = now;
        for (int i = n - 2; i >= 0; i--) { // 维护上凸包
            while (now > pre && cross(A[i], ans[now], ans[now - 1]) < flag) {
                now--;
            }
            ans[++now] = A[i];
        }
        ans.resize(now);
        return ans;
    }

    template<class T> bool turnRight(Pt a, Pt b) {
        return cross(a, b) < 0 || (cross(a, b) == 0 && dot(a, b) < 0);
    }
    struct Line {
        static int cmp;
        mutable Point<int> a, b;
        friend bool operator<(Line x, Line y) {
            return cmp ? x.a < y.a : turnRight(x.b, y.b);
        }
        friend auto &operator<<(ostream &os, Line l) {
            return os << "<" << l.a << ", " << l.b << ">";
        }
    };

    int Line::cmp = 1;
    struct UpperConvexHull : set<Line> {
        bool contains(const Point<int> &p) const {
            auto it = lower_bound({p, 0});
            if (it != end() && it->a == p) return true;
            if (it != begin() && it != end() && cross(prev(it)->b, p - prev(it)->a) <= 0) {
                return true;
            }
            return false;
        }
        void add(const Point<int> &p) {
            if (contains(p)) return;
            auto it = lower_bound({p, 0});
            for (; it != end(); it = erase(it)) {
                if (turnRight(it->a - p, it->b)) {
                    break;
                }
            }
            for (; it != begin() && prev(it) != begin(); erase(prev(it))) {
                if (turnRight(prev(prev(it))->b, p - prev(prev(it))->a)) {
                    break;
                }
            }
            if (it != begin()) {
                prev(it)->b = p - prev(it)->a;
            }
            if (it == end()) {
                insert({p, {0, -1}});
            } else {
                insert({p, it->a - p});
            }
        }
    };
    struct ConvexHull {
        UpperConvexHull up, low;
        bool empty() const {
            return up.empty();
        }
        bool contains(const Point<int> &p) const {
            Line::cmp = 1;
            return up.contains(p) && low.contains(-p);
        }
        void add(const Point<int> &p) {
            Line::cmp = 1;
            up.add(p);
            low.add(-p);
        }
        bool isIntersect(int A, int B, int C) const {
            Line::cmp = 0;
            if (empty()) return false;
            Point<int> k = {-B, A};
            if (k.x < 0) k = -k;
            if (k.x == 0 && k.y < 0) k.y = -k.y;
            Point<int> P = up.upper_bound({{0, 0}, k})->a;
            Point<int> Q = -low.upper_bound({{0, 0}, k})->a;
            return sign(A * P.x + B * P.y - C) * sign(A * Q.x + B * Q.y - C) > 0;
        }
        friend ostream &operator<<(ostream &out, const ConvexHull &ch) {
            for (const auto &line : ch.up) out << "(" << line.a.x << "," << line.a.y << ")";
            cout << "/";
            for (const auto &line : ch.low) out << "(" << -line.a.x << "," << -line.a.y << ")";
            return out;
        }
    };
} // namespace Geometry