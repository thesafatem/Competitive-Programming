#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())     
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(0)         
using namespace std;    

vector<int> g[1000010];
int d[1000010];
int tin[1000010], tout[1000010];
vector<int> up[1000010];
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
		d[to] = d[v] + 1;
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

int dist(int u, int v) {
	int anc = lca(u, v);
	return d[u] + d[v] - 2 * d[anc];
}

void solve() {
	g[1].pb(2); g[1].pb(3); g[1].pb(4);
	g[2].pb(1); g[3].pb(1); g[4].pb(1);
	int ans = 2;
	int maxh = 1;
	int far = 2;
	int n = 4;
	int q; scanf("%d", &q);
	vector<int> qs;
	for (int i = 0; i < q; i++) {
		int v; scanf("%d", &v);
		g[v].pb(n + 1); g[v].pb(n + 2);
		g[n + 1].pb(v); g[n + 2].pb(v);
		qs.pb(v);
		n += 2;
	}
	while ((1 << lg) <= n) lg++;
	for (int i = 0; i <= n; i++) {
		up[i].resize(lg + 1);
	}
	dfs(1, 1);
	for (int i = 0; i < q; i++) {
		int v = qs[i];
		if (d[v] == maxh) {
			ans++;
			maxh++;
			far = g[v][1];
		} else {
			int di = dist(g[v][1], far);
			if (di > ans) {
				ans = di;
			}
		}
		printf("%d\n", ans);
	}
}

int main() {
	solve();
	return 0;
}