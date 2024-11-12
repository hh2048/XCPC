/**   快读
 *    2023-08-11: https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63381475&returnHomeType=1&uid=815516497
 *    *    感谢菜菜园子群友提供
**/
struct IO {
    char a[1 << 25], b[1 << 25], *s, *t;
    IO() : s(a), t(b) {
        a[std::fread(a, 1, sizeof a, stdin)] = 0;
    }
    ~IO() {
        std::fwrite(b, 1, t - b, stdout);
    }
    IO &operator>>(std::uint64_t &x);
    IO &operator>>(std::int64_t &x);
    IO &operator>>(std::int32_t &x);
    IO &operator>>(std::uint32_t &x) {
        x = 0;
 
        while (*s < '0' || *s > '9')
            ++s;
 
        while (*s >= '0' && *s <= '9')
            x = x * 10 + *s++ - '0';
 
        return *this;
    }
    IO &operator<<(const char *tmp) {
        return std::fwrite(tmp, 1, std::strlen(tmp), stdout), *this;
    }
    IO &operator<<(char x) {
        return *t++ = x, *this;
    }
    IO &operator<<(std::int32_t x);
    IO &operator<<(std::uint64_t x);
    IO &operator<<(std::int64_t x);
    IO &operator<<(std::uint32_t x) {
        static char c[16], *i;
        i = c;
 
        if (x == 0) {
            *t++ = '0';
        } else {
            while (x != 0) {
                std::uint32_t y = x / 10;
                *i++ = x - y * 10 + '0', x = y;
            }
 
            while (i != c)
                *t++ = *--i;
        }
 
        return *this;
    }
} io;