auto KMP = [&](string s, string t) -> void {
    int n = s.size(), m = t.size();
    vector<int> nxt(m + 1);
    s = '-' + s;
    t = '-' + t;
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && t[i] != t[j + 1]) j = nxt[j];
        if (t[i] == t[j + 1]) j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && s[i] != t[j + 1]) j = nxt[j];
        if (s[i] == t[j + 1]) j++;
        if (j == m) {
            cout << i - m + 1 << "\n"; // t 在 s 中出现的位置
            j = nxt[j];
        }
    }
};