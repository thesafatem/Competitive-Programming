#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
int p[MAXN], sz[MAXN], r[MAXN];

void init(int n) {
	for (int i = 1; i <= n; i++) {
		p[i] = i;
		sz[i] = 1;
		r[i] = 1;
	}
}

int get_parent(int v) {
	if (v == p[v]) return v;
	return p[v] = get_parent(p[v]);
}

bool merge(int u, int v) {
	u = get_parent(u);
	v = get_parent(v);

	if (u == v) return false;

	// size heuristic
	{
		if (sz[u] > sz[v]) swap(u, v);
		p[u] = v;
		sz[v] += sz[u];
		return true;
	}

	// rank heuristic
	{
		if (r[u] > r[v]) swap(u, v);
		p[u] = v;
		r[v] = max(r[v], min(r[v], r[u]) + 1);
		return true;
	}

}

int main() {

}