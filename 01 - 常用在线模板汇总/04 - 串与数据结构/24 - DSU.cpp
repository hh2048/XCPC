struct DSU {
    vector<int> fa, p;

    DSU(int n) {
        fa.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
        p.resize(n + 1, 1);
    }
    int get(int x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool merge(int x, int y) { // 设x是y的祖先
        x = get(x), y = get(y);
        if (x == y) return false;
        if (x < y) swap(x, y); // 将编号小的合并到大的上
        fa[y] = x;
        p[x] += p[y];
        return true;
    }
    bool same(int x, int y) {
        return get(x) == get(y);
    }
    int size(int x) { // 输出连通块中点的数量
        return p[get(x)];
    }
};