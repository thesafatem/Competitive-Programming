#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

vector<int> LIS(vector<int> &a) {
	int n = a.size();
	vector<int> d(n + 1, INF), p(n + 1), prev(n + 1, -1);
	d[0] = -INF; p[0] = -1;
	for (int i = 0; i < n; i++) {
		int j = int(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
		if (d[j - 1] < a[i] and a[i] < d[j]) {
			d[j] = a[i];
			p[j] = i;
			prev[i] = p[j - 1];
		}
	}
	vector<int> path;
	int pos;
	for (int i = n; i >= 1; i--) {
		if (d[i] != INF) {
			pos = p[i];
			break;
		}
	}
	while (pos != -1) {
		path.push_back(pos);
		pos = prev[pos];
	}
	reverse(path.begin(), path.end());
	return path;
}

int main() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> path = LIS(a);
	for (int i = 0; i < path.size(); i++) {
		cout << a[path[i]] << " ";
	}
	cout << endl;
	return 0;
}