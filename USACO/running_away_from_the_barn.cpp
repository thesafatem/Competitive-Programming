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

vector<pair<int, long long> > g[200010];
long long h[200010];
int lg = 0;
vector<int> up[200010];
int scanline[200010];

void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int i = 0; i < sz(g[v]); i++) {
        int to = g[v][i].first;
        long long w = g[v][i].second;
        if (to != p) {
            h[to] = h[v] + w;
            dfs(to, v);
        }
    }
}

void dfs2(int v, int p) {
    for (int i = 0; i < sz(g[v]); i++) {
        int to = g[v][i].first;
        if (to != p) {
            dfs2(to, v);
            scanline[v] += scanline[to];
        }
    }
}

void solve() {
    int n; 
    long long L;
    cin >> n >> L;
    while ((1ll << lg) <= n) lg++;
    for (int i = 0; i <= n; i++) {
        up[i].resize(lg + 1);
    }
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        long long w; cin >> w;
        g[i].pb(mp(x, w));
        g[x].pb(mp(i, w));
    }
    g[1].pb(mp(0, LINF));
    g[0].pb(mp(1, LINF));
    dfs(0, 0);
    for (int i = 1; i <= n; i++) {
        long long cur = 0;
        int v = i;
        scanline[i]++;
        for (int j = lg; j >= 0; j--) {
            if (cur + h[v] - h[up[v][j]] <= L) {
                cur += h[v] - h[up[v][j]];
                v = up[v][j];
            }
        }
        scanline[up[v][0]]--;
    }   
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << scanline[i] << endl;
    }
}   
 
int main() {
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
    jonathan;
    livingston;
    solve();
    return 0;
}