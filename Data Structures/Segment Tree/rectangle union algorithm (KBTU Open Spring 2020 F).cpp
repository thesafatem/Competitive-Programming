#include <iostream>
#include <vector>
#include <algorithm>
#define pb push_back
#define mp make_pair
using namespace std;

struct tree {
	vector<int> min, cnt, add;

	void init(int n) {
		min.resize(4 * n);
		cnt.resize(4 * n);
		add.resize(4 * n);
	}

	void pull(int v) {
		if (min[2 * v] == min[2 * v + 1]) {
			min[v] = min[2 * v];
			cnt[v] = cnt[2 * v] + cnt[2 * v + 1];
		} else if (min[2 * v] < min[2 * v + 1]) {
			min[v] = min[2 * v];
			cnt[v] = cnt[2 * v];
		} else {
			min[v] = min[2 * v + 1];
			cnt[v] = cnt[2 * v + 1];
		}
	} 

	void push(int v) {
		min[2 * v] += add[v];
		min[2 * v + 1] += add[v];
		add[2 * v] += add[v];
		add[2 * v + 1] += add[v];
		add[v] = 0; 
	}

	void apply(int v, int val) {
		min[v] += val;
		add[v] += val;
	}

	void build(int v, int tl, int tr) {
		if (tl == tr) {
			min[v] = 0;
			cnt[v] = 1;
			add[v] = 0;
		} else {
			int mid = tl + tr >> 1;
			build(2 * v, tl, mid);
			build(2 * v + 1, mid + 1, tr);
			pull(v);
		}
	}

	void update(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= l and tr <= r) {
			apply(v, val);
			return;
		} else if (tl > r or tr < l) {
			return;
		} else {
			push(v);
			int mid = tl + tr >> 1;
			update(2 * v, tl, mid, l, r, val);
			update(2 * v + 1, mid + 1, tr, l, r, val);
			pull(v);
		}
	}

	int get() {
		return min[1] == 0 ? cnt[1] : 0;
	}
};

int main() {
	int n; cin >> n;
	vector<int> prev(n + 10, 0);
	vector<bool> used(n + 10, false);
	vector<vector<pair<int, pair<int, int> > > > events(n + 10);
	map<int, int> last;

	for (int i = 1; i <= n; i++) {
		int num; cin >> num;
		if (last[num] > 0) {
			prev[i] = last[num];
		}
		last[num] = i;
	}

	for (int i = n; i >= 1; i--) {
		if (!used[i]) {
			int cur = i;
			vector<int> v;
			v.pb(n + 1);
			while (cur != 0) {
				v.pb(cur);
				used[cur] = true;
				cur = prev[cur];
			}
			v.pb(0);
			reverse(v.begin(), v.end());
			for (int i = 1; i < int(v.size()) - 1; i++) {
				int a = v[i - 1], b = v[i], c = v[i + 1];
				events[a + 1].pb(mp(1, mp(b, c - 1)));
				events[b + 1].pb(mp(-1, mp(b, c - 1)));
			}
		}
	}

	tree t;
	t.init(n);
	t.build(1, 1, n);

	long long ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < int(events[i].size()); j++) {
			pair<int, pair<int, int> > e = events[i][j];
			int val = e.first;
			int down = e.second.first;
			int up = e.second.second;
			t.update(1, 1, n, down, up, val);
		}
		ans += n - t.get();
	}

	cout << ans << endl;

	return 0;
}
