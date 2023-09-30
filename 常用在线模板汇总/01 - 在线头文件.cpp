#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

namespace WIDA {
    // 常用宏定义
    using PII = pair<int, int>;
    using TII = tuple<int, int, int>;
    #define mymap __gnu_pbds::gp_hash_table
    #define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
    #define FOR2(i, a, b) for (int i = (int)(a); i <= (int)(b); i += 2)
    #define FORD(i, b, a) for (int i = (int)(a); i >= (int)(b); i--)
    #define ALL(a) a.begin(), a.end()
    #define RALL(a) a.rbegin(), a.rend()
    #define VI vector<int>
    #define MI map<int, int>
    #define RE return;
    #define RET return true;
    #define REF return false;
    #define Yes cout << "Yes" << endl;
    #define YES cout << "YES" << endl;
    #define No cout << "No" << endl;
    #define NO cout << "NO" << endl;
    #define pb push_back
    #define fi first
    #define se second
    #define sz size()
    
    // 常用库函数重定义
    template<typename T> T min(const vector<T> &v) {
        return *min_element(v.begin(), v.end());
    }
    template<typename T> T max(const vector<T> &v) {
        return *max_element(v.begin(), v.end());
    }
    template<typename T> T acc(const vector<T> &v) {
        return accumulate(v.begin(), v.end(), T(0LL));
    }
    template<class T> void reverse(vector<T> &v) {
        reverse(v.begin(), v.end());
    }
    template<class T> void sort(vector<T> &v) {
        sort(v.begin(), v.end());
    }
    template<class T> void rsort(vector<T> &v) {
        sort(v.rbegin(), v.rend());
    }
    template<class T> T mymax(T x, T y) {
        return x < y ? y : x;
    }
    template<class T> T mymin(T x, T y) {
        return x > y ? y : x;
    }
    template<class T> void cmax(T &x, T y) {
        x = mymax(x, y);
    }
    template<class T> void cmin(T &x, T y) {
        x = mymin(x, y);
    }
    template<class T> T sign(const T &a) {
        return a == 0 ? 0 : (a < 0 ? -1 : 1);
    }
    template<class T> T floor(const T &a, const T &b) {
        T A = abs(a), B = abs(b);
        assert(B != 0);
        return sign(a) * sign(b) > 0 ? A / B : -(A + B - 1) / B;
    }
    template<class T> T ceil(const T &a, const T &b) {
        T A = abs(a), B = abs(b);
        assert(b != 0);
        return sign(a) * sign(b) > 0 ? (A + B - 1) / B : -A / B;
    }
    int mypow(int n, int k, int p) {
        int r = 1;
        for (; k; k >>= 1, n = n * n % p) {
            if (k & 1) r = r * n % p;
        }
        return r;
    }
    template<class... Args> void __(Args... args) {
        auto _ = [&](auto x) { cout << x << " "; };
        int __[] = {(_(args), 0)...};
        cout << "\n";
    }
    const int N = 1e6 + 7;
    const int INF = numeric_limits<int>::max();
} // namespace WIDA

using namespace WIDA;


#ifndef ONLINE_JUDGE
    #define tout cout
    #include <bits/wida.h>
#else
    #define _(...)
#endif

#define endl "\n"
#define int long long


void solve() {
    
}

signed main() {
    
}

int __OI_INIT__ = []() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(0), cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(12);
    return 0;
}();
