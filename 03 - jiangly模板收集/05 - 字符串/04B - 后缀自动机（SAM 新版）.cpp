/**   后缀自动机（SAM 新版）
 *    2023-05-27: https://cf.dianhsu.com/gym/104353/submission/207318083
 *    2023-09-25: https://qoj.ac/submission/188106
 *    2024-04-09: https://qoj.ac/submission/384423 【模板】
 *    2024-04-09: https://qoj.ac/submission/384429 【模板】
**/
struct SAM {
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, next{} {}
    };
    std::vector<Node> t;
    SAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
    int extend(int p, char c, char offset = 'a') {
        return extend(p, c - offset);
    }
    
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int next(int p, char c, char offset = 'a') {
        return next(p, c - 'a');
    }
    
    int link(int p) {
        return t[p].link;
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int size() {
        return t.size();
    }
};

