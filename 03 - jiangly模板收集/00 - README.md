## 声明

该文件夹代码非本人原创，我只做了整理归档。大部分代码来自于 [Codefroces Jiangly](https://codeforces.com/submissions/jiangly) 的提交，部分来自于GYM、牛客多校、Atcoder。

首发地址：[个人博客园](https://www.cnblogs.com/WIDA/p/17633758.html)

灵感参考链接：[beiyouwuyanzu/cf_code_jiangly](https://github.com/beiyouwuyanzu/cf_code_jiangly)

***

# 01 - 杂类

## 01 - int128 输出流

[2023-03-20](https://codeforces.com/contest/1806/submission/198413531)

## 02 - 库函数重载

上取整下取整 [2023-10-15](https://codeforces.com/contest/293/submission/228297248)

最大值赋值 [2023-09-30](https://codeforces.com/contest/1874/submission/226069129)

***

# 02 - 图论

## 01 - 强连通分量缩点 SCC 

[2023-06-18](https://codeforces.com/contest/1835/submission/210147209)

## 02 - 求解割边、割边缩点 EBCC 

[2023-05-11](https://codeforces.com/contest/118/submission/205426518)

## 03 - 二分图最大权匹配 (KM)【久远】MaxAssignment

[2022-04-10](https://atcoder.jp/contests/abc247/submissions/30867023)

## 04 - 一般图最大匹配（带花树算法）【久远】

[2021-12-24](https://codeforces.com/contest/1615/submission/140509278)

## 05 - 2-Sat TwoSat 

[2023-09-29](https://atcoder.jp/contests/arc161/submissions/46031530)

## 06 - 最大流（旧版）Flow 

整数：[2022-09-03](https://codeforces.com/contest/1717/submission/170688062)

浮点数：[2022-04-09](https://cf.dianhsu.com/gym/104288/submission/201412765)

## 06 - 最大流（新版）MaxFlow 

[2023-07-21](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62915815)

## 07 - 费用流（最小费用可行流） MCFGraph 

[2022-12-12](https://codeforces.com/contest/1766/submission/184974697)

## 07 - 费用流（最小费用最大流） MCFGraph

同上，但是需要注释掉建边限制。

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
```

## 08 - 树链剖分 HLD 

[2023-08-31](https://codeforces.com/contest/1863/submission/221214363)

***

# 03 - 数论

## 01 - 快速幂

[2023-10-09](https://atcoder.jp/contests/tenka1-2017/submissions/46411797)

## 02 - 欧拉筛

[2023-08-29](https://cf.dianhsu.com/gym/104479/submission/220987267)

## 03 - 素数+莫比乌斯函数筛（莫比乌斯函数/反演）

[2023-03-04](https://atcoder.jp/contests/tupc2022/submissions/39391116)

## 04 - 求解单个数的欧拉函数

[2023-10-09](https://atcoder.jp/contests/tenka1-2017/submissions/46411797)

## 05 - 扩展欧几里得

[2023-10-09](https://atcoder.jp/contests/tenka1-2017/submissions/46411797)

## 06 - 组合数（配合取模类） Comb 

[2023-08-26](https://codeforces.com/contest/1864/submission/220584872)

## 06 - 组合数/二项式（任意模数） Binomial

[2023-08-22](https://codeforces.com/contest/896/submission/219861532)

## 07 - Miller-Rabin 素数测试 与 Pollard-Rho 因式分解

[2023-05-16](https://cf.dianhsu.com/gym/104354/submission/206130894)

## 08 - 平面几何

[2023-07-17](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62808640)

## 09 - 静态凸包

[2023-04-09](https://cf.dianhsu.com/gym/104288/submission/201412835)

## 10 - 多项式相关（旧版）

[2023-02-06](https://atcoder.jp/contests/arc155/submissions/38664055)

## 10 - 多项式相关（新版配合取模类）

[2023-09-20](https://atcoder.jp/contests/arc163/submissions/45737810)

***

# 04 - 数据结构

## 01 - 树状数组（旧版）Fenwick 

[2023-08-11](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63382128)

## 01 - 树状数组（新版）Fenwick 

[2023-12-28](https://codeforces.com/contest/1915/submission/239262801)

## 02 - 并查集 DSU 

[2023-08-04](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63239142)

## 03 - 线段树 SegmentTree 

[2023-08-11](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63382128)

[2023-08-29](https://cf.dianhsu.com/gym/104479/submission/220987267)

[2022-04-23](https://codeforces.com/contest/1672/submission/154766851)

[2023-10-18](https://cf.dianhsu.com/gym/104417/submission/223800089)

## 04 - 懒标记线段树 LazySegmentTree 

[2023-07-17](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=62804432)

[2023-03-12](https://codeforces.com/contest/1804/submission/197106837)

[2023-03-03](https://atcoder.jp/contests/joi2023yo2/submissions/39363123)

## 05 - 取模类（旧版）Z

[2022-06-12](https://codeforces.com/contest/1697/submission/160317720)

## 05 - 取模类（新版）MLong MInt  

[2023-08-14](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63433564)

根据输入内容动态修改 MOD 的方法：`Z::setMod(p);` 。

## 06 - 状压RMQ

[2023-03-02](https://atcoder.jp/contests/joi2022ho/submissions/39351739)

## 07 - Splay

[2023-02-15](https://atcoder.jp/contests/joi2023ho/submissions/38901674)

[2023-09-30](https://cf.dianhsu.com/gym/104479/submission/221036520)

## 08 - 其他平衡树

[2023-08-04](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63246177)

[2023-08-26](https://codeforces.com/contest/1864/submission/220558951)

[2023-04-03](https://codeforces.com/contest/38/submission/200537139)

[2023-07-31](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63162242)

## 09 - 分数四则运算 Frac 

[2023-04-23](https://codeforces.com/contest/598/submission/203186397)

## 10 - 线性基 Basis

[2023-12-03](https://codeforces.com/contest/1902/submission/235594491)

***

# 05 - 字符串

## 01 - Manacher

[2023-05-14](https://codeforces.com/contest/1827/submission/205865086)

## 02 - Z函数

[2023-08-11](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63378373)

## 03 - 后缀数组 SA 

[2023-03-14](https://atcoder.jp/contests/discovery2016-qual/submissions/39727257)

## 04 - 后缀自动机 SAM 

[2023-05-27](https://cf.dianhsu.com/gym/104353/submission/207318083)

## 05 - AC自动机（旧版）AC 

[2021-07-07](https://codeforces.com/contest/710/problem/F)

## 05 - AC自动机（新版）AhoCorasick 

[2023-04-07](https://codeforces.com/contest/1801/submission/201155712)

## 06 - 随机生成模底版字符串哈希（例题）

[2022-06-09](https://codeforces.com/contest/1598/submission/160006998)
