#include <iostream>
#include <vector>
#include <algorithm>
#define pb push_back
#define mp make_pair
using namespace std;

const int MAXN = 1e5 + 5;
int n, m;
int p[MAXN], sz[MAXN];
vector<pair<int, pair<int, int> > > edges;

void init() {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		sz[i] = 1;
	}
}

int gp(int v) {
	if (v == p[v]) return v;
	return p[v] = gp(p[v]);
}

bool merge(int u, int v) {
	u = gp(u);
	v = gp(v);
	if (u == v) return false;
	if (sz[u] > sz[v]) swap(u, v);
	p[u] = v;
	sz[v] += sz[u];
	return true;
}

long long kruskal() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, cost; cin >> u >> v >> cost;
		edges.pb(mp(cost, mp(u, v)));
	}
	sort(edges.begin(), edges.end());

	init();
	long long ans = 0;
	for (int i = 0; i < m; i++) {
		pair<int, pair<int, int> > edge = edges[i];
		int u = edge.second.first;
		int v = edge.second.second;
		int cost = edge.first;
		if (merge(u, v)) {
			ans += cost;
		}
	}

	return ans;
}	

int main() {
	cout << kruskal() << endl;
}