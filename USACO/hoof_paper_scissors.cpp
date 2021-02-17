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
#define ll long long
#define endl '\n'
using namespace std;                            
                                                
void yes() {cout << "Yes" << endl;}                                               
void no() {cout << "No" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 

const int INF = 1e9 + 9;
const long long LINF = 8e18 + 8;
const double EPS = 1e-7;
const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1); 

void solve() {
    int n, k; cin >> n >> k;
    char a[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    string p = "HPS";
    int dp[n + 1][k + 1][5];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int c = 0; c < 3; c++) {
                dp[i][j][c] = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int c = 0; c < 3; c++) {
                if (j == 0) {
                    dp[i][j][c] = dp[i - 1][j][c] + (p[c] == a[i]);
                    //cout << i << " " << j << " " << p[c] << " " << dp[i][j][c] << endl;
                    continue;
                }
                int c1 = (c + 1) % 3;
                int c2 = (c + 2) % 3;
                dp[i][j][c] = max(dp[i - 1][j][c], max(dp[i - 1][j - 1][c1], dp[i - 1][j - 1][c2])) + (p[c] == a[i]);
                //cout << i << " " << j << " " << p[c] << " " << dp[i][j][c] << endl;
            }
        }
    }
    int mx = 0;
    for (int i = 0; i < 3; i++) mx = max(mx, dp[n][k][i]);
    cout << mx << endl;
}  

int main() {
    jonathan;
    livingston;
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    bool test = 0;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}