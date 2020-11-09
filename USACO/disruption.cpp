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
                                                
void yes() {cout << "Yes" << endl;}                                               
void no() {cout << "No" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 

const int INF = 1e9 + 9;
const long long LINF = 1e18 + 8;
const double EPS = 1e-7;
const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1);  

struct edge {
    int u, v, cost;
};

vector<int> g[50050];
vector<pair<edge, int> > e;
vector<int> res;
int tin[50050], tout[50050], timer;
vector<int> up[50050];
int lg;
map<pair<int, int>, int> mapik;

void dfs(int v, int p) {
    up[v][0] = p;
    tin[v] = timer++;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int i = 0; i < sz(g[v]); i++) {
        int to = g[v][i];
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer++;
}

bool upper(int u, int v) {
    return tin[u] <= tin[v] and tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (upper(u, v)) return u;
    if (upper(v, u)) return v;
    for (int i = lg; i >= 0; i--) {
        if (!upper(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

void solve() {
    int n, m; cin >> n >> m;
    while ((1 << lg) <= n) lg++;
    for (int i = 0; i <= n; i++) {
        up[i].resize(lg + 1);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
        mapik[mp(u, v)] = i;
        mapik[mp(v, u)] = i;
    }
    dfs(1, 1);
    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        edge eg = {u, v, c};
        e.pb(mp(eg, lca(u, v)));
    }

    sort(all(e), [&](pair<edge, int> a, pair<edge, int> b) {
        return a.first.cost < b.first.cost;
    });

    res.resize(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int l = e[i].second;
        int x = e[i].first.u;
        while (!upper(x, l)) {
            int y = up[x][0];
            // cout << x << " " << y << " " << l << endl;
            if (upper(y, l) and y != l) break;
            if (upper(l, up[x][0])) up[x][0] = l;
            if (mapik.count(mp(x, y))) {
                if (res[mapik[mp(x, y)]] == -1) {
                    res[mapik[mp(x, y)]] = e[i].first.cost;
                }
            }
            x = y;
        }
        x = e[i].first.v;
        while (!upper(x, l)) {
            int y = up[x][0];
            // cout << x << " " << y << " " << l << endl;
            if (upper(y, l) and y != l) break;
            if (upper(l, up[x][0])) up[x][0] = l;
            if (mapik.count(mp(x, y))) {
                if (res[mapik[mp(x, y)]] == -1) {
                    res[mapik[mp(x, y)]] = e[i].first.cost;
                }
            }
            x = y;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        cout << res[i] << endl;
    }
}       


int main() {
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}