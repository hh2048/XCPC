/**   欧拉函数（求解单个数的欧拉函数）
 *    2023-10-09: https://atcoder.jp/contests/tenka1-2017/submissions/46411797
**/
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res = res / i * (i - 1);
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}