std::unordered_map<int, Z> fMu;

constexpr int N = 1E7;
std::vector<int> minp, primes;
std::vector<Z> mu;

void sieve(int n) {
    minp.assign(n + 1, 0);
    mu.resize(n);
    primes.clear();
    
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            mu[i] = -1;
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        mu[i] += mu[i - 1];
    }
}


Z sumMu(int n) {
    if (n <= N) {
        return mu[n];
    }
    if (fMu.count(n)) {
        return fMu[n];
    }
    if (n == 0) {
        return 0;
    }
    Z ans = 1;
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * sumMu(n / l);
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    sieve(N);
    
    int L, R;
    std::cin >> L >> R;
    L -= 1;
    
    Z ans = 0;
    for (int l = 1, r; l <= R; l = r + 1) {
        r = R / (R / l);
        if (l <= L) {
            r = std::min(r, L / (L / l));
        }
        
        ans += (power(Z(2), R / l - L / l) - 1) * (sumMu(r) - sumMu(l - 1));
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

