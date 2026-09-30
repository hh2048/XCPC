## 第十二章：STL与库函数

### 库函数

#### 迭代器（iterator）

通常直接使用 `auto`，全名如 `vector<int>::iterator`。

`next`、`prev` 返回移动后的迭代器，`advance` 则直接修改传入的迭代器。**在使用前注意先检查边界**，不能越过合法迭代器范围。

只有 `vector`、`array`、`deque` 等随机访问容器支持 `it + k` 和迭代器相减，且复杂度为 $\mathcal O(1)$。

对 `set`、`map` 应使用 `next(it, k)`、`prev(it, k)`，复杂度为 $\mathcal O(k)$。

具体操作举例参见各容器章节。

#### 顺序调整（sort、shuffle）

`sort` 不稳定排序。要求区间支持随机访问，不能用于 `set`、`map`。

`stable_sort` 稳定排序。会保留比较结果相等元素的原相对顺序；只有题目确实依赖这个顺序时才使用。

```c++
vector<int> a = {4, 1, 5, 1, 3};
sort(a.begin(), a.end()); // 升序：{1, 1, 3, 4, 5}
sort(a.rbegin(), a.rend()); // 降序：{5, 4, 3, 1, 1}

stable_sort(a.begin(), a.end());
```

`reverse` 反转区间。

```c++
reverse(a.begin(), a.end());
```

`nth_element` 可以在线性均摊时间内找出第 $k \left(0 \leq k \lt n\right)$ 小元素。调用后只有 $a_k$ 的值和两侧大小关系得到保证，整体并未排序。

```c++
vector<int> a = {4, 1, 5, 1, 3};
int k = 2;
nth_element(a.begin(), a.begin() + k, a.end());
cout << a[k] << '\n'; // 找出第 k 小元素（k 从 0 开始）：3
```

`shuffle` 用于随机打乱。

```c++
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
shuffle(a.begin(), a.end(), rng);
```

#### 查找（lower_bound）

在使用前需要**先进行排序**，以下是默认升序的写法。

`lower_bound` 和 `upper_bound` 返回首个 $\geq x$ 和 $> x$ 的迭代器。

```c++
vector<int> a = {1, 3, 3, 5};
int x = 3;
auto L_itr = lower_bound(a.begin(), a.end(), x); // 首个 >= x 的迭代器
auto R_itr = upper_bound(a.begin(), a.end(), x); // 首个 > x 的迭代器

auto L_idx = L_itr - a.begin(); // 下标：1
auto R_idx = R_itr - a.begin(); // 下标：3

auto count_x = R_itr - L_itr; // x 在 a 中出现的次数：2

if (L_itr != a.end()) {
    auto L_val = *L_itr; // 首个 >= x 的值：3
}
if (R_itr != a.end()) {
    auto R_val = *R_itr; // 首个 > x 的值：5
}
```

`binary_search` 返回是否存在 $x$。

```c++
bool has_x = binary_search(a.begin(), a.end(), x);
```

`equal_range` 返回等价于同时求 `lower_bound` 和 `upper_bound` 的结果。

```c++
auto [L_itr, R_itr] = equal_range(a.begin(), a.end(), x);
```

#### 去重与删除（unique、erase）

在使用前需要**先进行排序**。

`unique` 会原地改写序列，返回去重后最后一个不重复元素的下一个位置，但是不改变容器大小，需要 `erase` 配合。

```c++
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());
```

不要在范围 `for` 循环中删除容器元素。需要边遍历边删除时，使用 `erase` 返回的新迭代器。因为删除元素后，原位置及其后的迭代器、引用和指针可能失效。

```c++
for (auto it = a.begin(); it != a.end();) {
    if (*it < 0) it = a.erase(it); // erase 返回下一个迭代器
    else ++it;
}
```

#### 填充与变换（iota、fill）

`iota` 生成连续编号；`fill` 用于整体赋值。

```c++
iota(a.begin(), a.end(), x); // 赋值为 x, x+1, x+2, ...

fill(a.begin(), a.end(), x); // 赋值为 x
```

`transform` 用于逐项变换。

```c++
transform(a.begin(), a.end(), a.begin(), [](int v) {
    return v * v;
}); // 赋值为每个元素的平方
```

#### 排列（next_permutation）

在使用前需要**先进行排序**。

`next_permutation` 会原地改写序列为字典序的下一个排列，最后一次调用返回 `false` 时会恢复为最小排列。`prev_permutation` 会原地改写序列为字典序的上一个排列（逆字典序）。

```c++
sort(p.begin(), p.end());
do {
    // 使用当前排列 p
} while (next_permutation(p.begin(), p.end()));

sort(p.rbegin(), p.rend());
do {
    // 使用当前排列 p
} while (prev_permutation(p.begin(), p.end()));
```

#### 数值扫描（accumulate、min_element）

`accumulate` 计算区间和。初始值决定累加类型，记得写 `0LL` 防止 `int` 溢出。

```c++
i64 sum = accumulate(a.begin(), a.end(), 0LL);
```

`min_element` 和 `max_element` 返回最小值和最大值的迭代器。

```c++
auto Min_itr = min_element(a.begin(), a.end());
auto Max_itr = max_element(a.begin(), a.end());
```

`is_sorted` 判断区间是否非递减。

```c++
bool nondecreasing = is_sorted(a.begin(), a.end());
```

`all_of` 判断区间是否所有元素都满足条件；`any_of` 判断区间是否存在元素满足条件。

```c++
bool all_positive = all_of(a.begin(), a.end(), [](int v) {
    return v > 0;
});
bool has_negative = any_of(a.begin(), a.end(), [](int v) {
    return v < 0;
});
```

### 数值处理与类型转换

#### 类型边界（numeric_limits）

`numeric_limits<T>::max()` 可以获取类型的最大值；`numeric_limits<T>::lowest()` 可以获取类型的最小值。

谨慎使用 `numeric_limits<double>::min()`，其值会返回浮点数的**最小正规范化值**，是一个非常小的正数，而不是最小值。

```c++
cout << numeric_limits<int>::max() << "\n"; // 输出 2147483647
cout << numeric_limits<double>::lowest() << "\n"; // 输出 -1.79769e+308
cout << numeric_limits<i64>::lowest() << "\n"; // 输出 -9223372036854775808
```

#### 数学函数（gcd、log2）

`gcd(x, y)` 返回两个数的最大公因数；`lcm(x, y)` 返回两个数的最小公倍数。

注意，当存在负数时，它们返回非负结果（可理解为等价于 `|gcd(|x|, |y|)|` 与 `|lcm(|x|, |y|)|`）。

```c++
int g = gcd(84, 30); // 6
int h = gcd(84, -30); // 6
i64 l = lcm(12LL, 18LL); // 36
```

`sqrt(x)` 返回 $\sqrt{x}$（需要 $x \geq 0$）；`pow(x, y)` 返回 $x^y$；`log2(x)` 返回 $\log_2(x)$（需要 $x > 0$）。需要注意，**这三个函数返回的结果是浮点数**，不要拿它们替代精确的整数运算。

`exp2(x)` 返回 $2^x$；`__lg(x)` 返回 $\lfloor \log_2(x) \rfloor$（需要 $x > 0$）。

#### 位运算（与或非、__builtin_）

对非负整数 $x$，第 $k \left(0 \leq k \lt 63\right)$ 位（最低位为 $0$）的查询和修改常用下面的写法，需要注意 `1LL` 的使用。

```c++
i64 x = 0; int k = 3;

x |= 1LL << k; // 第 k 位置为 1
x &= ~(1LL << k); // 第 k 位置为 0
x ^= 1LL << k; // 第 k 位取反（0/1 翻转）
bool on = (x >> k) & 1LL; // 查询第 k 位是否为 1
```

后 $k$ 位常用下面的写法：

```c++
i64 mask = (1LL << k) - 1;
i64 low = x & mask; // 取出后 k 位
i64 without_low = x & ~mask; // 后 k 位全置为 0
```

常用扩展如下（`i64` 版本需要加上 `ll` 后缀），需要注意的是，尽量预防 `x=0` 的出现，某些函数行为未定义。

```c++
int x = 26; // 26=(11010)
cout << __builtin_popcount(x) << '\n'; // 返回含 1 的数量：3
cout << __builtin_ffs(x) << '\n'; // 最低位 1 的位置（右数，从 1 开始，x=0 返回 0）：2
cout << __builtin_ctz(x) << '\n'; // 末尾 0 的个数（x=0 时未定义）：1
cout << __builtin_clz(x) << '\n'; // 32 位 unsigned 的前导 0 个数（x=0 时未定义）：27

// c++20 标准，需要为 unsigned 类型
cout << bit_width((unsigned)x) << '\n'; // 返回位数（x=0 返回 0）：5
// c++17 替代写法
cout << (x == 0 ? 0 : 32 - __builtin_clz(x)) << '\n';
```

#### 数字转字符串

`to_string` 将各种类型的数字直接转为字符串。

`itoa` 可以将十进制数字转为任意进制的字符串（`i64` 版本为 `_i64toa`）。

```c++
// MSVC 非标准扩展；GNU C++ 不保证提供
char ans[32] = {};
// 参数依次为 “待转换的数字”，“目标字符数组”，“进制”
itoa(26, ans, 2);
cout << ans << '\n'; // 11010
```

**但是这个函数为 Windows 独有**，如果编译出错，建议手写替换：

```c++
/**
    @brief 将整数 x 转换为 base 进制的字符串
    @param x 待转换的整数：[-2^63, 2^63-1]
    @param base 进制：[2, 36]
    @return 转换后的字符串
*/
string my_itoa(i64 x, int base) {
    static const string dig = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (base < 2 || base > 36) return {};
    if (x == 0) return "0";

    bool f = x < 0;
    string s;
    while (x != 0) {
        int d = x % base;
        if (d < 0) d = -d;
        s.push_back(dig[d]);
        x /= base;
    }
    if (f) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}
```

#### 字符串转数字

`stoi` 将字符串转为各种类型的数字（`i64` 版本为 `stoll`、`double` 版本为 `stod`、`f64` 版本为 `stold`）。

```c++
// 参数依次为 “待转换的字符串”，“起始位置（不推荐使用，建议直接置 0）”，“进制（传 0 时按前缀自动识别）”
cout << stoi("1010", 0, 2) << '\n'; // 10
cout << stoll("7f", 0, 16) << '\n'; // 127
cout << stoi("0x3f", 0, 0) << '\n'; // 63

cout << stod("12.34") << '\n'; // 12.34
```

`atoi` 按十进制将 C 字符串转为整数（`i64` 版本为 `atoll`）。跳过前导空白，允许一个正负号，在首个非数字字符处停止。无有效数字时返回 $0$（无法区分非法输入与合法的 `"0"`）。


```c++
cout << atoi("12") << '\n'; // 12
cout << atoi("   -12abc") << '\n'; // -12
cout << atoi("abc12") << '\n'; // 0

string s = "1234567890123";
i64 x = atoll(s.c_str());
```

### 常用容器

#### vector

`vector` 是最常用的动态数组，支持随机访问，尾部插入通常为均摊 `O(1)`。

```c++
int n = 5;
vector<int> a(n); // n 个 0
vector<int> b(n, 7); // n 个 7
vector<int> c = {4, 1, 5};

a.resize(2 * n); // 改变 size()，新增元素为 0
a.assign(n, -1); // 将内容替换为 n 个 -1
a.reserve(2 * n); // 预留空间（注意，不实际改变 size()），避免多次扩容，略微提高效率

vector dp(n, vector(m, vector<int>(k, 0))); // C++17 类模板实参推导
```

常用操作：

```c++
a.push_back(x);
a.emplace_back(x);
a.insert(a.end(), b.begin(), b.end()); // 在指定位置插入另一个容器的所有元素

a.pop_back(); // 不返回被删除的值
a.front();
a.back();
a.clear();
a.empty();
a.size();
```

扩容和删除一个元素后，原来的迭代器、引用和指针均可能失效；在区间中间插入或删除会移动后续元素，通常是线性复杂度。均需要谨慎使用。

#### string

`string` 是字符的动态数组，支持随机访问 `[]` 和大多数 `vector` 式操作。

```c++
string s;
s += 'a';
s += "abc";

int n = 5;
s.resize(2 * n); // 改变 size()，新增元素为 '\0'
s.assign(n, 'b'); // 将内容替换为 n 个 'b'
s.reserve(2 * n); // 预留空间（注意，不实际改变 size()），避免多次扩容，略微提高效率
```

常用操作：

```c++
s.push_back('a'); 

s.pop_back(); // 不返回被删除的值
s.front();
s.back();
s.clear();
s.empty();
s.size();
```

`find` 和 `rfind` 分别返回第一次（最左边）和最后一次（最右边）出现的子串位置，找不到时返回 `string::npos`。注意，不要和 `-1` 做脆弱的类型比较。

```c++
string s = "AAABCDEFGGAG";
if (s.find("go") == string::npos) {
    cout << "not found" << '\n';
}

cout << s.find("A") << '\n'; // 返回第一次出现的位置：0
cout << s.find("A", 3) << '\n'; // 从位置 3 开始查找第一次出现的位置：10
cout << s.rfind("A") << '\n'; // 返回最后一次出现的位置：10
cout << s.rfind("A", 9) << '\n'; // 从位置 9 开始查找最后一次出现的位置：2
```

输入一整行时使用 `getline`。若此前用过 `cin >> x`，先空读丢弃行尾换行：

```c++
int x;
cin >> x;

string line;
getline(cin, line); // 空读，丢弃当前行剩余内容
// 也可以使用 cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, line);
```

`substr` 返回子串。

```c++
// 参数依次为“开始位置（大于 size() 会越界报错）”，“长度（留空自动取到末尾，超过末尾自动截断）”
string p = "ABCDEFG";
cout << p.substr(2, 2) << "\n"; // CD
cout << p.substr(2) << "\n"; // CDEFG
cout << p.substr(2, 10) << "\n"; // CDEFG
```

#### pair

`pair` 适合表示二元组，默认比较按 first、second 的字典序进行。

```c++
vector<pair<int, int>> edge(m);
for (auto &[u, v] : edge) { // C++17 结构化绑定，直接修改容器元素
    cin >> u >> v;
}
```

#### tuple

`tuple` 是固定长度的异构类型集合，索引必须在编译期确定：

```c++
tuple<string, int, i64> info = {"Alice", 20, 100000};
auto [name, age, score] = info;
```

`get<i>(info)` 用于获取第 $i$ 个元素。注意这里的 $i$ 只能是常量。

```c++
cout << get<0>(info) << "\n"; // Alice
```

#### struct

`struct` 的成员默认公开，适合表示多字段状态。需要直接用于默认 `sort`、`set`、`map` 比较时定义 `operator<`；作为 `unordered` 容器的 `key` 时，需要比较全部 `key` 字段的 `operator==` 与后文的哈希函数。

`tie` 将已有字段按引用组成 `tuple`，字段顺序就是字典序比较的优先级。

```c++
struct State {
    string x, y;
    int z;

    bool operator<(const State& o) const {
        return tie(x, y, z) < tie(o.x, o.y, o.z);
    }
    bool operator==(const State& o) const {
        return tie(x, y, z) == tie(o.x, o.y, o.z);
    }
};
```

C++20 提供飞碟运算符 `operator<=>`，若对象已规范化且逐字段相等就是数值相等，可写 `= default`，会按照字段顺序自动生成比较运算符 `==`、`<`、`>`、`<=`、`>=`。以下写法可以完全替代上面的写法。

```c++
struct State {
    string x, y;
    int z;

    auto operator<=>(const State&) const = default;
};
```

成员声明顺序不是比较规则时，不能写 `= default`，而要手写 `operator<=>`。它仍会提供 `<`、`>`、`<=`、`>=`；`==` 需另写。

```c++
auto operator<=>(const State &o) const {
    return tie(y, x, z) <=> tie(o.y, o.x, o.z);
}
bool operator==(const State &) const = default;
```

#### array

`array<T, n>` 是定长数组，$n$ 必须是编译期常量；相比原生数组，它带有迭代器、`size`、`fill` 等标准接口。

```c++
array<int, 4> a;
a.fill(3);
a[1] = 8;

sort(a.begin(), a.end());
cout << a.size() << ' ' << a.front() << ' ' << a.back() << '\n';
```

#### stack

`vector` 的下位替代，常数更大且支持的操作更少。不建议使用

后进先出。没有迭代器、`clear`、`resize` 等函数，访问前先检查 `empty`。常见操作：

```c++
stack<int> st;

st.push(x);
st.emplace(x);

st.pop();
st.top();
st.empty();
st.size();
```

#### queue

先进先出。没有迭代器、`clear`、`resize` 等函数，访问前先检查 `empty`。常见操作：

```c++
queue<int> q;

q.push(x);
q.emplace(x);

q.pop();
q.front();
q.back();
q.empty();
q.size();
```

快速清空小技巧，重新构造一个临时对象并赋值：

```c++
queue<int> q;
q = queue<int>();
```

#### deque

支持两端的均摊 `O(1)` 插入、删除和随机访问。

```c++
deque<int> d;

int n;
d.resize(n); // 改变 size()，新增元素为 0
d.assign(n, 0); // 将内容替换为 n 个 0
```

常见操作：

```c++
d.push_front(x);
d.push_back(x);

d.pop_front();
d.pop_back();

d.front();
d.back();
d.clear();
d.empty();
d.size();
```

#### priority_queue

默认是大根堆，`top()` 返回当前最大值；传入 `greater<T>` 可得到小根堆。常见操作：

```c++
priority_queue<int> max_heap;
priority_queue<int, vector<int>, greater<int>> min_heap;

max_heap.push(x); // 注意，复杂度为 O(log SIZE)
max_heap.emplace(x); // 注意，复杂度为 O(log SIZE)

max_heap.pop(); // 注意，复杂度为 O(log SIZE)
max_heap.top(); // 复杂度为 O(1)
max_heap.empty();
max_heap.size();
```

自定义结构体时，比较器返回 `true` 表示第一个参数的优先级更低（应排在后面），**非常容易写反**。

```c++
struct Node {
    int x; string s;
    friend bool operator < (const Node &a, const Node &b) {
        if (a.x != b.x) return a.x > b.x;
        return a.s > b.s;
    }
};
priority_queue<Node> pq;
```

#### bitset

`bitset<n>` 是 $n$ 位的二进制数，支持按位运算。其中，$n$ 必须是编译期常量，与 `array` 类似。可以直接读入只含 0/1 的字符串或从整数构造：

```c++
bitset<32> a;
cin >> a;
bitset<32> aa(a);

unsigned x = 13;
bitset<32> c = x;
bitset<32> cc(x);
```

常见的位运算都可以直接使用。整体操作复杂度为 $\mathcal O(\tfrac{n}{w})$，其中 $w$ 为机器字长，通常为 $32$ 或 $64$。

```c++
bitset<23> B1("11101001"), B2("11101000");
cout << (B1 ^ B2) << "\n";
cout << (B1 | B2) << "\n";
cout << (B1 & B2) << "\n";
cout << (B1 == B2) << "\n";
```

可以直接用 `cout` 输出二进制数，也可以用 `to_ullong` 或 `to_string` 转换为 `unsigned long long`（超出范围会报错）或字符串输出。

```c++
bitset<8> b(27);
cout << b << "\n"; // 00011011
cout << b.to_ullong() << "\n"; // 27
cout << b.to_string() << "\n"; // 00011011
```

第 $k \left(0 \leq k \lt n\right)$ 位（最低位为 $0$）的查询和修改常用下面的写法，单点操作复杂度为 $\mathcal O(1)$。

```c++
b.set(k); // 将第 k 位置 1
b.reset(k); // 将第 k 位置 0
b.flip(k); // 将第 k 位取反（0/1 翻转）
bool on = b.test(k); // 查询第 k 位是否为 1
```

常用扩展如下：

```c++
b.set(); // 将所有位置 1
b.reset(); // 将所有位置 0
b.flip(); // 将所有位取反（0/1 翻转）

cout << b.any() << "\n"; // 判断是否至少有一个 1
cout << b.none() << "\n"; // 判断是否全为 0
cout << b.all() << "\n"; // 判断是否全为 1
cout << b.count() << "\n"; // 返回 1 的个数
```

`_Find_first`、`_Find_next` 等是 libstdc++ 的非标准扩展，除非明确使用 GNU 环境，否则不要把它们作为通用模板接口。

### 关联容器

#### set

`set` 自动去重并按比较器维护顺序。单次操作通常为 `O(log n)`。常见操作：

```c++
set<int> s = {5, 1, 5, 3}; // {1, 3, 5}

set<int, greater<int>> down = {5, 1, 5, 3}; // 降序容器：{5, 3, 1}

s.insert(x);
s.emplace(x);

s.clear();
s.empty();
s.size();

s.erase(x); // 删除等于 x 的元素
s.erase(it); // 删除迭代器 it 指向的元素
s.find(x); // 返回第一个等于 x 的迭代器，找不到时返回 end()
s.count(x); // 返回 x 的个数
s.lower_bound(x); // 默认升序：返回第一个 >= x 的迭代器
s.upper_bound(x); // 默认升序：返回第一个 > x 的迭代器
```

注意没有 `rfind`。

需要前驱或后继时先检查边界，不能对 `begin()` 求前驱：

```c++
set<int> s = {5, 1, 5, 3};
int x = 4;
auto it = s.lower_bound(x);
if (it != s.begin()) {
    auto pre = prev(it); // 最大的 < x 的元素：3
}

it = s.upper_bound(x);
if (it != s.end()) {
    auto nxt = it; // 最小的 > x 的元素：5
}

if (!s.empty()) {
    auto ed = *prev(s.end(), 1); // 返回最后一个元素：5
}
```

#### multiset

`multiset` 基本等同 `set`，但允许重复元素。常见操作：

```c++
multiset<int> ms = {5, 1, 5, 3}; // {1, 3, 5, 5}
```

`erase(x)` 用于删除，要区分“按值”和“按迭代器”：
- 当 $x$ 为某一元素时，删除**所有**这个数，复杂度为 $\mathcal O (num_x+logN)$；
- 当 $x$ 为迭代器时，删除这个迭代器。

```c++
multiset<int> ms = {1, 2, 2, 3};
ms.erase(2); // 删除所有值为 2 的元素
auto it = ms.find(2);
if (it != ms.end()) ms.erase(it); // 只删除一个 2
```

#### map

`map<Key, Value>` 按 key 有序（默认升序）且 key 唯一，支持 `[]` 访问。常见操作：

```c++
map<int, string> mp;
mp.insert({2, "two"});
mp.emplace(1, "one");
mp.try_emplace(3, "three"); // key 不存在时才构造 value
mp.insert_or_assign(2, "TWO"); // 存在则覆盖

mp[key] = value; // 随机访问，插入或覆盖
mp.find(x); // 返回第一个等于 x 的迭代器，找不到时返回 end()
mp.count(x); // 返回 x 的个数
mp.lower_bound(x); // 默认升序：返回第一个 >= x 的迭代器
mp.upper_bound(x); // 默认升序：返回第一个 > x 的迭代器
```

`mp[key]` 在 key 不存在时会插入一个默认构造的 value。只读查询优先使用 `find` 或 `count`，避免查询本身改变容器。

#### multimap

`multimap` 基本等同 `map`，但允许重复 key。常见操作：

```c++
multimap<int, string> mm = {
    {2, "two"}, {1, "one"}, {3, "three"}
};
mm.insert({2, "two"});
```

注意，`multimap` 不支持 `[]` 随机访问。如果需要遍历同一个 key 的记录，使用 `equal_range` 遍历：

```c++
auto [it1, it2] = mm.equal_range(2);
for (auto it = it1; it != it2; ++ it) {
    cout << it->second << " ";
}
```

### 哈希容器

#### unordered 系列

本质是哈希表，不维护大小顺序，遍历结果也不应作为题目输出顺序。期望单次操作的复杂度为 $\mathcal O(1)$，但是可能会被最坏数据卡到 $\mathcal O(n)$。

前序四个容器均有对应：`unordered_set`、`unordered_map`、`unordered_multiset`、`unordered_multimap`。

标准库通常已经为整数、字符串等基础类型提供哈希；`pair`、`vector` 和自定义结构体通常需要自己提供哈希。遇到没有标准哈希的 key，需要同时满足：

1. 两个相等的 key 必须得到相同的哈希值；
2. 结构体要提供 `operator==`；
3. 哈希冲突可以存在，容器会再用相等判断确认 key。

支持使用 `reserve` 函数预留空间（注意，不实际改变 `size()`），避免多次扩容，略微提高效率。但是不支持 `resize` 和 `assign` 函数。

#### 为 pair 定义哈希

一种极简的写法，常数较小。冲突发生后，哈希表可能需要多检查几个元素，并调用相等比较；这会让查找或插入变慢。

```c++
struct hash_pair { 
    template <class A, class B> 
    size_t operator()(const pair<A, B> &p) const { 
        return hash<A>{}(p.first) ^ hash<B>{}(p.second); 
    } 
};
unordered_set<pair<int, int>, hash_pair> S;
```

一种冲突概率较低的写法，但是常数较大。

```c++
struct hash_pair {
    template<class A, class B>
    size_t operator()(const pair<A, B>& p) const {
        size_t h1 = hash<A>{}(p.first);
        size_t h2 = hash<B>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};
```

#### 为 vector 定义哈希

一种极简的写法，常数较小。冲突发生后，哈希表可能需要多检查几个元素，并调用相等比较；这会让查找或插入变慢。

```c++
struct hash_vector { 
    template<class T>
    size_t operator()(const vector<T> &p) const {
        size_t h = 0;
        for (const auto &it : p) {
            h ^= hash<T>{}(it);
        }
        return h; 
    } 
};
unordered_map<vector<int>, int, hash_vector> mp;
```

一种冲突概率较低的写法，但是常数较大。

```c++
struct hash_vector {
    template<class T>
    size_t operator()(const vector<T>& a) const noexcept {
        size_t h = 0;
        for (const auto &it : a) {
            h ^= hash<T>{}(it) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};
```

#### 为结构体定义哈希

需要两个条件，一个是在结构体中重载等于号（区别于非哈希容器需要重载小于号，如上所述，当冲突时编译器需要根据重载的等于号判断），第二是写一个哈希函数。注意 `hash<>{}()` 的尖括号中的类型匹配。

一种极简的写法，常数较小。冲突发生后，哈希表可能需要多检查几个元素，并调用相等比较；这会让查找或插入变慢。

```c++
struct State { 
    string x, y;
    int z;
    bool operator==(const State& o) const {
        return tie(x, y, z) == tie(o.x, o.y, o.z);
    }
};
struct hash_state { 
    size_t operator()(const State &p) const { 
        return hash<string>{}(p.x) ^ hash<string>{}(p.y) ^ hash<int>{}(p.z); 
    } 
};
unordered_map<State, int, hash_state> mp;
```

一种冲突概率较低的写法，但是常数较大。

```c++
struct hash_state {
    size_t operator()(const State& v) const {
        constexpr size_t C = 0x9e3779b97f4a7c15ULL;

        size_t h = hash<string>{}(v.x);
        h ^= hash<string>{}(v.y) + C + (h << 6) + (h >> 2);
        h ^= hash<int>{}(v.z) + C + (h << 6) + (h >> 2);
        return h;
    }
};
```

#### 抵抗构造数据的哈希

利用随机化算法，最大限度降低规律整数造成大量碰撞的概率。但是常数非常大，通常不推荐使用：几乎不存在现场赛卡哈希的情况，建议先检查是不是哪里写错了，再怀疑哈希问题。

```c++
using u64 = uint64_t;
struct myhash {
    static u64 hash(u64 x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(u64 x) const {
        static const u64 h = chrono::steady_clock::now().time_since_epoch().count();
        return hash(x + h);
    }
    size_t operator()(pair<u64, u64> x) const {
        static const u64 h = chrono::steady_clock::now().time_since_epoch().count();
        return hash(x.first + h) ^ (hash(x.second + h) >> 1);
    }
};
unordered_map<int, int, myhash> mp;
```

### GNU PBDS

#### 引入头文件

使用 GNU PBDS 需要引入额外头文件，其中，`namespace __gnu_pbds` 会和标准库中的 `std::priority_queue` 冲突，此时依旧需要写 `std::` 或 `__gnu_pbds::` 来规避歧义。

```c++
#include <bits/extc++.h> // 万能头，如果不支持，则需要单独引入
using namespace __gnu_pbds;
```

#### gp_hash_table

对标 `unordered_map` 的哈希表，常数更优，可作为极端数据下的备选。

```c++
#include <ext/pb_ds/assoc_container.hpp>
template<class S, class T> using gpmap = gp_hash_table<S, T>;
```

#### order statistics tree

有序树，支持“第 k 小元素”和“小于 x 的元素个数”。但是常数较大，通常不推荐使用：这个写法的好处是非常短，但是**常数和拓展性都不如手写一棵平衡树**。常见用法如下，复杂度均为 $\mathcal O(\log \text{SIZE})$。

```c++
#include <ext/pb_ds/tree_policy.hpp>
template<class T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set<int> os;
os.insert(5);
os.insert(1);
os.insert(7);

auto it = os.find_by_order(1); // 下标从 0 开始；越界时返回 end()
if (it != os.end()) cout << *it << '\n'; // 5

int rank = os.order_of_key(6); // 小于 6 的元素个数：2
```

### 程序标准化

#### Lambda 与比较器

Lambda 适合一次性排序、筛选和变换，通常 `[]` 留空即可（不捕获外部变量）。

```c++
sort(a.begin(), a.end(), [](int x, int y) {
    if (x % 10 != y % 10) return x % 10 < y % 10;
    return x < y;
});
```

需要修改外部变量时用引用捕获 `[&]`（适合 DFS、DP、累加答案）；只读且希望固定副本时用值捕获 `[=]`（会产生复制，慎传数组等大对象）。

```c++
int lim = 10, sum = 0;

auto by_ref = [&](int x) {
    sum += x; // 修改外部 sum
    return x <= lim; // 每次读取当前 lim，这里使用的是为更新后的 lim = 3
};

auto by_val = [=](int x) {
    return x <= lim; // 保存构造 Lambda 时的 lim = 10
};

lim = 3;
cout << by_ref(4) << '\n'; // false，且使得 sum 增加 4
cout << by_val(4) << '\n'; // true
```

Lambda 和普通函数都可用 `auto` 推导返回类型；需要保留引用时写 `auto&`。`-> T` 用于显式指定返回类型；通常可省略，只有多个 `return` 推导类型不一致或希望强制返回类型时再写。

```c++
auto square = [](i64 x) -> i64 {
    return x * x;
};
```

#### 递归 Lambda

C++17 中最方便的递归写法是把自身作为参数传入，**此写法需要显式指定返回类型**。多层递归时，使用 `auto&& self` 常数更优于 `auto self`。

```c++
auto dfs = [&](auto&& self, int u, int fa) -> void {
    for (int v : g[u]) {
        if (v == fa) continue;
        self(self, v, u);
    }
};
dfs(dfs, 1, 0);
```

也有使用 `function` 的统一写法，但是常数比 `auto` 写法更大，不推荐使用。

```c++
function<void(int, int)> dfs = [&](int u, int fa) {
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
};
dfs(1, 0);
```

#### 使用构造函数

可以将一些必要的声明和预处理放在构造函数，在编译时，无论放置在程序的哪个位置，都会先于主函数进行。

关闭同步后不要混用 C 的 `scanf/printf` 与 C++ 的 `cin/cout`。换行优先使用 `'\n'`，除非是交互题，否则**不要使用** `endl`。

```c++
int __FAST_IO__ = []() { // 函数名称可以随意修改
    ios::sync_with_stdio(0), cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(12);
    #ifndef ONLINE_JUDGE
        freopen("1.in", "r", stdin);
        freopen("1.out", "w", stdout);
    #endif
    return 0;
}();
```

<div style="page-break-after:always">/END/</div>