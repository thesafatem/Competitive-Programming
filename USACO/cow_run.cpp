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
    vector<int> le, ri;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x > 0 ? ri.pb(x) : le.pb(x);
    }
    ri.pb(0);
    sort(all(le));
    le.pb(0);
    sort(all(ri));
    reverse(all(le));
    long long dp[n + 2][n + 2][2];
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < sz(ri); i++) {
        for (int j = 0; j < sz(le); j++) {
            if (i == 0 and j == 0) continue;
            else if (i == 0) {
                dp[0][j][0] = dp[0][j - 1][0] + 1ll * abs(le[j] - le[j - 1]) * (n - i - j + 1);
                dp[0][j][1] = LINF;
            } else if (j == 0) {
                dp[i][0][0] = LINF;
                dp[i][0][1] = dp[i - 1][0][1] + 1ll * abs(ri[i] - ri[i - 1]) * (n - i - j + 1);
            } else {
                dp[i][j][1] = min(dp[i - 1][j][1] + 1ll * abs(ri[i] - ri[i - 1]) * (n - i - j + 1), 
                    dp[i - 1][j][0] + 1ll * abs(ri[i] - le[j]) * (n - i - j + 1));
                dp[i][j][0] = min(dp[i][j - 1][0] + 1ll * abs(le[j] - le[j - 1]) * (n - i - j + 1),
                    dp[i][j - 1][1] + 1ll * abs(le[j] - ri[i]) * (n - i - j + 1));
            }
        }
    }
    int a = sz(ri) - 1, b = sz(le) - 1;
    cout << min(dp[a][b][0], dp[a][b][1]) << endl;
}   
 
int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);
    jonathan; 
    livingston;
    solve();
    return 0;
}