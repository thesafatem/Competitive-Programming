#include <bits/stdc++.h>
#define pb push_back
using namespace std;

vector<int> g[100010];
int c[100010];
int sz[100010];
bool used[100010];

bool cmp(int i, int j) {
    return sz[i] > sz[j];
}

void calc(int v, int p) {
    sz[v] = 1;
    for (int i = 0; i < int(g[v].size()); i++) {
        int to = g[v][i];
        if (to == p) continue;
        if (used[to]) continue;
        else {
            calc(to, v);
            sz[v] += sz[to];
        }
    }
    sort(g[v].begin(), g[v].end(), cmp);
}

int dfs(int v, int p, int siz) {
    int to = -1;
    for (int i = 0; i < int(g[v].size()); i++) {
        if (g[v][i] != p and !used[g[v][i]]) {
            to = g[v][i];
            break;
        }
    }
    if (to == -1 or 2 * sz[to] <= siz) return v;
    else return dfs(to, v, siz);
}

void centroid(int v, int p, int level) {
    calc(v, p);
    int center = dfs(v, p, sz[v]);
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