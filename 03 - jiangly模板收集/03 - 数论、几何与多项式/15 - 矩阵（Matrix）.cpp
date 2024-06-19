/**   矩阵（Matrix）
 *    2024-03-14: https://qoj.ac/submission/353771
**/
using i64 = long long;
using u64 = unsigned long long;

using Matrix = std::array<u64, 65>;

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c{};
    for (int i = 0; i <= 64; i++) {
        for (int j = 0; j <= 64; j++) {
            if (j == 64 ? i == 64 : (a[i] >> j & 1)) {
                c[i] ^= b[j];
            }
        }
    }
    return c;
}

u64 operator*(u64 a, const Matrix &b) {
    u64 c = 0;
    for (int i = 0; i <= 64; i++) {
        if (i == 64 || (a >> i & 1)) {
            c ^= b[i];
        }
    }
    return c;
}

Matrix readMatrix() {
    int m;
    std::cin >> m;

    Matrix f{};
    for (int i = 0; i < m; i++) {
        int s, o;
        u64 A;
        std::cin >> s >> o >> A;

        if (o == 0) {
            for (int j = 0; j < 64; j++) {
                if (A >> ((j + s) % 64) & 1) {
                    f[64] ^= 1ULL << ((j + s) % 64);
                } else {
                    f[j] ^= 1ULL << ((j + s) % 64);
                }
            }
        } else {
            for (int j = 0; j < 64; j++) {
                if (A >> ((j + s) % 64) & 1) {
                    f[j] ^= 1ULL << ((j + s) % 64);
                }
            }
        }
    }

    u64 B;
    std::cin >> B;
    f[64] ^= B;

    return f;
}