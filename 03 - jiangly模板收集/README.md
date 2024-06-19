## 声明

自用！非本人原创，仅作整理归档。大部分代码来自于 [CodeForces Jiangly](https://codeforces.com/submissions/jiangly) 的提交，部分来自于GYM、牛客、Atcoder。[文章博客链接](https://www.cnblogs.com/WIDA/p/17633758.html)，[文章 GitHub 链接](https://github.com/hh2048/XCPC/tree/main/03%20-%20jiangly%E6%A8%A1%E6%9D%BF%E6%94%B6%E9%9B%86)。

灵感参考链接：[beiyouwuyanzu/cf_code_jiangly](https://github.com/beiyouwuyanzu/cf_code_jiangly)

***

# 01 - 杂类

## 01 - int128 输出流

[2023-03-20](https://codeforces.com/contest/1806/submission/198413531)

## 02 - 库函数重载

上取整下取整 [2023-10-15](https://codeforces.com/contest/293/submission/228297248)

最大值赋值 [2023-09-30](https://codeforces.com/contest/1874/submission/226069129)

精确开平方 [2024-03-02](https://qoj.ac/submission/343317)，[2023-09-19](https://qoj.ac/submission/183430)

## 03 - 字符调整

大小写转换、获取字母序 [2024-03-16](https://qoj.ac/submission/355156)

## 04 - 实数域二分

[2023-10-21](https://qoj.ac/submission/222042)

***

# 02 - 图与网络

## 01 - 强连通分量缩点（SCC）

[2023-06-18](https://codeforces.com/contest/1835/submission/210147209)

## 02 - 求解割边、割边缩点（EBCC）

[2023-05-11](https://codeforces.com/contest/118/submission/205426518)

## 03 - 二分图最大权匹配（MaxAssignment）【久远】
<!-- 
基于KM[2022-04-10](https://atcoder.jp/contests/abc247/submissions/30867023) -->

## 04 - 一般图最大匹配（Graph）【久远】

带花树算法[2021-12-24](https://codeforces.com/contest/1615/submission/140509278)

## 05 - TwoSat（2-Sat）

[2023-09-29](https://atcoder.jp/contests/arc161/submissions/46031530)

## 06 - 最大流（MaxFlow）

A（Flow 旧版其一，整数应用）[2022-09-03](https://codeforces.com/contest/1717/submission/170688062)

B（Flow 旧版其二，浮点数应用）[2022-04-09](https://cf.dianhsu.com/gym/104288/submission/201412765)

C（MaxFlow 新版）[2023-07-21](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62915815)

## 07 - 费用流（MCFGraph）

<!-- A（最小费用可行流）[2022-12-12](https://codeforces.com/contest/1766/submission/184974697)

B（最小费用最大流）代码同上，但是需要注释掉建边限制。以下为参考：

```c
void addEdge(int u, int v, int c, int f) { // 可行流
    if (f < 0) {
        g[u].push_back(e.size());
        e.emplace_back(v, 0, f);
        g[v].push_back(e.size());
        e.emplace_back(u, c, -f);
    } else {
        g[u].push_back(e.size());
        e.emplace_back(v, c, f);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -f);
    }
}
```

```c
void addEdge(int u, int v, int c, int f) { // 最大流
    g[u].push_back(e.size());
    e.emplace_back(v, c, f);
    g[v].push_back(e.size());
    e.emplace_back(u, 0, -f);
}
``` -->

## 08 - 树链剖分（HLD）

[2023-08-31](https://codeforces.com/contest/1863/submission/221214363)

***

# 03 - 数论、几何与多项式

## 01 - 快速幂
<!-- 
[2023-10-09](https://atcoder.jp/contests/tenka1-2017/submissions/46411797) -->

## 02 - 欧拉筛
<!-- 
[2023-08-29](https://cf.dianhsu.com/gym/104479/submission/220987267) -->

## 03 - 莫比乌斯函数筛（莫比乌斯函数/反演）

[2023-03-04](https://atcoder.jp/contests/tupc2022/submissions/39391116)

## 04 - 欧拉函数

A（求解单个数的欧拉函数）[2023-10-09](https://atcoder.jp/contests/tenka1-2017/submissions/46411797)

B（求解全部数的欧拉函数）[2023-09-24](https://qoj.ac/submission/187055)

## 05 - 扩展欧几里得（exGCD）
<!-- 
[2023-10-09](https://atcoder.jp/contests/tenka1-2017/submissions/46411797) -->

## 06 - 组合数

A（Comb+MInt & MLong）[2023-08-26](https://codeforces.com/contest/1864/submission/220584872)

B（逆元小范围预处理）[2024-03-14](https://qoj.ac/submission/353877)，[2023-10-06](https://qoj.ac/submission/203196)

## 07 - 二项式（Binomial 任意模数计算）
<!-- 
[2023-08-22](https://codeforces.com/contest/896/submission/219861532) -->

## 08 - 素数测试与因式分解（Miller-Rabin & Pollard-Rho）

[2023-05-16](https://cf.dianhsu.com/gym/104354/submission/206130894)

## 09 - 平面几何

[2023-07-17](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62808640)

## 10 - 静态凸包

A（with. Point，旧版）[2023-04-09](https://cf.dianhsu.com/gym/104288/submission/201412835)

B（with. Point，新版）[2024-04-06](https://qoj.ac/submission/379920)

C（with. std::complex）[2022-02-04](https://loj.ac/s/1370861)

## 11 - 多项式相关（Poly）

A（Z 旧版）[2023-02-06](https://atcoder.jp/contests/arc155/submissions/38664055)

B（Poly+MInt & MLong 新版）[2023-09-20](https://atcoder.jp/contests/arc163/submissions/45737810)

## 12 - 矩阵（Matrix）

[2024-03-14](https://qoj.ac/submission/353771)

## 13 - 多项式乘法

[2024-03-10](https://qoj.ac/submission/350298)

## 14 - 高精度（BigInt）

[2023-09-11](https://qoj.ac/submission/176420)

***

# 04 - 数据结构

## 01 - 树状数组（Fenwick）

<!-- A（Fenwick 旧版）[2023-08-11](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63382128)

B（Fenwick 新版）[2023-12-28](https://codeforces.com/contest/1915/submission/239262801) -->

## 02 - 并查集（DSU）

[2023-08-04](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63239142)

<!-- ## 03 - 线段树（SegmentTree）

A（SegmentTree 基础区间加乘）[2023-10-18](https://cf.dianhsu.com/gym/104417/submission/223800089)

B（SegmentTree+Info 查找前驱后继）[2023-08-11](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63382128)

C（SegmentTree+Info+Merge 区间合并）[2022-04-23](https://codeforces.com/contest/1672/submission/154766851)

D（不封装版）[2024-03-10](https://qoj.ac/submission/350095)

E（不封装版）[2023-09-24](https://qoj.ac/submission/187031) -->

## 04 - 懒标记线段树（LazySegmentTree）
<!-- 
A（LazySegmentTree 基础区间修改）[2023-03-12](https://codeforces.com/contest/1804/submission/197106837)

B（LazySegmentTree 查找前驱后继）[2023-07-17](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62804432)

C（LazySegmentTree 二分修改）[2023-03-03](https://atcoder.jp/contests/joi2023yo2/submissions/39363123) -->

## 05 - 取模类（MLong & MInt）

A（Z 旧版）[2022-06-12](https://codeforces.com/contest/1697/submission/160317720)

B（MLong & MInt 新版）[2023-08-14](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63433564)

根据输入内容动态修改 MOD 的方法：`Z::setMod(p);` 。

## 06 - 状压RMQ（RMQ）


## 07 - Splay

A[2023-02-15](https://atcoder.jp/contests/joi2023ho/submissions/38901674)

B[2023-09-30](https://cf.dianhsu.com/gym/104479/submission/221036520)

C[2024-03-30](https://codeforces.com/contest/1942/submission/254202464)

## 08 - 其他平衡树

A[2023-08-04](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63246177)

B[2023-08-26](https://codeforces.com/contest/1864/submission/220558951)

C[2023-04-03](https://codeforces.com/contest/38/submission/200537139)

D[2023-07-31](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63162242)

## 09 - 分数四则运算（Frac）

[2023-04-23](https://codeforces.com/contest/598/submission/203186397)

## 10 - 线性基（Basis）

[2023-12-03](https://codeforces.com/contest/1902/submission/235594491)

***

# 05 - 字符串

## 01 - 马拉车（Manacher）
<!-- 
A（Manacher 旧版）[2024-04-06](https://qoj.ac/submission/380047) -->

B（Manacher 新版）[2024-04-14](https://atcoder.jp/contests/abc349/submissions/52365777)

## 02 - Z函数

<!-- [2023-08-11](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63378373) -->

## 03 - 后缀数组

A（SuffixArray）[2023-03-14](https://atcoder.jp/contests/discovery2016-qual/submissions/39727257)

B（SA 及其应用）[2023-09-24](https://qoj.ac/submission/187270)

## 04 - 后缀自动机（SuffixAutomaton）

A（SuffixAutomaton 旧版）[2022-08-17](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=53409023&returnHomeType=1&uid=329687984)
<!-- 
B（SAM 新版）[2023-05-27](https://cf.dianhsu.com/gym/104353/submission/207318083) -->

## 05 - 回文自动机（PAM）

[2023-05-19](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62237107&returnHomeType=1&uid=329687984)

## 06 - AC自动机（AhoCorasick）

A（AC 旧版）[2021-07-07](https://codeforces.com/contest/710/problem/F)

B（AhoCorasick 新版）[2023-04-07](https://codeforces.com/contest/1801/submission/201155712)

C（AhoCorasick 新新版）[2024-04-09](https://www.luogu.com.cn/record/155114676)

## 07 - 随机生成模底 字符串哈希（例题）

[2022-06-09](https://codeforces.com/contest/1598/submission/160006998)

## 08 - 最长公共前缀 LCP

[2024-03-02](https://qoj.ac/submission/343378)

## 09 - 字典树 Trie

A [2023-09-26](https://qoj.ac/submission/188993)

B [2023-09-26](https://qoj.ac/submission/188957)