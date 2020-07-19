#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
using namespace std;

vector<int> g[100010], p[100010]; // p stores all ancestors of vertex down to up
int sz[100010];
int next[100010];
bool used[100010];

void calc(int v, int prev) {
	sz[v] = 1;
	next[v] = -1;
	for (int i = 0; i < sz(g[v]); i++) {
		int to = g[v][i];
		if (to == prev or used[to]) continue;
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

void centroid(int v, int prev, int last) {
	calc(v, prev);
	int ctr = dfs(v, sz[v]);
	used[ctr] = true;
	if (last != -1) p[ctr].push_back(last);
	p[ctr].insert(p[ctr].end(), p[last].begin(), p[last].end());
	for (int i = 0; i < sz(g[ctr]); i++) {
		int to = g[ctr][i];
		if (!used[to]) centroid(to, ctr, ctr);
	}
}

void solve() {
	int n; cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	centroid(1, -1, 0);
	for (int i = 1; i <= n; i++) {
		cout << i << ": ";
		for (int j = 0; j < sz(p[i]); j++) {
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	solve();
}