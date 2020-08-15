"""
link to the problem: https://codeforces.com/gym/102644/problem/H
"""

#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define endl "\n"
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(0)                   
using namespace std;                            
 
const long long INF = 3e18 + 8;
const double EPS = 1e-9;
const long long MOD = 1e9 + 7;

const int N = 2;

struct Matrix {
    long long mat[N][N];

    Matrix() {}

    Matrix(char c) {
        if (c == 'H') {
            mat[0][0] = 1;
            mat[0][1] = 0;
            mat[1][0] = 1;
            mat[1][1] = 0;
        } else if (c == 'S' or c == 'D') {
            mat[0][0] = 0;
            mat[0][1] = 1;
            mat[1][0] = 0;
            mat[1][1] = 1;
        } else if (c == 'A' or c == 'O' or c == 'E' or c == 'U' or c == 'I') {
            mat[0][0] = 0;
            mat[0][1] = 1;
            mat[1][0] = 1;
            mat[1][1] = 0;
        } else if (c != '?') {
            mat[0][0] = 1;
            mat[0][1] = 0;
            mat[1][0] = 0;
            mat[1][1] = 1;
        } else {
            mat[0][0] = 19;
            mat[0][1] = 7;
            mat[1][0] = 6;
            mat[1][1] = 20;
        }
    }

    Matrix operator * (Matrix const &obj) {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res.mat[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    res.mat[i][j] += mat[i][k] * obj.mat[k][j];
                    res.mat[i][j] %= MOD;
                }
            }
        }
        return res;
    }

    Matrix operator ^ (long long &p) {
        Matrix res, a;
        for (int i = 0; i < N; i++) res.mat[i][i] = 1;
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) a.mat[i][j] = mat[i][j];
        while (p > 0) {
            if (p & 1) res = res * a;
            a = a * a;
            p >>= 1;
        }
        return res;
    }
};

struct T {
    vector<Matrix> t;
    vector<Matrix> a;

    void init(int n, vector<Matrix> v) {
        t.resize(4 * n);
        a = v;
    }

    void pull(int v) {
        t[v] = t[2 * v] * t[2 * v + 1];
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
            return;
        }
        int mid = tl + tr >> 1;
        build(2 * v, tl, mid);
        build(2 * v + 1, mid + 1, tr);
        pull(v);
    }

    void update(int v, int tl, int tr, int i, Matrix x) {
        if (i > tr or i < tl) return;
        else if (i == tl and i == tr) {
            t[v] = x;
            return;
        } else {
            int mid = tl + tr >> 1;
            update(2 * v, tl, mid, i, x);
            update(2 * v + 1, mid + 1, tr, i, x);
            pull(v);
        }
    }
};
 
void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<Matrix> a(n + 1);
    for (int i = 0; i < n; i++) {
        a[i + 1] = Matrix(s[i]);
    }
    T t;
    t.init(n, a);
    t.build(1, 1, n);
    cout << t.t[1].mat[0][0] << endl;
    for (int i = 0; i < q; i++) {
        int pos; cin >> pos;
        char c; cin >> c;
        t.update(1, 1, n, pos, Matrix(c));
        cout << t.t[1].mat[0][0] << endl;
    }
}   
 
int main() {
    jonathan;
    livingston;
    bool tests = 0;
    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}