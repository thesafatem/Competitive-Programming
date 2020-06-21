#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;

const int MAXN = 200010;

vector<int> g[MAXN];
int tin[MAXN], tout[MAXN];
vector<int> up[MAXN];
int timer = 0, lg = 0;

void dfs(int v, int p) {
	tin[v] = timer++;
	up[v][0] = p;
	for (int i = 1; i <= lg; i++) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (int i = 0; i < int(g[v].size()); i++) {
		int to = g[v][i];
		if (to == p) continue;
		dfs(to, v);
	}
	tout[v] = timer++;
}

bool is_upper(int u, int v) {
	return tin[u] <= tin[v] and tout[u] >= tout[v];
}

int lca(int u, int v) {
	if (is_upper(u, v)) return u;
	if (is_upper(v, u)) return v;
	for (int i = lg; i >= 0; i--) {
		if (!is_upper(up[u][i], v)) {
			u = up[u][i];
		}
	}
	return up[u][0];
}

void solve() {
	int n, q; cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	while ((1 << lg) <= n) lg++;
	for (int i = 0; i <= n; i++) {
		up[i].resize(lg + 1);
	}
	dfs(1, 1);
	for (int i = 0; i < q; i++) {
		int u, v; cin >> u >> v;
		cout << lca(u, v) << endl;
	}
}

int main() {
	solve();
	return 0;
}