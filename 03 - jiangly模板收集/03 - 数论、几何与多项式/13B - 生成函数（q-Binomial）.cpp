/**   生成函数（q-Binomial）
 *    2023-09-04: https://qoj.ac/submission/164128
**/
int power(int a, int b, int p) {
    int res = 1;
    for (; b; b /= 2, a = 1LL * a * a % p) {
        if (b % 2) {
            res = 1LL * res * a % p;
        }
    }
    return res;
}

int qint(int n, int q, int p) {
    return 1LL * (power(q, n, p) - 1) * power(q - 1, p - 2, p) % p;
}

int qBinomial(int n, int k, int q, int p) {
    if (q == 0) {
        return 1;
    }
    int r = 0;
    int x = 1;
    do {
        x = 1LL * x * q % p;
        r++;
    } while (x != 1);
    
    if (n / r > k / r + (n - k) / r) {
        return 0;
    }
    int num = 1, den = 1;
    for (int i = 1; i <= k % r; i++) {
        num = 1LL * num * qint(n % r - i + 1, q, p) % p;
        den = 1LL * den * qint(i, q, p) % p;
    }
    n /= r, k /= r;
    while (n > 0 || k > 0) {
        if (n % p < k % p) {
            return 0;
        }
        for (int i = 1; i <= k % p; i++) {
            num = 1LL * num * (n % p - i + 1) % p;
            den = 1LL * den * i % p;
        }
        n /= p, k /= p;
    }
    int ans = 1LL * num * power(den, p - 2, p) % p;
    return ans;
}