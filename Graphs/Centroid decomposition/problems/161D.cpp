#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
using namespace std;

vector<int> g[50050];
int heavy[50050];
int sz[50050];
bool used[50050];
int h[50050];
int cnt[505];
int cur[505];
long long ans = 0;
int n, k;

void calc(int v, int p) {
	sz[v] = 1;
	heavy[v] = -1;
	for (int i = 0; i < sz(g[v]); i++) {
		int to = g[v][i];
		if (to == p or used[to]) continue;
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

void rec(int v, int p) {
	h[v] = h[p] + 1;
	if (h[v] <= k) ans += cnt[k - h[v]];
	if (h[v] <= k) cur[h[v]]++;
	for (int i = 0; i < sz(g[v]); i++) {
		int to = g[v][i];
		if (!used[to] and to != p) {
			rec(to, v);
		}
	}
}

void centroid(int v, int p) {
	calc(v, p);
	int ctr = dfs(v, sz[v]);
	used[ctr] = true;
	for (int i = 0; i <= k; i++) {
		cnt[i] = 0;
	}
	h[ctr] = 0;
	for (int i = 0; i < sz(g[ctr]); i++) {
		int to = g[ctr][i];
		if (!used[to]) {
			rec(to, ctr);
		}
		for (int j = 0; j <= k; j++) {
			cnt[j] += cur[j];
			cur[j] = 0;
		}
	}
	ans += cnt[k];
	for (int i = 0; i < sz(g[ctr]); i++) {
		int to = g[ctr][i];
		if (!used[to]) centroid(to, ctr);
	}
}

void solve() {
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	centroid(1, -1);
	cout << ans << endl;
}	

int main() {
	solve();
}