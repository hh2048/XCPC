```cpp
struct Matrix : std::array<std::array<i64, 4>, 4> {
    Matrix(i64 v = 0) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                (*this)[i][j] = (i == j ? v : inf);
            }
        }
    }
};
 
Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c(inf);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                c[i][k] = std::min(c[i][k], a[i][j] + b[j][k]);
            }
        }
        c[i][3] = std::min(c[i][3], a[i][3]);
    }
    c[3][3] = 0;
    return c;
}
 
struct Node {
    Node *ch[2], *p;
    i64 sumg = 0;
    i64 sumh = 0;
    i64 sumb = 0;
    i64 g = 0;
    i64 h = 0;
    i64 b = 0;
    Matrix mat;
    Matrix prd;
    std::array<i64, 4> ans{};
    Node() : ch{nullptr, nullptr}, p(nullptr) {}
    
    void update() {
        mat = Matrix(inf);
        mat[0][0] = b + h - g + sumg;
        mat[1][1] = mat[1][2] = mat[1][3] = h + sumh;
        mat[2][0] = mat[2][1] = mat[2][2] = mat[2][3] = b + h + sumb;
        mat[3][3] = 0;
    }
};
void push(Node *t) {
    
}
void pull(Node *t) {
    t->prd = (t->ch[0] ? t->ch[0]->prd : Matrix()) * t->mat * (t->ch[1] ? t->ch[1]->prd : Matrix());
}
bool isroot(Node *t) {
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node *t) {
    return t->p->ch[1] == t;
}
void pushAll(Node *t) {
    if (!isroot(t)) {
        pushAll(t->p);
    }
    push(t);
}
void rotate(Node *t) {
    Node *q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) {
        t->ch[x]->p = q;
    }
    t->p = q->p;
    if (!isroot(q)) {
        q->p->ch[pos(q)] = t;
    }
    t->ch[x] = q;
    q->p = t;
    pull(q);
}
void splay(Node *t) {
    pushAll(t);
    while (!isroot(t)) {
        if (!isroot(t->p)) {
            if (pos(t) == pos(t->p)) {
                rotate(t->p);
            } else {
                rotate(t);
            }
        }
        rotate(t);
    }
    pull(t);
}
 
std::array<i64, 4> get(Node *t) {
    std::array<i64, 4> ans;
    ans.fill(inf);
    ans[3] = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            ans[i] = std::min(ans[i], t->prd[i][j]);
        }
    }
    return ans;
}
 
void access(Node *t) {
    std::array<i64, 4> old{};
    for (Node *i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        if (i->ch[1]) {
            auto res = get(i->ch[1]);
            i->sumg += res[0];
            i->sumh += std::min({res[1], res[2], res[3]});
            i->sumb += std::min({res[0], res[1], res[2], res[3]});
        }
        i->ch[1] = q;
        i->sumg -= old[0];
        i->sumh -= std::min({old[1], old[2], old[3]});
        i->sumb -= std::min({old[0], old[1], old[2], old[3]});
        old = get(i);
        i->update();
        pull(i);
    }
    splay(t);
}
```

```cpp
/**   Splay
 *    2024-06-24: https://cf.dianhsu.com/gym/105229/submission/267199687?version=1.5
**/
constexpr int D = 27;
struct Info {
    int up[D][2] {};
    int down[D][2] {};
    int t = 0;
    i64 ans = 0;
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.t = a.t ^ b.t;
    c.ans = a.ans + b.ans;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < 2; j++) {
            c.ans += (1LL << i) * a.down[i][j] * b.up[i][j ^ 1];
            c.up[i][j] += a.up[i][j] + b.up[i][j ^ (a.t >> i & 1)];
            c.down[i][j] += b.down[i][j] + a.down[i][j ^ (b.t >> i & 1)];
        }
    }
    return c;
}
struct Node {
    Node *ch[2], *p;
    Info val;
    Info tot;
    int cnt[D][2];
    i64 pair[D][2];
    i64 sum;
    Node() : ch{nullptr, nullptr}, p(nullptr), cnt {}, pair {}, sum {} {}
};
void pull(Node *t) {
    t->tot = (t->ch[0] ? t->ch[0]->tot : Info {}) + t->val + (t->ch[1] ? t->ch[1]->tot : Info {});
}
bool isroot(Node *t) {
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node *t) {
    return t->p->ch[1] == t;
}
void rotate(Node *t) {
    Node *q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) {
        t->ch[x]->p = q;
    }
    t->p = q->p;
    if (!isroot(q)) {
        q->p->ch[pos(q)] = t;
    }
    t->ch[x] = q;
    q->p = t;
    pull(q);
}
void update(Node *t) {
    t->val.ans = t->val.t + t->sum;
    for (int i = 0; i < D; i++) {
        t->val.ans += (1LL << i) * t->pair[i][t->val.t >> i & 1];
        for (int j = 0; j < 2; j++) {
            t->val.up[i][j] = t->cnt[i][j ^ (t->val.t >> i & 1)];
            t->val.down[i][j] = t->cnt[i][j ^ (t->val.t >> i & 1)];
        }
        t->val.up[i][t->val.t >> i & 1]++;
        t->val.down[i][t->val.t >> i & 1]++;
    }
    pull(t);
}
void splay(Node *t) {
    while (!isroot(t)) {
        if (!isroot(t->p)) {
            if (pos(t) == pos(t->p)) {
                rotate(t->p);
            } else {
                rotate(t);
            }
        }
        rotate(t);
    }
    pull(t);
}
void add(Node *t, Info s) {
    for (int i = 0; i < D; i++) {
        for (int x = 0; x < 2; x++) {
            t->pair[i][x] += s.up[i][1 ^ x];
            for (int j = 0; j < 2; j++) {
                t->pair[i][x] += t->cnt[i][j] * s.up[i][j ^ 1 ^ x];
            }
        }
        for (int j = 0; j < 2; j++) {
            t->cnt[i][j] += s.up[i][j];
        }
    }
    t->sum += s.ans;
}
void del(Node *t, Info s) {
    t->sum -= s.ans;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < 2; j++) {
            t->cnt[i][j] -= s.up[i][j];
        }
        for (int x = 0; x < 2; x++) {
            for (int j = 0; j < 2; j++) {
                t->pair[i][x] -= t->cnt[i][j] * s.up[i][j ^ 1 ^ x];
            }
            t->pair[i][x] -= s.up[i][1 ^ x];
        }
    }
}
void access(Node *t, int v) {
    Info lst;
    for (Node *i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        if (i->ch[1]) {
            add(i, i->ch[1]->tot);
        }
        i->ch[1] = q;
        if (q) {
            del(i, lst);
        } else {
            i->val.t = v;
        }
        lst = i->tot;
        update(i);
    }
    splay(t);
}
```