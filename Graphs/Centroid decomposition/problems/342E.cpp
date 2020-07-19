#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
using namespace std;

vector<int> g[100010], p[100010]; // p stores all ancestors of vertex down to up
vector<int> up[100010];
set<pair<int, int> > red[100010];
int tin[100010], tout[100010];
int h[100010];
int sz[100010];
int heavy[100010];
bool used[100010];
int timer = 0, lg = 0;

void lca_dfs(int v, int p) {
	tin[v] = timer++;
	up[v][0] = p;
	for (int i = 1; i <= lg; i++) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (int i = 0; i < sz(g[v]); i++) {
		int to = g[v][i];
		if (to == p) continue;
		h[to] = h[v] + 1;
		lca_dfs(to, v);
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

int dist(int u, int v) {
	int anc = lca(u, v);
	return h[u] + h[v] - 2 * h[anc];
}

void calc(int v, int prev) {
	sz[v] = 1;
	heavy[v] = -1;
	for (int i = 0; i < sz(g[v]); i++) {
		int to = g[v][i];
		if (to == prev or used[to]) continue;
		calc(to, v);
		sz[v] += sz[to];
		if (heavy[v] == -1 or sz[to] > sz[heavy[v]]) {
			heavy[v] = to;
		}
	}
}

int dfs(int v, int siz) {
	if (heavy[v] == -1 or 2 * sz[heavy[v]] <= siz) return v;
	else return dfs(heavy[v], siz);
}

void centroid(int v, int prev, int last) {
	calc(v, prev);
	int ctr = dfs(v, sz[v]);
	used[ctr] = true;
	p[ctr].push_back(ctr);
	if (last != -1) p[ctr].insert(p[ctr].end(), p[last].begin(), p[last].end());
	for (int i = 0; i < sz(g[ctr]); i++) {
		int to = g[ctr][i];
		if (!used[to]) centroid(to, v, ctr);
	}
}

void paint(int v) {
	for (int i = 0; i < sz(p[v]); i++) {
		int ctr = p[v][i];
		int len = dist(ctr, v);
		red[ctr].insert(mp(len, v));
	}
}

int find(int v) {
	int res = 2e9;
	for (int i = 0; i < sz(p[v]); i++) {
		int ctr = p[v][i];
		int len = dist(ctr, v);
		set<pair<int, int> >::iterator it = red[ctr].begin();
		if (it != red[ctr].end()) {
			pair<int, int> mn = *it;
			res = min(res, len + mn.first);
		}
	}
	return res;
}

void solve() {
	int n; cin >> n;
	int q; cin >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	while ((1 << lg) <= n) lg++;
	for (int i = 0; i <= n; i++) up[i].resize(lg + 1);
	lca_dfs(1, 1);
	centroid(1, -1, -1);
	paint(1);
	for (int i = 0; i < q; i++) {
		int id, v; cin >> id >> v;
		if (id == 1) {
			paint(v);
		} else {
			cout << find(v) << endl;
		}
	}
}

int main() {
	solve();
}