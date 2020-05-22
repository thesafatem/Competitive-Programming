#include <iostream>
using namespace std;

struct edge {
	int u, v, cost;
};

const int MAXN = 1e5 + 5, INF = 1e9 + 7;
int n, m;
int p[MAXN], sz[MAXN], min_edge[MAXN];
edge g[MAXN];

void init() {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		sz[i] = 1;
	}
}

int gp(int v) {
	if (p[v] == v) return v;
	return p[v] = gp(p[v]);
} 

bool merge(int u, int v) {
	u = gp(u);
	v = gp(v);
	if (u == v) return false;
	if (sz[u] > sz[v]) {
		swap(u, v);
	}
	p[u] = v;
	return true;
}

long long boruvka() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> g[i].u >> g[i].v >> g[i].cost;
	}

	init();

	long long ans = 0;
	int components = n;
	while (components > 1) {
		for (int i = 1; i <= n; i++) {
			min_edge[i] = -INF;
		}

		for (int i = 1; i <= m; i++) {
			if (gp(g[i].u) == gp(g[i].v)) continue;
			int pu = gp(g[i].u);
			if (min_edge[pu] == -INF or g[i].cost < g[min_edge[pu]].cost) {
				min_edge[pu] = i;
			}
			int pv = gp(g[i].v);
			if (min_edge[pv] == -INF or g[i].cost < g[min_edge[pv]].cost) {
				min_edge[pv] = i;
			}
		}

		for (int i = 1; i <= n; i++) {
			if (min_edge[i] != -INF) {
				if (merge(g[min_edge[i]].u, g[min_edge[i]].v)) {
					ans += g[min_edge[i]].cost;
					components--;
				}
			}
		}
	}

	return ans;
}

int main() {
	cout << boruvka() << endl;
	return 0;
}