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

vector<pair<int, int> > g[20010];
vector<long long> d[205];

void solve() {
    int n, m, k, q; cin >> n >> m >> k >> q;
    vector<int> hubs(k);
    vector<int> is_hub(n + 1, -1);
    for (int i = 0; i < m; i++) {
        int u, v, d; cin >> u >> v >> d;
        g[u].pb(mp(v, d));
    }
    for (int i = 0; i < k; i++) {
        cin >> hubs[i];
        is_hub[hubs[i]] = i;
    }
    for (int i = 0; i < k; i++) {
        int hub = hubs[i];
        d[i].resize(n + 1, LINF);
        d[i][hub] = 0;
        set<pair<int, int> > setik;
        setik.insert(mp(d[i][hub], hub));
        while (!setik.empty()) {
            int v = setik.begin()->second;
            setik.erase(setik.begin());
            for (int j = 0; j < sz(g[v]); j++) {
                int to = g[v][j].first;
                int w = g[v][j].second;
                if (d[i][v] + w < d[i][to]) {
                    setik.erase(mp(d[i][to], to));
                    d[i][to] = d[i][v] + w;
                    setik.insert(mp(d[i][to], to));
                }
            }
        } 
    }
    long long res = 0;
    int cnt = 0;
    for (int it = 0; it < q; it++) {
        int u, v; cin >> u >> v;
        if (is_hub[u] != -1) {
            if (d[is_hub[u]][v] != LINF) {
                cnt++;
                res += d[is_hub[u]][v];
            }
        } else {
            long long mn = LINF;
            for (int i = 0; i < sz(g[u]); i++) {
                int to = g[u][i].first;
                if (is_hub[to] == -1) break;
                else if (d[is_hub[to]][v] != LINF) {
                    mn = min(mn, d[is_hub[to]][v] + g[u][i].second);
                }
            }
            if (mn != LINF) {
                cnt++;
                res += mn;
            }
        }
    }
    cout << cnt << endl;
    cout << (res == LINF ? 0 : res) << endl;
}   
 
int main() {
    freopen("vacationgold.in", "r", stdin);
    freopen("vacationgold.out", "w", stdout);
    jonathan; 
    livingston;
    solve();
    return 0;
}