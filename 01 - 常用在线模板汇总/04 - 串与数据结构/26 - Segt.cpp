template <class T> struct Segt_ {
    struct node {
        int l, r;
        T w, Min;
        T lazy;
    };
    vector<T> w;
    vector<node> t;

    Segt_(int n) {
        w.resize(n + 1);
        t.resize((n << 2) + 1);
        build(1, n);
    }
    Segt_(vector<int> in) {
        int n = in.size() - 1;
        w.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            w[i] = in[i];
        }
        t.resize((n << 2) + 1);
        build(1, n);
    }
    void pushdown(node &p, T lazy) { // 在此更新下递函数
        p.w += (p.r - p.l + 1) * lazy;
        p.Min += lazy;
        p.lazy += lazy;
    }
    void pushup(node &p, node &l, node &r) { // 在此更新上传函数
        p.w = l.w + r.w;
        p.Min = min(l.Min, r.Min);
    }
#define GL (k << 1)
#define GR (k << 1 | 1)
    void pushdown(int k) { // 不需要动
        if (t[k].lazy == 0) return;
        pushdown(t[GL], t[k].lazy);
        pushdown(t[GR], t[k].lazy);
        t[k].lazy = 0;
    }
    void pushup(int k) { // 不需要动
        pushup(t[k], t[GL], t[GR]);
    }
    void build(int l, int r, int k = 1) {
        if (l == r) {
            t[k] = {l, r, w[l], w[l]};
            return;
        }
        t[k] = {l, r};
        int mid = (l + r) / 2;
        build(l, mid, GL);
        build(mid + 1, r, GR);
        pushup(k);
    }
    void modify(int l, int r, T val, int k = 1) { // 区间修改
        if (l <= t[k].l && t[k].r <= r) {
            pushdown(t[k], val);
            return;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        if (l <= mid) modify(l, r, val, GL);
        if (mid < r) modify(l, r, val, GR);
        pushup(k);
    }
    T Min(int l, int r, int k = 1) { // 区间询问最小值
        if (l <= t[k].l && t[k].r <= r) {
            return t[k].Min;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        T ans = 1E18;
        if (l <= mid) ans = min(ans, Min(l, r, GL));
        if (mid < r) ans = min(ans, Min(l, r, GR));
        return ans;
    }
    T ask(int l, int r, int k = 1) { // 区间询问，不合并
        if (l <= t[k].l && t[k].r <= r) {
            return t[k].w;
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        T ans = 0;
        if (l <= mid) ans += ask(l, r, GL);
        if (mid < r) ans += ask(l, r, GR);
        return ans;
    }
    node Ask(int l, int r, int k = 1) { // 区间合并
        if (l <= t[k].l && t[k].r <= r) {
            return t[k];
        }
        pushdown(k);
        int mid = (t[k].l + t[k].r) / 2;
        // 区间合并这里的if是反过来的
        if (r <= mid) return Ask(l, r, GL);
        if (mid < l) return Ask(l, r, GR);
        auto left = Ask(l, r, GL), right = Ask(l, r, GR);
        node res = {0, 0, 0, 0};
        pushup(res, left, right); // 合并left和right为新区间
        return res;
    }
    void debug(int k = 1) {
        cout << "[" << t[k].l << ", " << t[k].r << "]: ";
        cout << "w = " << t[k].w << ", ";
        cout << "Min = " << t[k].Min << ", ";
        cout << "lazy = " << t[k].lazy << ", ";
        cout << endl;
        if (t[k].l == t[k].r) return;
        debug(GL), debug(GR);
    }
#undef GL
#undef GR
};
using Segt = Segt_<int>;