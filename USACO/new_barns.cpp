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

int cnt_v, cnt_t, lg;
int tree[100100];
int belongs[100100];
pair<int, int> endi[100100];
vector<int> g[100100];
int tin[100100], tout[100100], timer;
int h[100100];
vector<int> up[100100];

void dfs(int v, int p) {
    tin[v] = timer++;
    h[v] = h[p] + 1;
    up[v][0] = p;
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

int dist(int u, int v) {
    int lc = lca(u, v);
    return h[u] + h[v] - 2 * h[lc];
}

void solve() {
    int n; cin >> n;
    while ((1 << lg) < n) lg++;
    for (int i = 0; i <= n; i++) {
        up[i].resize(lg + 1);
    }
    vector<pair<char, int> > q;
    for (int i = 0; i < n; i++) {
        char type; cin >> type;
        int v; cin >> v;
        q.pb(mp(type, v));
        if (type == 'B') {
            if (v == -1) {
                tree[++cnt_t] = ++cnt_v;
                belongs[cnt_v] = cnt_t;
            } else {
                g[++cnt_v].pb(v);
                g[v].pb(cnt_v);
                belongs[cnt_v] = belongs[v];
            }
        }
    }
    for (int i = 1; i <= cnt_t; i++) {
        int root = tree[i];
        timer = 0;
        dfs(root, root);
    }
    cnt_v = 0;
    for (int i = 0; i < n; i++) {
        char t = q[i].first;
        int v = q[i].second;
        if (t == 'B') {
            ++cnt_v;
            int tre = belongs[cnt_v];
            if (v == -1) endi[tre] = mp(cnt_v, cnt_v);
            else {
                int d = dist(endi[tre].first, endi[tre].second);
                if (dist(endi[tre].first, cnt_v) > d) {
                    endi[tre].second = cnt_v;
                } else if (dist(endi[tre].second, cnt_v) > d) {
                    endi[tre].first = cnt_v;
                }
            }
        } else {
            int tre = belongs[v];
            cout << max(dist(v, endi[tre].first), dist(v, endi[tre].second)) << endl;
        }
    }
}       


int main() {
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}