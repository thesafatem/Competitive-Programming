#include <bits/stdc++.h>  
using namespace std;

template <typename T>
struct Complex {
    T real, imag;
    Complex(T x=(T)0, T y=(T)0) : real(x), imag(y) {}
    Complex conj() { return Complex(real, -imag); }
    Complex operator+(const Complex& c) { return Complex(real + c.real, imag + c.imag); }
    Complex operator-(const Complex& c) { return Complex(real - c.real, imag - c.imag); }
    Complex operator*(const T& num) { return Complex(real * num, imag * num); }
    Complex operator/(const T& num) { return Complex(real / num, imag / num); }
    Complex operator*(const Complex& c) {
        return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
    }
    Complex operator/(const Complex& c) {
        return *this * c.conj() / (c.x * c.x + c.y * c.y);
    }
};
 
typedef long long itype;
typedef long double dtype;
 
typedef Complex<dtype> ftype;
typedef vector<itype> poly;
const dtype PI = 4 * atan((dtype) 1);
 
void fft(ftype* A, int n, bool inv=false) {
    for (int i = 1, j = n / 2; i + 1 < n; i++) {
        if (i < j) swap(A[i], A[j]);
        int t = n / 2;
        while (j >= t) j -= t, t >>= 1;
        j += t;
    }
    for (int h = 2; h <= n; h <<= 1) {
        ftype wm(cos(2 * PI / h), sin(2 * PI / h));
        for (int i = 0; i < n; i += h) {
            ftype w(1);
            for (int j = i; j < i + h / 2; j++) {
                ftype x = A[j], y = w * A[j + h / 2];
                A[j + h / 2] = x - y;
                A[j] = x + y;
                w = w * wm;
            }
        }
    }
    if (inv) {
        reverse(A + 1, A + n);
        for (int i = 0; i < n; i++) {
            A[i] = A[i] / n;
        }
    }
}
 
poly pmul(poly p, poly q) {
    int dim = p.size() + q.size() - 1;
    while (__builtin_popcount(dim) != 1) ++dim;
    ftype* a = new ftype[dim];
    ftype* b = new ftype[dim];
    for (int i = 0; i < p.size(); i++)
        a[i] = p[i];
    for (int i = 0; i < q.size(); i++)
        b[i] = q[i];
    fft(a, dim);
    fft(b, dim);
    for (int i = 0; i < dim; i++)
        a[i] = a[i] * b[i];
    fft(a, dim, true);
    poly res(dim);
    for (int i = 0; i < dim; i++)
        res[i] = round(a[i].real);
    while (res.size() && !res.back())
        res.pop_back();
    delete[] a;
    delete[] b;
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    poly A(n), B(m);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }
    poly res = pmul(A, B);
}