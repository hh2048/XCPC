#include <bits/stdc++.h>

using i64 = long long;

bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int findPrime(int n) {
    while (!isprime(n)) {
        n++;
    }
    return n;
}

using Hash = std::array<int, 2>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    const int P = findPrime(rng() % 900000000 + 100000000);
    
    std::string s, x;
    std::cin >> s >> x;
    
    int n = s.length();
    int m = x.length();
    
    std::vector<int> h(n + 1), p(n + 1);
    for (int i = 0; i < n; i++) {
        h[i + 1] = (10LL * h[i] + s[i] - '0') % P;
    }
    p[0] = 1;
    for (int i = 0; i < n; i++) {
        p[i + 1] = 10LL * p[i] % P;
    }
    
    auto get = [&](int l, int r) {
        return (h[r] + 1LL * (P - h[l]) * p[r - l]) % P;
    };
    
    int px = 0;
    for (auto c : x) {
        px = (10LL * px + c - '0') % P;
    }
    
    for (int i = 0; i <= n - 2 * (m - 1); i++) {
        if ((get(i, i + m - 1) + get(i + m - 1, i + 2 * m - 2)) % P == px) {
            std::cout << i + 1 << " " << i + m - 1 << "\n";
            std::cout << i + m << " " << i + 2 * m - 2 << "\n";
            return 0;
        }
    }
    
    std::vector<int> z(m + 1), f(n + 1);
    z[0] = m;
    
    for (int i = 1, j = -1; i < m; i++) {
        if (j != -1) {
            z[i] = std::max(0, std::min(j + z[j] - i, z[i - j]));
        }
        while (z[i] + i < m && x[z[i]] == x[z[i] + i]) {
            z[i]++;
        }
        if (j == -1 || i + z[i] > j + z[j]) {
            j = i;
        }
    }
    for (int i = 0, j = -1; i < n; i++) {
        if (j != -1) {
            f[i] = std::max(0, std::min(j + f[j] - i, z[i - j]));
        }
        while (f[i] + i < n && f[i] < m && x[f[i]] == s[f[i] + i]) {
            f[i]++;
        }
        if (j == -1 || i + f[i] > j + f[j]) {
            j = i;
        }
    }
    
    for (int i = 0; i + m <= n; i++) {
        int l = std::min(m, f[i]);
        
        for (auto j : { m - l, m - l - 1 }) {
            if (j <= 0) {
                continue;
            }
            if (j <= i && (get(i - j, i) + get(i, i + m)) % P == px) {
                std::cout << i - j + 1 << " " << i << "\n";
                std::cout << i + 1 << " " << i + m << "\n";
                return 0;
            }
            if (i + m + j <= n && (get(i, i + m) + get(i + m, i + m + j)) % P == px) {
                std::cout << i + 1 << " " << i + m << "\n";
                std::cout << i + m + 1 << " " << i + m + j << "\n";
                return 0;
            }
        }
    }
    
    return 0;
}

