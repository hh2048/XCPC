```c++
/**   Link-Cut Tree【久远】
 *    2020-09-01: https://codeforces.com/gym/102129/submission/91552908
**/
namespace SegT {
    int tag[8 * N];
    int64_t wsum[8 * N], sum[8 * N];
    void add(int p, int l, int r, int v) {
        sum[p] += v * (r - l);
        wsum[p] += 1ll * v * (r - l) * (l + r + 1) / 2;
        tag[p] += v;
    }
    void push(int p, int l, int r) {
        int m = (l + r) / 2;
        add(2 * p, l, m, tag[p]);
        add(2 * p + 1, m, r, tag[p]);
        tag[p] = 0;
    }
    void pull(int p) {
        sum[p] = sum[2 * p] + sum[2 * p + 1];
        wsum[p] = wsum[2 * p] + wsum[2 * p + 1];
    }
    void rangeAdd(int p, int l, int r, int x, int y, int v) {
        if (l >= y || r <= x)
            return;
        if (l >= x && r <= y)
            return add(p, l, r, v);
        push(p, l, r);
        int m = (l + r) / 2;
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    int64_t query(int p, int l, int r, int x) {
        if (l >= x)
            return sum[p] * x;
        if (r <= x)
            return wsum[p];
        int m = (l + r) / 2;
        push(p, l, r);
        return query(2 * p, l, m, x) + query(2 * p + 1, m, r, x);
    }
    int get(int p, int l, int r, int x) {
        if (r - l == 1)
            return sum[p];
        int m = (l + r) / 2;
        push(p, l, r);
        if (x < m) {
            return get(2 * p, l, m, x);
        } else {
            return get(2 * p + 1, m, r, x);
        }
    }
}
namespace LCT {
    int ch[2 * N][2], p[2 * N], endp[2 * N], mn[2 * N], mx[2 * N];
    bool isroot(int t) {
        return ch[p[t]][0] != t && ch[p[t]][1] != t;
    }
    bool pos(int t) {
        return ch[p[t]][1] == t;
    }
    void pull(int t) {
        mn[t] = std::max(0, ch[t][0] ? mn[ch[t][0]] : SAM::len[SAM::link[t]]);
        mx[t] = ch[t][1] ? mx[ch[t][1]] : SAM::len[t];
    }
    void rotate(int t) {
        int k = !pos(t);
        int q = p[t];
        ch[q][!k] = ch[t][k];
        if (ch[t][k])
            p[ch[t][k]] = q;
        p[t] = p[q];
        if (isroot(q)) {
            endp[t] = endp[q];
        } else {
            ch[p[q]][pos(q)] = t;
        }
        ch[t][k] = q;
        p[q] = t;
        pull(q);
    }
    void splay(int t) {
        while (!isroot(t)) {
            int q = p[t];
            if (!isroot(q))
                rotate(pos(t) == pos(q) ? q : t);
            rotate(t);
        }
        pull(t);
    }
    void access(int t, int len) {
        for (int i = t, u = 0; i; u = i, i = p[i]) {
            splay(i);
            if (ch[i][1])
                endp[ch[i][1]] = endp[i];
            ch[i][1] = 0;
            pull(i);
            if (u)
                SegT::rangeAdd(1, 0, n, endp[i] - mx[i], endp[i] - mn[i], -1);
            ch[i][1] = u;
            pull(i);
        }
        splay(t);
        endp[t] = len;
        SegT::rangeAdd(1, 0, n, len - mx[t], len - mn[t], 1);
    }
    void cut(int t) {
        splay(t);
        if (ch[t][0]) {
            endp[ch[t][0]] = endp[t];
            p[ch[t][0]] = p[t];
            p[t] = 0;
            ch[t][0] = 0;
            pull(t);
        } else {
            p[t] = 0;
        }
    }
    void link(int t, int x) {
        p[t] = x;
    }
}
```

```c++
struct Node {
    Node *ch[2], *p;
    bool rev;
    int siz = 1;
    Node() : ch{nullptr, nullptr}, p(nullptr), rev(false) {}
};
void reverse(Node *t) {
    if (t) {
        std::swap(t->ch[0], t->ch[1]);
        t->rev ^= 1;
    }
}
void push(Node *t) {
    if (t->rev) {
        reverse(t->ch[0]);
        reverse(t->ch[1]);
        t->rev = false;
    }
}
void pull(Node *t) {
    t->siz = (t->ch[0] ? t->ch[0]->siz : 0) + 1 + (t->ch[1] ? t->ch[1]->siz : 0);
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
void access(Node *t) {
    for (Node *i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        i->ch[1] = q;
        pull(i);
    }
    splay(t);
}
void makeroot(Node *t) {
    access(t);
    reverse(t);
}
void link(Node *x, Node *y) {
    makeroot(x);
    x->p = y;
}
void split(Node *x, Node *y) {
    makeroot(x);
    access(y);
}
void cut(Node *x, Node *y) {
    split(x, y);
    x->p = y->ch[0] = nullptr;
    pull(y);
}
int dist(Node *x, Node *y) {
    split(x, y);
    return y->siz - 1;
}
```