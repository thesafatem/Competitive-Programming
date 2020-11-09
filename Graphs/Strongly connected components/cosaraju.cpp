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
bool used[100100];
vector<int> order, comp;

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
        cout << v << endl;
        if (!used[v]) {
            comp.clear();
            dfs2(v);
        }
    }
}       


int main() {
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}