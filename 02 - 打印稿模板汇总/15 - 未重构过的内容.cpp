### *线段树应用：扫描线

- 面积并

计算 $N$ 个矩形的面积并

```c++
//  code for P5490
#define lson (x << 1)
#define rson (x << 1 | 1)
const int N = 1e6 + 10;

int n, cnt = 0;
LL x1, y1, x2, y2, X[N << 1];

struct ScanLine {
    LL l, r, h;
    int mark; //mark用于保存权值 (1 / -1)
    bool operator<(const ScanLine &rhs) const { return h < rhs.h; }
} line[N << 1];

struct SegTree {
    int l, r, sum; //sum: 被完全覆盖的次数；
    LL len; //len: 区间内被截的长度。
} tree[N << 2];

void build_tree(int x, int l, int r) {
    tree[x].l = l, tree[x].r = r;
    tree[x].len = 0;
    tree[x].sum = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build_tree(lson, l, mid);
    build_tree(rson, mid + 1, r);
    return;
}

void pushup(int x) {
    int l = tree[x].l, r = tree[x].r;
    if (tree[x].sum /* 也就是说被覆盖过 */) tree[x].len = X[r + 1] - X[l]; //更新长度
    else tree[x].len = tree[lson].len + tree[rson].len; //合并儿子信息
}

void edit_tree(int x, LL L, LL R, int c) {
    int l = tree[x].l, r = tree[x].r;
    //  注意，l、r和L、R的意义完全不同
    //  l、r表示这个节点管辖的下标范围
    //  而L、R则表示需要修改的真实区间
    if (X[r + 1] <= L || R <= X[l]) return;
    //  这里加等号的原因：
    //  假设现在考虑 [2,5], [5,8] 两条线段，要修改 [1,5] 区间的sum
    //  很明显，虽然5在这个区间内，[5,8] 却并不是我们希望修改的线段
    //  所以总结一下，就加上了等号
    if (L <= X[l] && X[r + 1] <= R) {
        tree[x].sum += c;
        pushup(x);
        return;
    }
    edit_tree(lson, L, R, c);
    edit_tree(rson, L, R, c);
    pushup(x);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << x1 << y1 << x2 << y2;
        X[2 * i - 1] = x1, X[2 * i] = x2;
        line[2 * i - 1] = (ScanLine){x1, x2, y1, 1};
        line[2 * i] = (ScanLine){x1, x2, y2, -1};
        //      一条线段含两个端点，一个矩形的上下边都需要扫描线扫过
    }
    n <<= 1; //直接把 n <<= 1 方便操作
    sort(line + 1, line + n + 1);
    sort(X + 1, X + n + 1);
    int tot = unique(X + 1, X + n + 1) - X - 1; //去重
    build_tree(1, 1, tot - 1);
    //  为什么是 tot - 1 ：
    //  因为右端点的对应关系已经被篡改了嘛…
    //  [1, tot - 1]描述的就是[X[1], X[tot]]
    LL ans = 0;
    for (int i = 1; i < n /* 最后一条边是不用管的 */; i++) {
        edit_tree(1, line[i].l, line[i].r, line[i].mark); //先把扫描线信息导入线段树
        ans += tree[1].len * (line[i + 1].h - line[i].h); //然后统计面积
    }
    cout << ans << endl;
    return 0;
}
```

- 周长并

```c++
#define lson (x << 1)
#define rson (x << 1 | 1)
const int N = 2e4;
int n, X[N << 1];
int x1, y1, x2, y2, pre = 0; /* 先初始化为 0 */

struct ScanLine {
    int l, r, h, mark;
    if (h == rhs.h)
        return mark > rhs.mark;
    return h < rhs.h;
    //如果出现了两条高度相同的扫描线，也就是两矩形相邻
    //那么需要先扫底边再扫顶边，否则就会多算这条边
    //这个对面积并无影响但对周长并有影响
    // hack 数据：2 0 0 4 4 0 4 4 8 输出应为：24
} line[N];

struct SegTree {
    int l, r, sum, len, c;
    // c表示区间线段条数
    bool lc, rc;
    // lc, rc分别表示左、右端点是否被覆盖
    //统计线段条数(tree[x].c)会用到
} tree[N << 2];

void build_tree(int x, int l, int r) {
    tree[x].l = l, tree[x].r = r;
    tree[x].lc = tree[x].rc = false;
    tree[x].sum = tree[x].len = 0;
    tree[x].c = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build_tree(lson, l, mid);
    build_tree(rson, mid + 1, r);
}

void pushup(int x) {
    int l = tree[x].l, r = tree[x].r;
    if (tree[x].sum) {
        tree[x].len = X[r + 1] - X[l];
        tree[x].lc = tree[x].rc = true;
        tree[x].c = 1;
        //做好相应的标记
    } else {
        tree[x].len = tree[lson].len + tree[rson].len;
        tree[x].lc = tree[lson].lc, tree[x].rc = tree[rson].rc;
        tree[x].c = tree[lson].c + tree[rson].c;
        //如果左儿子左端点被覆盖，那么自己的左端点也肯定被覆盖；右儿子同理
        if (tree[lson].rc && tree[rson].lc)
            tree[x].c -= 1;
        //如果做儿子右端点和右儿子左端点都被覆盖，
        //那么中间就是连续的一段，所以要 -= 1
    }
}

void edit_tree(int x, int L, int R, int c) {
    int l = tree[x].l, r = tree[x].r;
    if (X[l] >= R || X[r + 1] <= L)
        return;
    if (L <= X[l] && X[r + 1] <= R) {
        tree[x].sum += c;
        pushup(x);
        return;
    }
    edit_tree(lson, L, R, c);
    edit_tree(rson, L, R, c);
    pushup(x);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << x1 << y1 << x2 << y2;
        line[2 * i - 1] = (ScanLine){x1, x2, y1, 1};
        line[2 * i] = (ScanLine){x1, x2, y2, -1};
        X[i * 2 - 1] = x1, X[i * 2] = x2;
    }
    n <<= 1;
    sort(line + 1, line + n + 1);
    sort(X + 1, X + n + 1);
    int tot = unique(X + 1, X + n + 1) - X - 1;
    build_tree(1, 1, tot - 1);
    int res = 0;
    for (int i = 1; i < n; i++) {
        edit_tree(1, line[i].l, line[i].r, line[i].mark);
        res += abs(pre - tree[1].len);
        pre = tree[1].len;                                  //统计横边
        res += 2 * tree[1].c * (line[i + 1].h - line[i].h); //统计纵边
    }
    res += line[n].r - line[n].l;
    //  特判一下枚举不到的最后一条扫描线
    printf("%d", res);
    return 0;
}
```

***

### *二维线段树：矩形树

题意：给你一个 $n*n$ 的矩阵，有 $m$ 个询问，`q x1 y1 x2 y2` 查询这个子矩阵的最大值和最小值，`c x y v` 是将 $(x,y)$ 点的值改成 $c$ 。二维线段树就是在一棵线段树的每一个节点，都保存着另一棵线段树的根节点编号。

```c++
const int N = 1500;
const int inf = 1e8;

int n, q, mx[N][N], mi[N][N];
int fg, xo, mians, mxans;

void upd2(int l, int r, int o, int y, int v) {
    if (l == r) { //如果找到了二维下标
        if (fg)
            mi[xo][o] = v, mx[xo][o] = v; ///如果此时正好找到了一维下标，就赋值
        else {                            ///否则更新一维的情况
            mi[xo][o] = min(mi[2 * xo][o], mi[2 * xo + 1][o]);
            mx[xo][o] = max(mx[2 * xo][o], mx[2 * xo + 1][o]);
        }
        return;
    }
    int m = (l + r) / 2;
    if (y <= m) upd2(l, m, 2 * o, y, v);
    else upd2(m + 1, r, 2 * o + 1, y, v);
    mi[xo][o] = min(mi[xo][2 * o], mi[xo][2 * o + 1]); ///递归回来更新二维情况
    mx[xo][o] = max(mx[xo][2 * o], mx[xo][2 * o + 1]);
}

///更新一维，x为要更新的一维下标，y为要更新的二维下标
void upd1(int l, int r, int o, int x, int y, int v) {
    if (l == r) {
        fg = 1; ///打上标记
        xo = o;
        upd2(1, n, 1, y, v);
        return;
    }
    int m = (l + r) / 2;
    if (x <= m) upd1(l, m, 2 * o, x, y, v);
    else upd1(m + 1, r, 2 * o + 1, x, y, v);
    fg = 0, xo = o;
    upd2(1, n, 1, y, v);
}

void qy2(int l, int r, int o, int pre, int ly, int ry) {
    if (ly <= l && ry >= r) {
        mians = min(mians, mi[pre][o]);
        mxans = max(mxans, mx[pre][o]);
        return;
    }
    int m = (l + r) / 2;
    if (ly <= m) qy2(l, m, 2 * o, pre, ly, ry);
    if (ry > m) qy2(m + 1, r, 2 * o + 1, pre, ly, ry);
}

void qy1(int l, int r, int o, int lx, int rx, int ly, int ry) {
    if (lx <= l && rx >= r) {
        qy2(1, n, 1, o, ly, ry);
        return;
    }
    int m = (l + r) / 2;
    if (lx <= m) qy1(l, m, 2 * o, lx, rx, ly, ry);
    if (rx > m) qy1(m + 1, r, 2 * o + 1, lx, rx, ly, ry);
}

int main() {
    scanf("%d", &n);
    int v;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &v), upd1(1, n, 1, i, j, v);
    scanf("%d", &q);
    while (q--) {
        char op[2];
        scanf("%s", op);
        int x, y, x1, y1;
        if (op[0] == 'q') {
            scanf("%d%d%d%d", &x, &y, &x1, &y1);
            mians = inf;
            mxans = 0;
            qy1(1, n, 1, x, x1, y, y1);
            printf("%d %d\n", mxans, mians);
        } else {
            scanf("%d%d%d", &x, &y, &v);
            upd1(1, n, 1, x, y, v);
        }
    }
    return 0;
}
```

***

### *最小瓶颈路

> 定义：在一张无向图中，给定起点 $s$ 与终点 $e$ ，需要找出一条简单路径，使路径上所有边中的**最大值最小**。

#### 单次查询：$\tt Kruskal$ 

利用 $\tt Kruskal$ 的过程。将所有边升序排序，逐一枚举每条边尝试将边两端的点所在集合进行合并，如果合并之后 $s$ 和 $e$ 在同一个集合中，则说明此时 $s$ 到 $e$ 连通。由于边的枚举是由小到大，因此**可以保证最后一次合并的边的权值就是答案**。

#### 多次查询：$\tt LCA + ST$ 表

$s$ 到 $e$ 的路径一定是 $s$ 到 $e$ 的最小瓶颈路之一（因为最小瓶颈路很可能有多条）。因此，对这张无向图预先进行MST，然后就变成了对于每个询问 $(s,e)$ ，输出 $s$ 到 $e$ 的路径上的权值最大值。这个可以用倍增 $\tt LCA$ 解决。

具体思路是在 $\tt ST$ 表预处理时，维护一个从该节点到其 $k$ 级父亲中经过的所有边的最大权值。在查询中仍然将 $s$ 和 $e$ 往上跳，同时维护路径中最大值，到其 $\tt LCA$ 结束。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10, maxj = 17, inf = 0x7fffffff;
struct edge {
    int u, v, w;
} e[M];
int heade[N], ev[M], ew[M], nexte[M];
int father[N], dep[N];
int fa[N][maxj], maxv[N][maxj];
int n, m, q, root, tot = 0, num = 0;
void add_edge(int u, int v, int w) {
    tot++;
    ev[tot] = v;
    ew[tot] = w;
    nexte[tot] = heade[u];
    heade[u] = tot;
}
int cmp(edge a, edge b) { return a.w < b.w; }
int find(int x) { return father[x] < 0 ? x : father[x] = find(father[x]); }
void union_set(int u, int v, int w) {
    int x = find(u), y = find(v);
    if (x == y) return;
    if (-father[x] > -father[y]) {
        father[x] += father[y];
        father[y] = x;
    } else {
        father[y] += father[x];
        father[x] = y;
    }
    add_edge(u, v, w);
    add_edge(v, u, w);
    num++;
}
void dfs(int ui) {
    int i, vi, wi;
    for (i = heade[ui]; ~i; i = nexte[i]) {
        vi = ev[i];
        wi = ew[i];
        if (vi == fa[ui][0]) continue;
        fa[vi][0] = ui;
        maxv[vi][0] = wi;
        dep[vi] = dep[ui] + 1;
        dfs(vi);
    }
}
void init() {
    int i, j;
    for (j = 1; (1 << j) <= n; j++) {
        for (i = 1; i <= n; i++) {
            if (fa[i][j - 1]) {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
                maxv[i][j] = max(maxv[i][j - 1], maxv[fa[i][j - 1]][j - 1]);
            }
        }
    }
}
int query(int u, int v) {
    int i, j, t, tmp = -inf;
    if (dep[u] < dep[v]) swap(u, v);
    t = (int)(log(dep[u]) / log(2));
    for (j = t; j >= 0; j--) {
        if (dep[u] - (1 << j) >= dep[v]) {
            tmp = max(tmp, maxv[u][j]);
            u = fa[u][j];
        }
    }
    if (u == v) return tmp;
    for (j = t; j >= 0; j--) {
        if (fa[u][j] && fa[u][j] != fa[v][j]) {
            tmp = max(tmp, max(maxv[u][j], maxv[v][j]));
            u = fa[u][j];
            v = fa[v][j];
        }
    }
    return max(tmp, max(maxv[u][0], maxv[v][0]));
}
int main() {
    int i, j, u, v, w;
    cin >> n >> m >> q;
    root = (1 + n) >> 1;
    memset(heade, -1, sizeof(heade));
    memset(father, -1, sizeof(father));
    for (i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        e[i] = {u, v, w};
    }
    sort(e + 1, e + m + 1, cmp);
    for (i = 1; i <= m; i++) {
        u = e[i].u, v = e[i].v, w = e[i].w;
        union_set(u, v, w);
        if (num >= n - 1) break;
    }
    dfs(root);
    init();
    for (i = 1; i <= q; i++) {
        scanf("%d%d", &u, &v);
        printf("%d\n",query(u,v));
    }
    return 0;
}
```

***

### *第 $K$ 短路

求解起点 $s$ 到终点 $e$ 间的第 $k$ 短路，先用 $\tt Djikstra$ 跑以 $e$ 为起点的最短路，随后用 $\tt BFS+A*$ 从 $s$ 跑。

```c++
typedef pair<LL, int> P;
const int N = 1000 + 7;
struct Edge { //正向边
    int to, next;
    LL val;
} edge[N * 100];
struct Line { //反向边
    int to, next;
    LL val;
} line[N * 100];
int n, m, s, e, tot, k, head[N], revhead[N];
int tot2;
bool vis[N];
LL dist[N];//保存终点到其他点的最短路
inline void addEdge(int a, int b, LL c) { //正向建边
    edge[tot].to = b;
    edge[tot].next = head[a];
    edge[tot].val = c;
    head[a] = tot++;
}
inline void AddEdge(int a, int b, LL c) { //反向建边
    line[tot2].to = b;
    line[tot2].next = revhead[a];
    line[tot2].val = c;
    revhead[a] = tot2++;
}
struct Node { // BFS保存状态
    int to; LL cost;
    bool operator<(const Node &another) const { //排序规则按照估价函数大小由小到大
        return cost + dist[to] > another.cost + dist[another.to];
        //估价= 当前 + 到终点最短
    }
    Node(int a, LL c) : to(a), cost(c) {}
};
inline void Dijkstra(int a) { //最短路
    dist[a] = 0;
    priority_queue<P, vector<P>, greater<P>> que;
    que.push(P(0, a));
    while (!que.empty()) {
        P p = que.top();
        que.pop();
        if (vis[p.second]) continue;
        vis[p.second] = 1;
        LL num = p.first;
        for (int i = revhead[p.second]; ~i; i = line[i].next) { //跑反向边
            if (!vis[line[i].to] && dist[line[i].to] > num + line[i].val) {
                dist[line[i].to] = num + line[i].val;
                que.push({dist[line[i].to], line[i].to});
            }
        }
    }
}
inline LL BFS(int a) { // BFS
    priority_queue<Node> que;
    que.push(Node(a, 0));
    while (!que.empty()) {
        Node node = que.top();
        que.pop();
        if (node.to == e) { //到达终点次数
            k--;
            if (k == 0) return node.cost;
        }
        for (int i = head[node.to]; ~i; i = edge[i].next) { //扩散（跑反向边）
            que.push(Node(edge[i].to, node.cost + edge[i].val));
        }
    }
    return -1;
}
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        tot = tot2 = 0;
        memset(dist, INF, sizeof(dist));
        memset(vis, 0, sizeof(vis));
        memset(head, -1, sizeof(head));
        memset(revhead, -1, sizeof(revhead));
        for (int i = 0; i < m; i++) {
            int a, b; LL v; cin >> a >> b >> v;
            addEdge(a, b, v);
            AddEdge(b, a, v);
        }
        scanf("%d%d%d", &s, &e, &k); //起点 + 终点 + k短路
        Dijkstra(e);
        if (dist[s] == INF) {
            printf("-1\n");
            continue;
        }
        if (s == e) k++; //起点终点重合，排除0距离
        LL ans = BFS(s);
        printf("%lld\n", ans);
    }
    return 0;
}
```

***

### * $\tt LCA$ 离线 $\tt Tarjan$

有一棵 $N$ 个节点的树，输出任意两个节点间的最小距离：$deep[a]+deep[b]−2∗deep[lca]$ 。

```c++
const int N = 5e4 + 7, M = 200007, INF = 0x3f3f3f3f;

int head[N], ver[N << 1], tot, edge[N << 1], nex[N << 1];
int n, m, T, t;
int fa[N], dis[N], vis[N], ans[N];
vector<int> query[N], query_id[N];

void add(int u, int v, int w) {
    ver[tot] = v;
    edge[tot] = w;
    nex[tot] = head[u];
    head[u] = tot++;
}

void add_query(int x, int y, int id) {
    query[x].push_back(y);
    query_id[x].push_back(id);
    query[y].push_back(x), query_id[y].push_back(id);
}

int Get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = Get(fa[x]);
}

void tarjan(int u) {
    vis[u] = 1;
    for (int i = head[u]; ~i; i = nex[i]) {
        int v = ver[i];
        if (vis[v]) continue;
        dis[v] = dis[u] + edge[i];
        tarjan(v);
        fa[v] = u;
    }
    for (int i = 0; i < query[u].size(); ++i) {
        int v = query[u][i], id = query_id[u][i];
        if (vis[v] == 2) {
            int lca = Get(v);
            ans[id] = min(ans[id], dis[v] + dis[u] - 2 * dis[lca]);
        }
    }
    vis[u] = 2;
}

int main() {
    cin >> T;
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            head[i] = -1, fa[i] = i, vis[i] = 0;
            query[i].clear(), query_id[i].clear();
        }
        tot = 0;
        memset(dis, 0, sizeof dis);
        for (int i = 1; i < n; ++i) {
            int x, y, z; cin >> x >> y >> z;
            add(x, y, z);
            add(y, x, z);
        }
        for (int i = 1; i <= m; ++i) {
            int x, y; cin >> x >> y;
            if (x == y) ans[i] = 0;
            else {
                add_query(x, y, i);
                ans[i] = INF;
            }
        }
        tarjan(1);
        for (int i = 1; i <= m; ++i) cout << ans << endl;
    }
    return 0;
}

```

***

### 最小生成树（MST问题）

#### *特殊建图：$\tt Borůvka$

$N\ (N\le 10^5)$ 个点，两两建边，边权为 $∣ i − j ∣ × D + A_ i + A_j$（D、A均给定）。基于并查集，以 $\mathcal O \big((N+M \big)*logN)$ 的复杂度完成。

```c++
/*Atcoder keyence2019 E*/
#define MN 201000

typedef long long ll;
int fa[MN];
int c1[MN], c2[MN];
int Min[MN];
ll D;
int a[MN];
int X[MN], Y[MN];
int x[MN], y[MN];
ll ans = 0;
int bl;
int n;

int Abs(int a) { return a > 0 ? a : -a; }
ll F(int i) { return i ? i * D + a[i] : 1e18; }
ll G(int i) { return i ? -i * D + a[i] : 1e18; }
ll H(int i, int j) {
    if (i == 0 || j == 0) return 1e18;
    return Abs(i - j) * D + a[i] + a[j];
}

void add(int *c, int x, int v, int type) {
    for (int i = x; i <= n; i += i & -i) {
        if (!type)
            if (F(v) < F(c[i])) c[i] = v;
        if (type)
            if (G(v) < G(c[i])) c[i] = v;
    }
}

int query(int *c, int x, int type) {
    int ans = 0;
    for (int i = x; i; i -= i & -i) {
        if (!type)
            if (F(c[i]) < F(ans)) ans = c[i];
        if (type)
            if (G(c[i]) < G(ans)) ans = c[i];
    }
    return ans;
}

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

void solve() {
    memset(x, 0, sizeof x);
    memset(y, 0, sizeof y);
    memset(c1, 0, sizeof c1);
    memset(c2, 0, sizeof c2);
    memset(Min, 0, sizeof Min);
    for (int i = 1; i <= n; i++) {
        int u = Find(i);
        int x = query(c1, u - 1, 1);
        int y = query(c2, n - u, 1);
        if (G(x) > G(y)) x = y;
        if (H(x, i) <= H(Min[i], i)) Min[i] = x;
        add(c1, u, i, 1);
        add(c2, n - u + 1, i, 1);
    }
    memset(c1, 0, sizeof c1);
    memset(c2, 0, sizeof c2);
    for (int i = n; i >= 1; i--) {
        int u = Find(i);
        int x = query(c1, u - 1, 0);
        int y = query(c2, n - u, 0);
        if (F(x) > F(y)) x = y;
        if (H(x, i) <= H(Min[i], i)) Min[i] = x;
        add(c1, u, i, 0);
        add(c2, n - u + 1, i, 0);
    }
    for (int i = 1; i <= n; i++) {
        int u = Find(i);
        if (H(i, Min[i]) < H(x[u], y[u])) x[u] = i, y[u] = Min[i];
    }
    int tot = 0;
    for (int i = 1; i <= n; i++) {
        int u = Find(i);
        ++tot;
        X[tot] = x[u];
        Y[tot] = y[u];
    }
    for (int i = 1; i <= tot; i++) {
        int x = Find(X[i]), y = Find(Y[i]);
        if (x == y) continue;
        ans += H(X[i], Y[i]);
        fa[x] = y;
        bl--;
    }
}

int main() {
    scanf("%d%lld", &n, &D);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), fa[i] = i;
    bl = n;
    while (bl > 1) solve();
    printf("%lld\n", ans);
}

```

#### *最小瓶颈生成树

> 定义：是图 $G$ 的一棵生成树，满足最大的边权值在 $G$ 的所有生成树中最小。

最小生成树是最小瓶颈生成树的充分不必要条件。 即**最小生成树一定是最小瓶颈生成树**，而最小瓶颈生成树不一定是最小生成树。

#### *最小生成树计数

统计一张图中最小生成树的数量（两棵树只要有一条边不同即视为不同）。

```c++
struct edge { LL u, v, w; };
edge e[102424];
LL fa[102424], use[102424];
LL is[102424];
LL find(LL x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
LL e_cmp(edge a, edge b) { return a.w < b.w; }
const LL p = 31011;
LL a[128][128];
LL inv[31015];
void kiLL(LL a, LL b, LL &aii, LL &aij, LL &aji, LL &ajj, LL &sign) {
    sign = 1;
    aii = ajj = 1;
    aij = aji = 0;
    while (b) {
        aii -= a / b * aji;
        aij -= a / b * ajj;
        aij = (aij % p + p) % p;
        aii = (aii % p + p) % p;
        a %= b;
        swap(a, b);
        swap(aii, aji);
        swap(aij, ajj);
        sign = -sign;
    }
}
LL det(LL n) {
    LL s = 1, _a, b, c, d, pa, ans = 1, nxa, nxb;
    FOR(i, 1, n) FOR(j, 1, n) 
        if (a[i][j] < 0) a[i][j] += p;
    FOR (i, 1, n) {
        FOR (j, i + 1, n) {
            kiLL(a[i][i], a[j][i], _a, b, c, d, pa);
            s *= pa;
            FOR (k, 1, n) {
                nxa = (a[i][k] * _a + a[j][k] * b) % p;
                nxb = (a[i][k] * c + a[j][k] * d) % p;
                a[i][k] = nxa;
                a[j][k] = nxb;
            }
        }
        ans = ans * a[i][i] % p;
    }

    return ans * (s + p) % p;
}
signed main() {
    LL n, m;
    inv[1] = 1;
    FOR (i, 2, p - 1) inv[i] = (p - p / i) * inv[p % i] % p;
    cin >> n >> m;
    FOR (i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        e[i] = {u, v, w};
    }
    sort(e + 1, e + m + 1, e_cmp);
    FOR (i, 1, n) fa[i] = i;
    LL g = n;
    for (int i = 1; i <= m && g > 1; ++ i)
        if (find(e[i].u) != find(e[i].v)) {
            use[i] = 1;
            fa[find(e[i].u)] = find(e[i].v);
            --g;
        }
    if (g > 1) {
        printf("0\n");
        return 0;
    }
    LL u = 1, v = 1, ans = 1;
    while (v <= m) {
        FOR (i, 1, n) {
            fa[i] = i;
            is[i] = 0;
        }
        FOR (i, 1, m)
            if (use[i] && e[i].w != e[u].w) {
                fa[find(e[i].u)] = find(e[i].v);
            }
        g = 0;
        FOR (i, 1, n) {
            if (!is[find(i)]) is[find(i)] = ++g;
            is[i] = is[find(i)];
        }
        FOR (i, 1, g) FOR (j, 1, g) a[i][j] = 0;
        while (e[u].w == e[v].w) {
            a[is[e[v].u]][is[e[v].v]] -= 1;
            a[is[e[v].v]][is[e[v].u]] -= 1;
            a[is[e[v].u]][is[e[v].u]] += 1;
            a[is[e[v].v]][is[e[v].v]] += 1;
            ++ v;
        }

        -- g;
        ans = ans * det(g) % p;
        u = v;
    }
    printf("%lld\n", ans);
    return 0;
}
```

***

### *次小生成树

使用 $\tt LCA$ 优化，以 $\mathcal O(N*logM)$ 求解无向图的严格次小生成树。

```c++
const int N = 500007, M = 1e6 + 7, INF = 0x3f3f3f3f;

int n, m;
int ver[M], nex[M], edge[M], head[N], tot;
int fa[N];
int deep[N];
int f[N][20]; // lca
int d1[N][20];
//注意d1[i][k]是当前i这个点从自己到2^k祖先整个路径上所有边权的的最大值，这样就不会因为lca是跳着走而有漏掉的情况
int d2[N][20];
int q[M]; //手写循环队列

struct node {
    int x, y, z;
    bool used;
    bool operator<(const node &t) const { return z < t.z; }
} e[M];

int Find(int x) {
    if (fa[x] == x)
        return x;
    return fa[x] = Find(fa[x]);
}

void add(int x, int y, int z) {
    ver[tot] = y;
    edge[tot] = z;
    nex[tot] = head[x];
    head[x] = tot++;
}

void bfs(int rt) { // bfs把所有的边都覆盖掉的
    deep[rt] = 1;
    int hh = 0, tt = 0;
    q[tt++] = rt;

    while (hh != tt) {
        int x = q[hh++];
        if (hh == M)
            hh = 0;

        for (int i = head[x]; ~i; i = nex[i]) {
            int y = ver[i], z = edge[i];
            if (!deep[y]) {
                deep[y] = deep[x] + 1;

                q[tt++] = y;
                if (tt == M) tt = 0;

                f[y][0] = x;     // lca的正常处理
                d1[y][0] = z;    //最大值，初始化为边权
                d2[y][0] = -INF; //次大值，最开始为-INF
                for (int k = 1; k <= 16; ++k) {
                    int anc = f[y][k - 1];
                    f[y][k] = f[anc][k - 1];
                    //左半边和右半边
                    int distance[4] = {d1[y][k - 1], d2[y][k - 1],
                                       d1[anc][k - 1], d2[anc][k - 1]};
                    //这两个要初始化为-INF，一会取最大值
                    d1[y][k] = d2[y][k] = -INF;
                    for (int o = 0; o < 4; ++o) {
                        int d = distance[o];
                        //老规矩，大于最大，最大给次大，更新最大
                        if (d > d1[y][k]) d2[y][k] = d1[y][k], d1[y][k] = d;
                        else if (d != d1[y][k] && d > d2[y][k]) d2[y][k] = d;
                        //否则看次大，反正d是不可能小于他们
                    }
                }
            }
        }
    }
}

int lca(int x, int y, int z) { //返回差值
    static int distance[N * 2]; //路上经过的全部放到这个数组里取最大值
    int cnt = 0;
    if (deep[x] < deep[y])swap(x, y);
    for (int k = 16; k >= 0; k--) {
        if (deep[f[x][k]] >= deep[y]) {
            distance[cnt++] = d1[x][k];
            distance[cnt++] = d2[x][k];
            x = f[x][k];
        }
    }
    if (x != y) {
        for (int k = 16; k >= 0; --k) {
            if (f[x][k] != f[y][k]) {
                distance[cnt++] = d1[x][k];
                distance[cnt++] = d2[x][k];
                distance[cnt++] = d1[y][k];
                distance[cnt++] = d2[y][k];
                x = f[x][k], y = f[y][k];
            }
        }
        distance[cnt++] = d1[x][0];
        distance[cnt++] = d1[y][0];
        //此时x和y距离它们的lca只有一步，也就是只有的d1 = w,而d2 = -INF,不用加
    }

    int dist1 = -INF, dist2 = -INF;
    //按照老规矩更新
    for (int i = 0; i < cnt; ++i) {
        int d = distance[i];
        if (d > dist1) dist2 = dist1, dist1 = d;
        else if (d != dist1 && d > dist2) dist2 = d;
    }
    //能换最大值肯定是换最大值更优
    if (z > dist1) return z - dist1;
    if (z > dist2) return z - dist2;
    return INF; //换不了就返回INF，因为我们最后要的是最小值（严格次小生成树）
}

ll kruskal() {
    ll res = 0;
    for (int i = 1; i <= n; ++i) fa[i] = i; //并查集初始化
    sort(e + 1, e + 1 + m);
    memset(head, -1, sizeof head);
    for (int i = 1; i <= m; ++i) {
        int x = e[i].x, y = e[i].y, z = e[i].z;
        int fx = Find(x);
        int fy = Find(y);
        if (fx != fy) {
            fa[fx] = fy;
            e[i].used = true;
            res += z;
            add(x, y, z);
            add(y, x, z);
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int x, y, z; cin >> x >> y >> z;
        e[i] = {x, y, z};
    }

    ll sum = kruskal();
    bfs(1); // lca预处理
    ll res = 1e18; //会爆int

    for (int i = 1; i <= m; ++i) {
        if (!e[i].used) { //对于所有非树边
            int x = e[i].x, y = e[i].y, z = e[i].z;
            res = min(res, sum + lca(x, y, z));
        }
    }
    printf("%lld\n", res);
    return 0;
}
```

***

### 多源汇最短路

####  *$\tt Johnson$ 解

可用于负权图，以 $\mathcal{O}(N*M*logN)$ 的复杂度计算。

***

### 子序列自动机

$\mathcal{Provided \ by \ \pmb{Wida}}$ 。 $q$ 次询问，每次询问序列 $B_q$ 是否是 $T$ 的子序列（子序列定义为从 $T$ 中删去若干个数字后与 $B_q$ 相等。 以 $\mathcal O(N+\sum L_i)$ 的复杂度完成遍历。 

```c++
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
const int SIZ =1e5;
char bef[SIZ+3],*p1=bef,*p2=bef;
char readc(){
    if(p1==p2) p1=bef,p2=bef+fread(bef,1,SIZ,stdin);
    return *p1++;
}
const int MAXN =1e5+3,MAXM=1e6+3;
int aft[MAXM],val[MAXM],len[MAXN];
int n,q,num,P[MAXN]; bool fnd[MAXN];
int head[MAXN],ver[MAXM],nxt[MAXM],tot;
int add(int u,int v){
    return ver[++tot]=v,nxt[tot]=head[u],head[u]=tot;
}
#define wrtyes (putchar('Y'),putchar('e'),putchar('s'),putchar('\n'))
#define wrtno  (putchar('N'),putchar('o'),putchar('\n'))
int main(){
    qread(),n=qread(),q=qread(),qread();
    up(1,n,i) P[i]=qread();
    up(1,q,i){
        len[i]=qread(),val[++num]=qread(),add(val[num],num);
        up(2,len[i],j) aft[num]=num+1,val[++num]=qread();
        aft[num]=-i;
    }
    up(1,n,i){
        int j=head[P[i]]; head[P[i]]=0;
        for(;j;j=nxt[j]){
            int u=ver[j],v=aft[u];
            v<0?(fnd[-v]=true):(add(val[v],v));
        }
    }
    up(1,q,i) fnd[i]?wrtyes:wrtno;
    return 0;
}
```

***
