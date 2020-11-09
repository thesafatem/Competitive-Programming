#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define endl "\n"
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(0)
using namespace std;                            
                                                
void yes() {cout << "YES" << endl;}                                               
void no() {cout << "NO" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 
 
const int INF = 1e9 + 9;
const long long LINF = 8e18 + 8;
const double EPS = 1e-9;
const long long MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<double> a(n);
    double s = 0.0;
    double mmx = 0.0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i > 0 and i < n - 1) mmx = max(mmx, a[i]);
        s += a[i];
    }
    double res = (s - mmx) / (n - 1);
    double l = 0.0, r = 10000.0;
    while (fabs(r - l) > 1e-5) {
        double mid = (l + r) / 2.0;
        vector<double> b(n);
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            b[i] = a[i] - mid;
            sum += b[i];
        }
        double cur = 0.0;
        double mx = 0.0;
        for (int i = 1; i < n - 1; i++) {
            if (cur + b[i] > 0.0) {
                cur += b[i];
                mx = max(mx, cur);
            } else {
                cur = 0.0;
            }
        }
        if (sum - mx < 0.0) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(3) << (fabs(l - s / n) < 1e-3 ? res : l) << endl;
}   
 
int main() {
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);
    jonathan; 
    livingston;
    solve();
    return 0;
}