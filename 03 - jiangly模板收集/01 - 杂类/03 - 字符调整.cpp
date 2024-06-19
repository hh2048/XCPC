/**   大小写转换、获取字母序
 *    2024-03-16: https://qoj.ac/submission/355156
**/
void rev(std::string &s) {
    int l = s.size();
    for (int i = 1; i < l; i += 2) {
        if (std::isupper(s[i])) {
            s[i] = std::tolower(s[i]);
        } else {
            s[i] = std::toupper(s[i]);
        }
    }
}

int get(char c) {
    int x;
    if (std::islower(c)) {
        x = c - 'a';
    } else {
        x = 26 + c - 'A';
    }
    return x;
}