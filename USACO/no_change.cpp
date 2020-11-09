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
    int k, n; cin >> k >> n;
    vector<long long> c(k), a(n + 1);
    for (int i = 0; i < k; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    int dp[(1 << k)];
    memset(dp, 0, sizeof dp);
    for (int mask = 1; mask < (1 << k); mask++) {
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                int prev = dp[mask - (1 << i)];
                int l = prev, r = n;
                int ans = prev;
                while (l <= r) {
                    int mid = l + r >> 1;
                    if (a[mid] - a[prev] <= c[i]) {
                        ans = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                dp[mask] = max(dp[mask], ans);
            }
        }
    }
    long long res = -1;
    for (int i = 0; i < (1 << k); i++) {
        if (dp[i] == n) {
            long long calc = 0; 
            for (int j = 0; j < k; j++) {
                if (!(i & (1 << j))) {
                    calc += c[j];
                }
            }
            res = max(res, calc);
        }
    }
    cout << res << endl;
}   
 
int main() {
    freopen("nochange.in", "r", stdin);
    freopen("nochange.out", "w", stdout);
    jonathan; 
    livingston;
    solve();
    return 0;
}