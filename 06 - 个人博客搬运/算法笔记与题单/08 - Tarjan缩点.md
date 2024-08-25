# 往期浏览

[第一期 - 博弈论](https://www.cnblogs.com/WIDA/p/16570498.html)

[第二期 - 前缀和](https://www.cnblogs.com/WIDA/p/15504413.html)

[第三期 - 二分与三分算法](https://www.cnblogs.com/WIDA/p/17615803.html)

[第四期 - 莫队算法](https://www.cnblogs.com/WIDA/p/17610403.html)

[第五期 - 线段树（暂时未公开）]()

[第六期 - 位运算 (Bitmasks)](https://www.cnblogs.com/WIDA/p/17547678.html)

[第七期 - 树上分治](https://www.cnblogs.com/WIDA/p/17610362.html)

[第八期 - Tarjan缩点](https://www.cnblogs.com/WIDA/p/17635152.html)

[第九期 - 网络流](https://www.cnblogs.com/WIDA/p/17672842.html)

[第十期 - 字符串哈希](https://www.cnblogs.com/WIDA/p/17766310.html)

# 讲解

## （有向图）强连通分量缩点

### 概念

强连通分量缩点后的图称为 SCC。

有两种方式会导致形成 SCC，其一是存在一条后向边，直接指向某个祖先节点；其二是存在一条横叉边，横叉边指向某个祖先节点。

==求解强连通分量==：该算法主要依赖于 dfs，定义两个数组，`time` 数组代表遍历到该点的时间戳， `upper` 数组代表从该点开始走能走到的最小时间戳。对于某一点 $x$ ，如果满足 `time[x] == upper[x]` ，说明这个点位于一个强连通分量的最上层，这时可以借助栈 `S` 来获得 $x$ 所在 SCC 的全部点的编号：一直到 $x$ 出栈为止，这些点都属于同一个 SCC。

==强连通分量缩点操作过程==：对于任意的边 $(x_i,y_i)$ ，如果它们不属于同一个强连通分量，那么就建立一条新边。

最终我们以 $\mathcal O (N + M)$ 的复杂度完成上述全部操作。

### 个人封装

```c
struct SCC {
    int n;
    vector<vector<int>> ver;
    vector<int> dfn, low, col, S;
    int now, cnt;

    SCC(int n) : n(n) {
        ver.assign(n + 1, {});
        dfn.resize(n + 1, -1);
        low.resize(n + 1);
        col.assign(n + 1, -1);
        S.clear();
        now = cnt = 0;
    }
    void add(int x, int y) {
        ver[x].push_back(y);
    }
    void tarjan(int x) {
        dfn[x] = low[x] = now++;
        S.push_back(x);
        for (auto y : ver[x]) {
            if (dfn[y] == -1) {
                tarjan(y);
                low[x] = min(low[x], low[y]);
            } else if (col[y] == -1) {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int pre;
            cnt++;
            do {
                pre = S.back();
                col[pre] = cnt;
                S.pop_back();
            } while (pre != x);
        }
    }
    pair<int, vector<vector<int>>> rebuild() { // [新图的顶点数量, 新图]
        work();
        vector<vector<int>> adj(cnt + 1);
        for (int i = 1; i <= n; i++) {
            for (auto j : ver[i]) {
                int x = col[i], y = col[j];
                if (x != y) {
                    adj[x].push_back(y);
                }
            }
        }
        return {cnt, adj};
    }
    void work() {
        for (int i = 1; i <= n; i++) { // 避免图不连通
            if (dfn[i] == -1) {
                tarjan(i);
            }
        }
    }
};
```

## （无向图）割边缩点

### 概念

割边缩点后的图称为 E-DCC。

较有向图中 SCC 的形成更简单，只有一种方式会形成 E-DCC，即不存在一条边，直接指向某个祖先节点。

==求解割边==：我们同样维护 `time` 和 `upper` 两个时间戳数组。对于某一条边 $(x-y)$ ，如果满足 `time[x] < upper[y]` ，说明 $y$ 不能到达 $x$ 的任何一个祖先节点，这条边就是割边。然而，在处理重边问题时，借助 $\tt vector$ 的方法无法对之进行处理（例如同时存在 $(u,v)$ 和 $(v,u)$ 两条边时，链式前向星可以借助 `h` 数组直接区分这两个 `u` 的不同，进而判断这条边不是割边，但是在 $\tt vector$ 数组中这两个 `u` 是相同的），故求解割边**一般都采用链式前向星建图法**。

==求解边双==：如果满足 `time[z] == upper[z]` ，$z$ 就位于一个边双的最上层，同样可以借助栈 `S` 来获得 $z$ 所在边双的全部点的编号：一直到 $z$ 出栈为止，这些点都属于同一个 E-DCC 。

==边双缩点操作过程==：旧图中的每一条割边即为新图中的一条边，获取割边两端点颜色后直接连接即可。下方给出的链式前向星方法是在求解割边的基础上顺便将边双缩点，如果不需要求解割边而只需要将边双缩点，那么直接套用 SCC 缩点的做法即可。

### 个人封装

```c
struct E_DCC {
    int n;
    vector<int> h, ver, ne;
    vector<int> dfn, low, col, S;
    int now, cnt, tot;
    vector<bool> bridge; // 记录是否是割边

    E_DCC(int n, int m) : n(n) {
        m *= 2; // 注意链式前向星边的数量翻倍
        ver.resize(m + 1);
        ne.resize(m + 1);
        bridge.resize(m + 1);
        
        h.resize(n + 1, -1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        col.resize(n + 1);
        S.clear();
        tot = cnt = now = 0;
    }
    void add(int x, int y) { // 注意，这里的编号从 0 开始
        ver[tot] = y, ne[tot] = h[x], h[x] = tot++;
        ver[tot] = x, ne[tot] = h[y], h[y] = tot++;
    }
    void tarjan(int x, int fa) { // 这里是缩边双，不是缩点，不相同
        dfn[x] = low[x] = ++now;
        S.push_back(x);
        for (int i = h[x]; ~i; i = ne[i]) {
            int y = ver[i];
            if (!dfn[y]) {
                tarjan(y, i); // 这里储存的是父亲边的编号
                low[x] = min(low[x], low[y]);
                // y 不能到达 x 的任何一个祖先节点，(x - y) 即为一条割边
                // 但是在这里，我们不直接储存 (x - y) 这条边，而是储存边的编号
                // 这样做是为了处理重边的情况（点可能相同，但是边的编号绝对不相同）
                if (dfn[x] < low[y]) {
                    bridge[i] = bridge[i ^ 1] = true;
                }
            } else if (i != (fa ^ 1)) { // 这里同样的，使用边的编号来处理重边情况
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int pre = 0;
            cnt++;
            do {
                pre = S.back();
                S.pop_back();
                col[pre] = cnt;
            } while (pre != x);
        }
    }
    pair<int, vector<vector<int>>> rebuild() { // [新图的顶点数量, 新图]
        work();
        vector<vector<int>> adj(cnt + 1);
        for (int i = 0; i < tot; ++i) {
            if (bridge[i]) { // 如果 (i, i ^ 1) 是割边
                int x = col[ver[i]], y = col[ver[i ^ 1]];
                adj[x].push_back(y); // 割边两端点颜色必定不同，故直接连边
            }
        }
        return {cnt, adj};
    }
    void work() {
        for (int i = 1; i <= n; i++) { // 避免图不连通
            if (dfn[i] == 0) {
                tarjan(i, -1);
            }
        }
    }
};
```

## （无向图）割点缩点

### 概念

割点缩点后的图称为 V-DCC。

==求解割点==：我们同样维护 `time` 和 `upper` 两个时间戳数组。对于某一条边 $(x-y)$ ，如果满足 `time[x] <= upper[y]` ，说明 $y$ 不能到达 $x$ 的任何一个祖先节点，这时有两种情况，其一是当 $x$ 不为根节点时，那么显然 $x$ 是一个割点；其二时当 $x$ 为根节点时，那么只有当 $x$ 至少拥有两个子节点时，其才为割点。所以我们还需要维护两个变量，其一是 $x$ 是否为当前根节点，其二是 $x$ 的子节点数量。

==求解点双==：同样借助栈 `S` 来维护，这里与求解 SCC 和 E-DCC 都不相同——对于某一条边 $(x-y)$ ，只要我们确定了 $x$ 是割点，就直接开始弹栈操作，一直到 $y$ 出栈为止，这些点都属于同一个 V-DCC 。而由于下方性质，所以额外的将 $x$ 也看做属于这个 V-DCC 。除此之外，由于判断条件的变化，我们需要特判：若一个点是孤立点，那么它也是一个 V-DCC 。

==点双缩点操作过程==：旧图中的每一个割点都是新图中的一个点，旧图中的 V-DCC 都需要向其所包含的每一个割点各连一条边。

```c
struct V_DCC {
    int n;
    vector<vector<int>> ver, col;
    vector<int> dfn, low, S;
    int now, cnt;
    vector<bool> point; // 记录是否为割点

    V_DCC(int n) : n(n) {
        ver.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        col.resize(2 * n + 1);
        point.resize(n + 1);
        S.clear();
        cnt = now = 0;
    }
    void add(int x, int y) {
        if (x == y) return; // 手动去除重边
        ver[x].push_back(y);
        ver[y].push_back(x);
    }
    void tarjan(int x, int root) {
        low[x] = dfn[x] = now++;
        S.push_back(x);
        if (x == root && !ver[x].size()) { // 特判孤立点
            ++cnt;
            col[cnt].push_back(x);
            return;
        }

        int flag = 0;
        for (auto y : ver[x]) {
            if (!dfn[y]) {
                tarjan(y, root);
                low[x] = min(low[x], low[y]);
                if (dfn[x] <= low[y]) {
                    flag++;
                    if (x != root || flag > 1) {
                        point[x] = true; // 标记为割点
                    }
                    int pre = 0;
                    cnt++;
                    do {
                        pre = S.back();
                        col[cnt].push_back(pre);
                        S.pop_back();
                    } while (pre != y);
                    col[cnt].push_back(x);
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }
    pair<int, vector<vector<int>>> rebuild() { // [新图的顶点数量, 新图]
        work();
        vector<vector<int>> adj(cnt + 1);
        for (int i = 1; i <= cnt; i++) {
            if (!col[i].size()) { // 注意，孤立点也是 V-DCC
                continue;
            }
            for (auto j : col[i]) {
                if (point[j]) { // 如果 j 是割点
                    adj[i].push_back(point[j]);
                    adj[point[j]].push_back(i);
                }
            }
        }
        return {cnt, adj};
    }
    void work() {
        for (int i = 1; i <= n; ++i) { // 避免图不连通
            if (!dfn[i]) {
                tarjan(i, i);
            }
        }
    }
};
```

# 题单

## [CodeForces 427C - Checkposts (1700)](https://codeforces.com/contest/427/problem/C)：SCC

## [CodeForces 1811F - Is It Flower? (2100)](https://codeforces.com/contest/1811/problem/F)：V-DCC

有其他做法。

## [CodeForces 118E - Bertown roads (2000)](https://codeforces.com/contest/118/problem/E)：E-DCC

官标 $\tt 2000$，实际难度应该在 $\tt 1600$ 左右。一眼模板，最难的点可能在构造输出边部分，然而这个也是典，使用 $\tt dfs$ 随便处理下即可。

## [CodeForces 1000E - We Need More Bosses (2100)](https://codeforces.com/contest/1000/problem/E)：E-DCC

## [894E](https://codeforces.com/contest/894/problem/E)：SCC

## 700C（$\tt *2600$；图论-缩点、网络流-最小割）

[洛谷博客](https://www.luogu.com.cn/blog/WIDA/solution-cf700c)。

## 999E - Reachability from the Capital $^ {*2000\text{;图论}}$

挺喜欢这题的。我们可以缩点，这样形如“首都无法到达 $x,y$ 城市，但是可以从 $x$ 到 $y$ ”这样的城市会变成一个点，非常方便统计；然而，首都能到达的城市也会被缩点的过程处理，所以我们要先增边——使得这些城市成为一整个强连通分量，之后再跑tarjan。