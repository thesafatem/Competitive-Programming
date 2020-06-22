#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(0)
using namespace std;

struct Tree {
	struct Node {
		int max, add;
	};

	vector<Node> t;
	vector<int> a;

	void init(int n, vector<int> &_a) {
		t.resize(4 * n);
		a = _a;
	}

	void pull(int v) {
		t[v].max = max(t[2 * v].max, t[2 * v + 1].max);
	}

	void apply(int v, int val) {
		t[v].max += val;
		t[v].add += val;
	}

	void push(int v) {
		apply(2 * v, t[v].add);
		apply(2 * v + 1, t[v].add);
		t[v].add = 0;
	}

	void build(int v, int tl, int tr) {
		t[v].add = 0;
		if (tl == tr) {
			t[v].max = a[tl];
		} else {
			int mid = tl + tr >> 1;
			build(2 * v, tl, mid);
			build(2 * v + 1, mid + 1, tr);
			pull(v);
		}
	}

	void update(int v, int tl, int tr, int l, int r, int val) {
		if (tl > r or l > tr) return;
		else if (tl >= l and tr <= r) {
			apply(v, val);
		} else {
			push(v);
			int mid = tl + tr >> 1;
			update(2 * v, tl, mid, l, r, val);
			update(2 * v + 1, mid + 1, tr, l, r, val);
			pull(v);
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl > r or l > tr) return -2e9;
		else if (tl >= l and tr <= r) return t[v].max;
		else {
			push(v);
			int mid = tl + tr >> 1;
			int resl = get(2 * v, tl, mid, l, r);
			int resr = get(2 * v + 1, mid + 1, tr, l, r);
			int res = max(resl, resr);
			pull(v);
			return res;
		}
	}
};

const int MAXN = 30010;
vector<int> g[MAXN];
int val[MAXN], height[MAXN], par[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
Tree t;
int curpos = 1;

int dfs(int v) {
	int size = 1;
	int c_size = 0;
	heavy[v] = -1;
	for (int i = 0; i < int(g[v].size()); i++) {
		int to = g[v][i];
		if (to == par[v]) continue;
		par[to] = v;
		height[to] = height[v] + 1;
		int to_size = dfs(to);
		size += to_size;
		if (to_size > c_size) {
			c_size = to_size;
			heavy[v] = to;
		}
	}
	return size;
}

void decompose(int v, int _head) {
	head[v] = _head;
	pos[v] = curpos++;
	if (heavy[v] != -1) {
		decompose(heavy[v], _head);
	}
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to == par[v] or to == heavy[v]) continue;
		decompose(to, to);
	}
}

void create_tree(int n) {
	vector<int> tree(n + 1);
	for (int i = 1; i <= n; i++) {
		tree[pos[i]] = val[i];
	}
	t.init(n, tree);
	t.build(1, 1, n);
}

int get_query(int u, int v, int n) {
	int res = -2e9;
	while (head[u] != head[v]) {
		if (height[head[u]] > height[head[v]]) {
			swap(u, v);
		}
		int ans = t.get(1, 1, n, pos[head[v]], pos[v]);
		res = max(res, ans);
		v = par[head[v]];
	}
	if (height[u] > height[v]) {	
		swap(u, v);
	}
	int ans = t.get(1, 1, n, pos[u], pos[v]);
	res = max(res, ans);
	return res;
}

void update_query(int u, int v, int val, int n) {
	while (head[u] != head[v]) {
		if (height[head[u]] > height[head[v]]) {
			swap(u, v);
		}
		t.update(1, 1, n, pos[head[v]], pos[v], val);
		v = par[head[v]];
	}
	if (height[u] > height[v]) {
		swap(u, v);
	}
	t.update(1, 1, n, pos[u], pos[v], val);
}

void solve() {
	int n, q; cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1);
	decompose(1, 1);
	create_tree(n);
	for (int i = 0; i < q; i++) {
		int id; cin >> id;
		int u, v; cin >> u >> v;
		if (id == 1) {
			int val; cin >> val;
			update_query(u, v, val, n);
		} else {
			cout << get_query(u, v, n) << endl;
		}
	}
}	

int main() {
	solve();
}