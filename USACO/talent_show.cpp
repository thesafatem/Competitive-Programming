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
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), t(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> t[i];
        t[i] = t[i] * 1000;
    }
    int l = 0, r = 1e9;
    long long dp[n + 1][W + 1];
    int ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= W; j++) {
                dp[i][j] = -INF;
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int _w = 0; _w <= W; _w++) {
                int w_ = min(_w + w[i], W);
                dp[i][_w] = max(dp[i][_w], dp[i - 1][_w]);
                dp[i][w_] = max(dp[i][w_], dp[i - 1][_w] + t[i] - 1ll * mid * w[i]);
            }
        }
        if (dp[n][W] >= 0) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
}  

int main() {
    jonathan;
    livingston;
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    bool test = 0;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}