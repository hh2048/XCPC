#include <bits/stdc++.h>
using namespace std;


/* tuple流输出定义 */
// helper: print elements with index IDX and higher of tuple t having MAX elements
template<int IDX, int MAX, typename... Args> struct PRINT_TUPLE {
    static void print(ostream &os, const tuple<Args...> &t) {
        os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
        PRINT_TUPLE<IDX + 1, MAX, Args...>::print(os, t);
    }
};
// partial specialization to end the recursion
template<int MAX, typename... Args> struct PRINT_TUPLE<MAX, MAX, Args...> {
    static void print(ostream &os, const tuple<Args...> &t) {}
};
// output operator for tuples
template<typename... Args> ostream &operator<<(ostream &os, const tuple<Args...> &t) {
    os << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);
    return os << "]";
}


/* pair流输出定义 */
template<class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    return os << '[' << p.first << "," << p.second << ']';
}


/* 顺序容器流输出定义 */
template<class T, class = decay_t<decltype(*begin(declval<T>()))>,
class = enable_if_t<!is_same<T, string>::value>>
ostream &operator<<(ostream &os, const T &c) {
    os << "[";
    for (auto it = c.begin(); it != c.end(); ++it) {
        if (it != prev(c.end())) {
            os << *it << ", ";
        } else {
            os << *it << "]";
        }
    }
    return os;
}


/* stack流输出定义 */
template <class T>
ostream &operator<<(ostream &os, const stack<T> &S) {
    stack<T> s = S;
    os << "S[";
    while (s.size() > 1) {
        os << s.top() << ",";
        s.pop();
    }
    if (s.size()) {
        os << s.top();
    }
    os << ">";
    return os;
}


/* queue流输出定义 */
template <class T>
ostream &operator<<(ostream &os, const queue<T> &S) {
    queue<T> s = S;
    os << "Q<";
    while (s.size() > 1) {
        os << s.front() << ",";
        s.pop();
    }
    if (s.size()) {
        os << s.front();
    }
    os << "]";
    return os;
}


/* deque流输出定义 */
template <class T>
ostream &operator<<(ostream &os, const deque<T> &S) {
    deque<T> s = S;
    os << "[";
    while (s.size() > 1) {
        os << s.front() << ", ";
        s.pop_front();
    }
    if (s.size()) {
        os << s.front();
    }
    os << "]";
    return os;
}


/* priority_queue流输出定义 */
template <class T>
ostream &operator<<(ostream &os, const priority_queue<T> &S) { // 大根堆
    priority_queue<T> s = S;
    os << "[";
    while (s.size() > 1) {
        os << s.top() << ", ";
        s.pop();
    }
    if (s.size()) {
        os << s.top();
    }
    os << "]";
    return os;
}
template <class T>
ostream &operator<<(ostream &os, const priority_queue<T, vector<T>, greater<T>> &S) { // 小根堆
    priority_queue<T, vector<T>, greater<T>> s = S;
    os << "[";
    while (s.size() > 1) {
        os << s.top() << ", ";
        s.pop();
    }
    if (s.size()) {
        os << s.top();
    }
    os << "]";
    return os;
}


/* 可变模板输出 */
template<class... Args> void _(Args... args) {
    auto _ = [&](auto x) -> void { cout << x << "▏"; };
    cout << "●";
    int arr[] = {(_(args), 0)...};
    cout << "\n";
}
template<class... Args> void _1(Args... args) {
    auto _ = [&](auto x) -> void { cout << x << "▏"; };
    cout << "  ●";
    int arr[] = {(_(args), 0)...};
    cout << "\n";
}
template<class... Args> void _2(Args... args) {
    auto _ = [&](auto x) -> void { cout << x << "▏"; };
    cout << "  ▲";
    int arr[] = {(_(args), 0)...};
    cout << "\n";
}
template<class... Args> void _3(Args... args) {
    auto _ = [&](auto x) -> void { cout << x << "▏"; };
    cout << "  ▼";
    int arr[] = {(_(args), 0)...};
    cout << "\n";
}

// 常用宏定义
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FOR2(i, a, b) for (int i = (int)(a); i <= (int)(b); i += 2)
#define FORD(i, b, a) for (int i = (int)(a); i >= (int)(b); i--)
#define ALL(a) a.begin(), a.end()
#define rALL(a) a.rbegin(), a.rend()
#define ED exit(0);
#define CE continue;
#define CO continue;
#define BK break;
