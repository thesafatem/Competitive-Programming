#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;

const int MAXN = 200010, MAXQ = 200010;
vector<int> g[MAXN];
vector<pair<int, int> > q[MAXN];
pair<int, int> queries[MAXQ];
int p[MAXN], anc[MAXN], sz[MAXN], lca[MAXQ];
bool used[MAXN];

int gp(int v) {
	if (p[v] == v) return v;
	else return p[v] = gp(p[v]);
}

void merge(int u, int v) {
	int root = u;
	u = gp(u); v = gp(v);
	if (sz[u] > sz[v]) swap(u, v);
	p[u] = v;
	sz[v] += sz[u];
	anc[v] = root;
}

void dfs(int v) {
	p[v] = v;
	sz[v] = 1;
	anc[v] = v;
	used[v] = true;
	for (int i = 0; i < int(g[v].size()); i++) {
		int to = g[v][i];
		if (!used[to]) {
			dfs(to);
			merge(v, to);
		}
	}
	for (int i = 0; i < int(q[v].size()); i++) {
		pair<int, int> a = q[v][i];
		int se = a.first;
		if (!used[se]) continue;
		int j = a.second;
		lca[j] = anc[gp(se)];
	}
}

void solve() {
	int n, m; cin >> n >> m;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	for (int i = 0; i < m; i++) {
		cin >> queries[i].first >> queries[i].second;
		q[queries[i].first].pb(mp(queries[i].second, i));
		q[queries[i].second].pb(mp(queries[i].first, i));
	}
	dfs(1);
	for (int i = 0; i < m; i++) {
		cout << lca[i] << endl;
	}
}

int main() {
	solve();
	return 0;
}