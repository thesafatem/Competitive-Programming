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

struct Vector {
    long long vec[N];

    Vector operator * (Matrix const &obj) {
        Vector res;
        for (int j = 0; j < N; j++) {
            res.vec[j] = 0;
            for (int i = 0; i < N; i++) {
                res.vec[j] += vec[j] * obj.mat[i][j];
                res.vec[j] %= MOD;
            }
        }
        return res;
    }
};
 
void solve() {
    long long k; cin >> k;
    if (k == 1) {
        cout << 1 << endl;
        return;
    }
    k -= 2;
    Matrix t;
    t.mat[0][0] = 1; t.mat[0][1] = 1;
    t.mat[1][0] = 1; t.mat[1][1] = 0;
    Vector v;
    v.vec[0] = 1; v.vec[1] = 0;
    t = t ^ k;
    v = v * t;
    cout << v.vec[0] << endl;
}   
 
int main() {
    bool tests = 0;
    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}