#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
using namespace std;

vector<int> g[100010];
int c[100010];
int next[100010];
int sz[100010];
bool used[100010];

void calc(int v, int p) {
    sz[v] = 1;
    next[v] = -1;
    for (int i = 0; i < int(g[v].size()); i++) {
        int to = g[v][i];
        if (to == p or used[to]) continue;
        calc(to, v);
        sz[v] += sz[to];
        if (next[v] == -1 or sz[to] > sz[next[v]]) {
            next[v] = to;
        }
    }
}

int dfs(int v, int siz) {
    if (next[v] == -1 or 2 * sz[next[v]] <= siz) return v;
    else return dfs(next[v], siz);
}

void centroid(int v, int p, int level) {
    calc(v, p);
    int center = dfs(v, sz[v]);
    c[center] = level;
    used[center] = true;
    for (int i = 0; i < int(g[center].size()); i++) {
        int to = g[center][i];
        if (!used[to]) {
            centroid(to, center, level + 1);
        }
    }
}

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; 
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    centroid(1, -1, 0);
    for (int i = 1; i <= n; i++) {
        cout << c[i] << " ";
    }
    cout << endl;
}

int main() {
    solve();
}