#include <iostream>
#include <vector>
#define pb push_back
#define mp make_pair
using namespace std;

//---------------------------------------------------------------------//
// Solution for the problem: https://atcoder.jp/contests/dp/tasks/dp_v //
//																       //
// If modulo is not a prime, we can't use inverse in rerooting part	   //
// Instead of this we can use prefix and suffix on vertex's children   //
//---------------------------------------------------------------------//

long long MOD;

vector<int> g[100010];
vector<long long> pref[100010];
vector<long long> suf[100010];
long long dp[100010];
long long ans[100010];

void dfs(int v, int p) {
	int n = int(g[v].size());
	for (int i = 0; i < n; i++) {
		int to = g[v][i];
		if (to == p) continue;
		dfs(to, v);
		dp[v] = dp[v] * (dp[to] + 1) % MOD;
	}
}

void calc(int v, int p) {
	ans[v] = dp[v];
	int n = int(g[v].size());
	pref[v].resize(n + 5, 1ll);
	suf[v].resize(n + 5, 1ll);
	for (int i = 0; i < n; i++) {
		int to = g[v][i];
		pref[v][i + 1] = pref[v][i] * (dp[to] + 1) % MOD;
	}
	for (int i = n - 1; i >= 0; i--) {
		int to = g[v][i];
		suf[v][i + 1] = suf[v][i + 2] * (dp[to] + 1) % MOD;
	}
	for (int i = 0; i < n; i++) {
		int to = g[v][i];
		if (to == p) continue;
		long long tv = dp[v];
		long long tto = dp[to];
		dp[v] = pref[v][i] * suf[v][i + 2] % MOD;
		dp[to] = dp[to] * (dp[v] + 1) % MOD;
		calc(to, v);
		dp[v] = tv;
		dp[to] = tto;
	}
}

void solve() {
	int n; cin >> n;
	cin >> MOD;
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}	
	for (int i = 0; i <= n; i++) {
		dp[i] = 1;
	}
	dfs(1, 1);
	calc(1, 1);
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << endl;
	}
}

int main() {
	solve();
	return 0;
}