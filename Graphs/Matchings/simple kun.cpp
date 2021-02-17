#include <bits/stdc++.h>                        
#define pb push_back
#define sz(x) (long long)((x).size())
using namespace std;

vector<int> g[505];
bool used[505];
int p[505]; // p[i] = v -> (v, i) in matching

bool dfs(int v) { // returns true if there is an augmenting path
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < sz(g[v]); i++) {
        int to = g[v][i];
        if (p[to] == -1 or dfs(p[to])) { // if vertex is free or dfs found an augmenting path
            p[to] = v; // change edge from matching
            return true;
        }
    }
    return false;
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        g[u].pb(n + v);
        g[n + v].pb(u);
    }

    for (int i = 1; i <= n + m; i++) {
        p[i] = -1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + m; j++) {
            used[j] = false;
        }
        dfs(i);
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (p[n + i] != -1) {
            ans++;
        }
    }
    cout << ans << endl;
    for (int i = 1; i <= m; i++) {
        if (p[n + i] != -1) {
            cout << p[n + i] << " " << i << endl;
        }
    }
}   
 
int main() {
    jonathan;
    livingston;
    bool test = 0;
    long long t = 1;
    if (test) cin >> t;
    for (long long i = 0; i < t; i++) {
        solve();
    }
    return 0;
}