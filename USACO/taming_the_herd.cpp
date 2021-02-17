#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(NULL); cout.tie(NULL)
#define f first
#define s second
#define ull unsigned long long
#define ll long long
#define endl '\n'
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

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int dp[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                int cnt = 0;
                for (int k = j + 1; k <= i; k++) {
                    if (a[k] != k - (j + 1)) cnt++;
                }
                dp[i][len] = min(dp[i][len], dp[j][len - 1] + cnt);
                // cout << len << " " << i << " " << j << " " << dp[i][len] << endl;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dp[n][i] << endl;
    }
}  

int main() {
    jonathan;
    livingston;
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
    bool test = 0;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}