#include <bits/stdc++.h>
using namespace std;

vector<int> LIS(vector<int> &a) {
	int n = a.size();
	vector<int> d(n, 1), p(n, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i] > a[j] and d[j] + 1 > d[i]) {
				d[i] = d[j] + 1;
				p[i] = j;
			}
		}
	}
	vector<int> path;
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (d[i] > d[pos]) {
			pos = i;
		}
	}
	while (pos != -1) {
		path.push_back(pos);
		pos = p[pos];
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