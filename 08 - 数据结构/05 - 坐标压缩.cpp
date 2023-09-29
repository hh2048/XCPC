// 如果是前缀和离散化操作，务必记得要将每一个数字的后一个数字也传入计算。
template <typename T> struct Compress_ {
    int n, shift = 0; // shift 用于标记下标偏移量
    vector<T> alls;
    
    Compress_() {}
    Compress_(auto in) : alls(in) {
        init();
    }
    void add(T x) {
        alls.emplace_back(x);
    }
    template <typename... Args> void add(T x, Args... args) {
        add(x), add(args...);
    }
    void init() {
        alls.emplace_back(numeric_limits<T>::max());
        sort(alls.begin(), alls.end());
        alls.erase(unique(alls.begin(), alls.end()), alls.end());
        this->n = alls.size();
    }
    int size() {
        return n;
    }
    int operator[](T x) { // 返回 x 元素的新下标
        return upper_bound(alls.begin(), alls.end(), x) - alls.begin() + shift;
    }
    T Get(int x) { // 根据新下标返回原来元素
        assert(x - shift < n);
        return x - shift < n ? alls[x - shift] : -1;
    }
    bool count(T x) { // 查找元素 x 是否存在
        return binary_search(alls.begin(), alls.end(), x);
    }
    friend auto &operator<< (ostream &o, const auto &j) {
        cout << "{";
        for (auto it : j.alls) {
            o << it << " ";
        }
        return o << "}";
    }
};
using Compress = Compress_<int>;