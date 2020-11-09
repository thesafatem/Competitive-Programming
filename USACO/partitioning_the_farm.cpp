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

int c[20][20];
int n, k;
bool can;

int get(int x1, int y1, int x2, int y2) {
    return c[x2][y2] - c[x1][y2] - c[x2][y1] + c[x1][y1];
}

void rec(vector<int> &v, int last, int check) {

    int prev = 0;
    int cnt = sz(v) - 1;

    v.pb(n);

    for (int i = 1; i <= n; i++) {
        bool ok = true;
        for (int j = 0; j < sz(v) - 1; j++) {
            if (get(i, v[j + 1], prev, v[j]) > check) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            if (i - prev == 1) {
                cnt = k + 1;
                break;
            } else {
                cnt++;
                prev = i - 1;
                i--;
            } 
        }
    }

    if (cnt <= k) can = true;

    v.pop_back();

    for (int j = last + 1; j < n; j++) {
        v.pb(j);
        rec(v, j, check);
        v.pop_back();
    }
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 and j == 1) continue;
            else if (i == 1) {
                c[i][j] += c[i][j - 1];
            } else if (j == 1) {
                c[i][j] += c[i - 1][j];
            } else {
                c[i][j] += c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];
            }
        }
    }

    int l = 0, r = 1e9;
    int ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        can = false;
        vector<int> v;
        v.pb(0);
        rec(v, 0, mid);
        if (can) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
}
 
int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    jonathan; 
    livingston;
    solve();
    return 0;
}