using Real = int;
using Point = complex<Real>;
 
Real cross(const Point &a, const Point &b) {
    return (conj(a) * b).imag();
} 
Real dot(const Point &a, const Point &b) {
    return (conj(a) * b).real();
}