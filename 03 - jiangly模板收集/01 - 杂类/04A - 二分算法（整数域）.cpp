/**   二分算法（整数域）： 前驱
 *    2023-09-18: https://qoj.ac/submission/182628
**/
int lo = 1, hi = 1E9;
while (lo < hi) {
    int m = (lo + hi + 1) / 2;
    if (check(m)) {
        lo = m;
    } else {
        hi = m - 1;
    }
}
std::cout << lo << "\n";

/**   二分算法（整数域）：后继
 *    2023-09-18: https://qoj.ac/submission/182752
**/
int lo = 1, hi = n;
while (lo < hi) {
    int m = (lo + hi) / 2;
    if (check(m)) {
        hi = m;
    } else {
        lo = m + 1;
    }
}
std::cout << lo << "\n";