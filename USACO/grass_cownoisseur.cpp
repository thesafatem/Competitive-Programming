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
#define endl '\n'
using namespace std;                            
                                                
void yes() {cout << "YES" << endl;}                                               
void no() {cout << "NO" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 

const int INF = 1e9 + 9;
const long long LINF = 1e18 + 8;
const double EPS = 1e-7;
const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1);  

vector<int> g[100100];
vector<int> gr[100100];
vector<int> g2[100100];
vector<int> gr2[100100];
bool used[100100];
int belongs[100100];
int siz[100100];
int dp[3][100100];
vector<int> order, comp;
int comp_cnt;

void dfs(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to]) dfs(to);
    }
    order.pb(v);
}

void dfs2(int v) {
    used[v] = true;
    comp.pb(v);
    for (auto to : gr[v]) {
        if (!used[to]) dfs2(to);
    }
}

void dfs3(int v) {
    used[v] = true;
    for (auto to : g2[v]) {
        if (!used[to]) dfs3(to);
    }
    order.pb(v);
}

void dfs4(int v) {
    used[v] = true;
    for (auto to : gr2[v]) {
        if (!used[to]) dfs4(to);
    }
    order.pb(v);
}

void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].pb(v);
        gr[v].pb(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) dfs(i);
    }
    reverse(all(order));
    memset(used, false, sizeof used);
    for (auto v : order) {
        if (!used[v]) {
            comp.clear();
            dfs2(v);
            comp_cnt++;
            for (auto u : comp) {
                belongs[u] = comp_cnt;
            }
            siz[comp_cnt] = sz(comp);
        }
    }
    for (int u = 1; u <= n; u++) {
        for (auto v : g[u]) {
            if (belongs[u] != belongs[v]) {
                g2[belongs[u]].pb(belongs[v]);
                gr2[belongs[v]].pb(belongs[u]);
            }
        }
    }

    order.clear();
    memset(used, false, sizeof used);
    dfs3(belongs[1]);
    reverse(all(order));
    for (auto u : order) {
        dp[1][u] += siz[u];
        for (auto v : g2[u]) {
            dp[1][v] = max(dp[1][v], dp[1][u]);
        }
    }

    order.clear();
    memset(used, false, sizeof used);
    dfs4(belongs[1]);
    reverse(all(order));
    for (auto u : order) {
        dp[2][u] += siz[u];
        for (auto v : gr2[u]) {
            dp[2][v] = max(dp[2][v], dp[2][u]);
        }
    }
    int ans = siz[belongs[1]];
    for (int u = 1; u <= comp_cnt; u++) { 
        sort(all(g2[u]));
        auto last = unique(all(g2[u]));
        g2[u].erase(last, g2[u].end());
        for (auto v : g2[u]) {
            if (dp[1][v] > 0 and dp[2][u] > 0) {
                ans = max(ans, dp[1][v] + dp[2][u] - siz[belongs[1]]);
            }
        }
    }
    cout << ans << endl;
}       


int main() {
    freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}