#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(NULL); cout.tie(NULL)
#define fi first
#define se second
#define ull unsigned long long
using namespace std;                            
                                                
void yes() {cout << "Yes" << endl;}                                               
void no() {cout << "No" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 
 
const int INF = 1e9 + 9;
const long long LINF = 1e18 + 8;
const double EPS = 1e-7;
// const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1); 
const string ALPHA1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ALPHA2 = "abcdefghijklmnopqrstuvwxyz";
const string DIGITS = "0123456789";

typedef complex<double> cd;
typedef long long ll;

const ll MOD = 998244353;

ll add(ll x, ll y) {
    x += y;
    if (x >= MOD) x -= MOD;
    return x;
}

ll sub(ll x, ll y) {
    x -= y;
    if (x < MOD) x += MOD;
    return x;
}

ll mult(ll x, ll y) {
    return x * y % MOD;
}

ll binpow(ll x, ll p) {
    if (p == 0) return 1;
    if (p & 1) return mult(binpow(x, p - 1), x);
    ll res = binpow(x, p / 2);
    return mult(res, res);
}

ll inv(ll x) {
    return binpow(x, MOD - 2);
}

const int LOG = 18;
const int N = 1 << LOG;
ll w[N + 5];
int rev[N + 5];

void initFFT() {
    ll W = -1;
    for (ll x = 2; ; x++) {
        ll y = x;
        for (int i = 1; i < LOG; i++) {
            y = mult(y, y);
        }
        if (y == MOD - 1) {
            W = x;
            break;
        }
    }
    if (W == -1) throw;
    w[0] = 1;
    for (int i = 1; i < N; i++) {
        w[i] = mult(w[i - 1], W);
    }

    int k = 0;
    rev[0] = 0;
    for (int mask = 1; mask < N; mask++) {
        if (mask >> (k + 1)) k++;
        rev[mask] = rev[mask ^ (1 << k)] ^ (1 << (LOG - 1 - k));
    }
}

ll F[2][N];

void FFT(ll A[], int k) {
    int L = 1 << k;
    for (int mask = 0; mask < L; mask++) {
        F[0][rev[mask] >> (LOG - k)] = A[mask];
    }
    int t = 0, nt = 1;
    for (int lvl = 0; lvl < k; lvl++) {
        int len = 1 << lvl;
        for (int st = 0; st < L; st += (len << 1)) {
            for (int i = 0; i < len; i++) {
                ll summand = mult(F[t][st + len + i], w[i << (LOG - 1 - lvl)]);
                F[nt][st + i] = add(F[t][st + i], summand);
                F[nt][st + len + i] = sub(F[t][st + i], summand);
            }
        }
        swap(t, nt);
    }
    for (int i = 0; i < L; i++) {
        A[i] = F[t][i];
    }
}

vector<ll> multiply(ll A[], ll B[], int sz1, int sz2) {
    int k = 0;
    while ((1 << k) < (sz1 + sz2 - 1)) k++;
    int L = 1 << k;
    ll C[L], D[L];
    for (int i = 0; i < L; i++) {
        C[i] = D[i] = 0;
    }
    for (int i = 0; i < sz1; i++) {
        C[i] = A[i];
    }
    for (int i = 0; i < sz2; i++) {
        D[i] = B[i];
    }
    FFT(C, k);
    FFT(D, k);
    for (int i = 0; i < L; i++) {
        C[i] = mult(C[i], D[i]);
    }
    FFT(C, k);
    reverse(C + 1, C + L);
    vector<ll> res;
    res.resize(sz1 + sz2 - 1);
    ll rL = inv(L);
    for (int i = 0; i < sz1 + sz2 - 1; i++) {
        res.push_back(mult(C[i], rL));
    }
    return res;
}

void solve() {

}  
 
int main() {
    jonathan;
    livingston;
    initFFT();
    bool test = true;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}