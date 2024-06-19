/**   前缀函数（KMP）
 *    2023-11-17: https://qoj.ac/submission/253754
 *    2024-04-09: https://qoj.ac/submission/384408 【模板】
**/
std::vector<int> kmp(std::string s) {
    int n = s.size();
    std::vector<int> f(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = f[j];
        }
        j += (s[i] == s[j]);
        f[i + 1] = j;
    }
    return f;
}