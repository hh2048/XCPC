/**   莫比乌斯函数筛（莫比乌斯反演）
 *    2023-03-04: https://atcoder.jp/contests/tupc2022/submissions/39391116
 *    2023-04-07: https://yukicoder.me/submissions/857472
**/
std::unordered_map<int, Z> fMu;

std::vector<int> minp, primes, phi, mu;
std::vector<i64> sphi;

void sieve(int n) {
    minp.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    sphi.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    primes.clear();
    phi[1] = 1;
    mu[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mu[i * p] = -mu[i];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        sphi[i] = sphi[i - 1] + phi[i];
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