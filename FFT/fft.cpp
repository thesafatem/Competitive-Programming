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
const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1); 
const string ALPHA1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string ALPHA2 = "abcdefghijklmnopqrstuvwxyz";
const string DIGITS = "0123456789";

typedef complex<double> cd;

const int LOG = 20;
const int N = 1 << LOG;
cd w[N + 5];
int rev[N + 5];

void initFFT() {
    for (int i = 0; i < N; i++) {
        w[i] = cd(cos(2 * PI * i / N), sin(2 * PI * i / N));
    }
    int k = 0;
    rev[0] = 0;
    for (int mask = 1; mask < N; mask++) {
        if (mask >> (k + 1)) k++;
        rev[mask] = rev[mask ^ (1 << k)] ^ (1 << (LOG - 1 - k));
    }
}

cd F[2][N];

void FFT(vector<cd> &A, int k) {
    int L = 1 << k;
    for (int mask = 0; mask < L; mask++) {
        F[0][rev[mask] >> (LOG - k)] = A[mask];
    }
    int t = 0, nt = 1;
    for (int lvl = 0; lvl < k; lvl++) {
        int len = 1 << lvl;
        for (int st = 0; st < L; st += (len << 1)) {
            for (int i = 0; i < len; i++) {
                cd summand = F[t][st + len + i] * w[i << (LOG - 1 - lvl)];
                F[nt][st + i] = F[t][st + i] + summand;
                F[nt][st + len + i] = F[t][st + i] - summand;
            }
        }
        swap(t, nt);
    }
    for (int i = 0; i < L; i++) {
        A[i] = F[t][i];
    }
}

vector<long long> multiply(vector<long long> A, vector<long long> B) {
    int sz1 = sz(A), sz2 = sz(B);
    int k = 0;
    while ((1 << k) < (sz1 + sz2 - 1)) k++;
    int L = 1 << k;
    vector<cd> C(L), D(L);
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
        C[i] *= D[i];
    }
    FFT(C, k);
    reverse(C.begin() + 1, C.end());
    vector<long long> res;
    res.resize(sz1 + sz2 - 1);
    for (int i = 0; i < sz1 + sz2 - 1; i++) {
        res.pb((long long)((C[i].real)() / L + 0.5));
    }
    return res;
}
 
void solve() {
    initFFT();
    int n, m; cin >> n >> m;
    vector<long long> A(n), B(m);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }
    // reverse(all(A));
    // reverse(all(B));
    vector<long long> C = multiply(A, B);
    // reverse(all(C));
    for (int i = 0; i < sz(C); i++) {
        cout << C[i] << " ";
    }
    cout << endl;
}  
 
int main() {
    jonathan;
    livingston;
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}